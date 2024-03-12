#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFLEN 512  // Max length of buffer
#define PORT 8888   // The port on which to listen for incoming data

int main(void) {
    struct sockaddr_in si_me, si_other;
    int sockfd, i, slen = sizeof(si_other), recv_len;
    char buf[BUFLEN];

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("socket");
        return 1;
    }

    // Zero out the structure
    memset((char *)&si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind socket to port
    if (bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me)) == -1) {
        perror("bind");
        return 1;
    }

    // Keep listening for data
    while (1) {
        printf("Waiting for data...");
        fflush(stdout);

        // Try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == -1) {
            perror("recvfrom");
            return 1;
        }

        // Print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n", buf);

        // Clear the buffer
        memset(buf, 0, BUFLEN);
    }

    close(sockfd);
    return 0;
}

