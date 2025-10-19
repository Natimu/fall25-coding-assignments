#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>


struct dhcp_packet {
uint8_t op; // Operation code (1 = BOOTREQUEST, 2 = BOOTREPLY)
uint32_t ciaddr; // Client IP address (0 if client is in INIT state)
uint32_t yiaddr; // 'Your' (client) IP address
uint32_t fromIPAddr; // should be 0.0.0.0 on client->server
uint32_t toIPAddr; // should be 255.255.255.255 on client->server
uint16_t transID; // transaction ID – random number client->server
};

int create_UDP_socket(){
    int sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0){
        perror("creating a socket failed");
        exit(EXIT_FAILURE);
    }
    return sd;
}

void enable_broadcast(int sc){
    int enable_broadcast = 1;
    if (setsockopt(sc, SOL_SOCKET, SO_BROADCAST, &enable_broadcast, sizeof(enable_broadcast)) == -1){
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

}
void send_packet(int sc, struct dhcp_packet *packet, struct sockaddr_in *server_addr){
    if (sendto(sc, packet, sizeof(*packet), 0,
               (struct sockaddr *)server_addr, sizeof(*server_addr)) == -1) {
        perror("sendto failed");
        exit(EXIT_FAILURE);
    }
    printf("Sent broadcast request (op=%d, transID=%d)\n",packet->op,  ntohs(packet->transID));

}

void Validate_reply(struct dhcp_packet *reply){
    // Validate reply
    if (reply->op == 2 && reply->toIPAddr == inet_addr("255.255.255.255")) {
        printf("\n--- Received Reply ---\n");
        printf("op: %d\n", reply->op);
        printf("ciaddr: %s\n", inet_ntoa(*(struct in_addr*)&reply->ciaddr));
        printf("yiaddr: %s\n", inet_ntoa(*(struct in_addr*)&reply->yiaddr));
        printf("fromIPAddr: %s\n", inet_ntoa(*(struct in_addr*)&reply->fromIPAddr));
        printf("toIPAddr: %s\n", inet_ntoa(*(struct in_addr*)&reply->toIPAddr));
        printf("transID: %d\n", ntohs(reply->transID));
    } else {
        printf("Invalid reply received.\n");
    }


}

int main(int argc, char *argv[]){
    if (argc !=2){
        fprintf(stderr, "Usage: %s client expects server port number\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);

    int sd = create_UDP_socket();
    enable_broadcast(sd);

    struct dhcp_packet packet;
    memset(&packet, 0, sizeof(packet));

    packet.op = 1; // BOOTREQUEST
    packet.ciaddr = inet_addr("0.0.0.0");
    packet.yiaddr = inet_addr("0.0.0.0");
    packet.fromIPAddr = inet_addr("0.0.0.0");
    packet.toIPAddr = inet_addr("255.255.255.255");
    srand(time(NULL));
    packet.transID = htons(rand() % 71221);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

    send_packet(sd, &packet, &server_addr);

    // wait for reply
    struct dhcp_packet reply;
    socklen_t addrlen = sizeof(server_addr);
    int n = recvfrom(sd, &reply, sizeof(reply), 0,
                     (struct sockaddr *)&server_addr, &addrlen);
    if (n < 0) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }

    Validate_reply(&reply);

    
    close(sd);

    return 0;
}