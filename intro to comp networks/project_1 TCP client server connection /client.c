#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define maxString 256   // Maximum length string allowed

// declaration for the three helping methods
int createSocket(const char *ip, int port); //creating a connection
void sendString(int sd, const char *str);   //sending a string file
void echo(int sd);  //receiving back and echo from the server


//inorder to create a connection two things are required. an ipaddress and port number 
// connection type TCP (connection oriented)
int createSocket(const char *ip, int port)
{
    int sd;
    struct sockaddr_in server_address;  //create a socket IPv4

    //create a socket IPv4 , TCP 
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("error opening stream socket");
        exit(1);
    }
    //Fill in server address information
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    // convert ipaddress from text to binary
    if(inet_pton(AF_INET, ip, &server_address.sin_addr) <= 0){
        printf("Failed to convert ip address\n");
        close(sd);  // if it fails to create the connection close sd and exit, "do not try to be a hero" :-)
        exit(1);
    }

    // connect to the server
    if(connect(sd, (struct sockaddr *)&server_address, sizeof(struct sockaddr_in)) < 0){
        perror("Error connecting stream socket");
        close(sd);
        exit(1);
    }
    return sd;  // return socket descriptor

}

// send string to server
void sendString(int sd, const char *str){

    int length = strlen(str);       //string length
    int convertedLength = htonl(length);    //convert length to network byte order

    //send the string length
    if(write(sd, &convertedLength, sizeof(convertedLength)) != sizeof(convertedLength)){
        printf("Error sending fileNameSize\n");
        close(sd);
        exit(1);
    }

    //send the actual string
    if(write(sd, str, length) != length){
        printf("Error sending FilleName\n");
        exit(1);
    }
}

// Hearing back from the server
void echo(int sd){

    int networkLength, length, rc;
    char buffer[maxString];

    // Hear the network length sent from the server
    if(read(sd,&networkLength, sizeof(networkLength)) <= 0){
        printf("Error reading echoed length\n");
        close(sd);
        exit(1);
    }

    // Convert the network length to host byte order
    length = ntohl(networkLength);

    printf("Server will echo back %d bytes.\n", length);    // Print the expected string length

    int bytesCount = 0;
    char *ptr = buffer;

    // Read until all byte are received
    while(bytesCount < length){
        if((rc= read(sd, ptr, length-bytesCount)) < 0){
            printf("Error Reading echoed string\n"); // Is interupted before reading all the expected strings
            close(sd);
            exit(1);
        }
        bytesCount += rc;
        ptr += rc;
    }

    buffer[length] = '\0';  // Add a Null-terminate the received string
    printf("Server echoed: '%s' \n", buffer);   // Print echoed string

}

int main(int argc, char *argv[]){

    int sd;
    int rc;
    struct sockaddr_in sin_addr;

    // Check command line arguments (needs port and IP)
    if(argc < 3){
        printf("Usage is: client <portNumber> <ipaddress> \n");
        exit(1);
    }

    // Convert portnumber and extract ipaddress
    int portNumber = atoi(argv[1]);
    const char *ipaddress = argv[2];
    //Create a socket and connect to a server
    sd = createSocket(ipaddress, portNumber);

    char file[maxString]; //Fill size has to be lessthan 255 character
    printf("Enter string (Has to be lessthan 255 characters): ");
    fgets(file, maxString, stdin);
    file[strcspn(file, "\n")] = '\0';   // Remove trailing newline from fgets

    sendString(sd, file);// Send string to server 
    
    echo(sd);   //Receive echo

    close(sd);  //close the socket
    return 0;
}
