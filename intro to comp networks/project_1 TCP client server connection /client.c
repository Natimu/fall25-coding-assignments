#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define maxString 256


int createSocket(const char *ip, int port);
void sendString(int sd, const char *str);
void echo(int sd);

int createSocket(const char *ip, int port){
    int sd;
    struct sockaddr_in server_address;


    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("error opening stream socket");
        exit(1);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if(inet_pton(AF_INET, ip, &server_address.sin_addr) <= 0){
        printf("Failed to convert ip address\n");
        close(sd);
        exit(1);
    }

    if(connect(sd, (struct sockaddr *)&server_address, sizeof(struct sockaddr_in)) < 0){
        perror("Error connecting stream socket");
        close(sd);
        exit(1);
    }
    return sd;

}

void sendString(int sd, const char *str){

    int length = strlen(str);
    int convertedLength = htonl(length);

    if(write(sd, &convertedLength, sizeof(convertedLength)) != sizeof(convertedLength)){
        printf("Error sending fileNameSize\n");
        close(sd);
        exit(1);
    }

    if(write(sd, str, length) != length){
        printf("Error sending FilleName");
        exit(1);
    }
}

void echo(int sd){

    int networkLength, length, rc;
    char buffer[maxString];

    if(read(sd,&networkLength, sizeof(networkLength)) <= 0){
        printf("Error reading echoed length");
        close(sd);
        exit(1);
    }

    length = ntohl(networkLength);

    printf("Server will echo back %d bytes.\n", length);

    int bytesCount = 0;
    char *ptr = buffer;

    while(bytesCount < length){
        if((rc= read(sd, ptr, length-bytesCount)) < 0){
            printf("Error Reading echoed string");
            close(sd);
            exit(1);
        }
        bytesCount += rc;
        ptr += rc;
    }

    buffer[length] = '\0';
    printf("Server echoed: '%s' \n", buffer);

}

int main(int argc, char *argv[]){

    int sd;
    int rc;
    struct sockaddr_in sin_addr;

    if(argc < 3){
        printf("Usage is: client <portNumber> <ipaddress> \n");
        exit(1);
    }

    int portNumber = atoi(argv[1]);
    const char *ipaddress = argv[2];

    int sd = createSocket(ipaddress, portNumber);

    char file[maxString];
    printf("Enter string (Has to be lessthan 255 characters): ");
    fgets(file, maxString, stdin);
    file[strcspn(file, "\n")] = '\0';

    sendString(sd, file);
    echo(sd);

    close(sd);
    return 0;
}
