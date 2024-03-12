#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "192.168.0.144" // Replace with your server's IP address
#define SERVER_PORT 8888        // Replace with your server's port
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE] = "Hello, UDP!"; // Message to send

    // Create socket (AF_INET - IPv4, SOCK_DGRAM - UDP)
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Send the message to the server
    if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Send to failed");
        exit(EXIT_FAILURE);
    }
    printf("UDP packet sent successfully\n");

    // Close the socket
    close(sockfd);

    return 0;
}

