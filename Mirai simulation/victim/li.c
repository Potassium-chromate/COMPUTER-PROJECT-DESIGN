#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h> // Provides declarations for ip header

#define PORT 9999
#define MAXLINE 2048

void read_iphdr(char *packet);
int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;

    // Create a raw socket that will listen for all incoming packets
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP); // IPPROTO_UDP to listen for only UDP packets
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));


    while (1) {
        int len, n;
        len = sizeof(cliaddr); // len is value/result
	memset(buffer, 0, sizeof(buffer));
        // Inside your while loop
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, 
        (struct sockaddr *)&cliaddr, &len);
	if (n < 0) {
	    perror("recvfrom error");
	    continue;
	}

	// Assuming IP header is 20 bytes and UDP header starts at byte 20
	int received_port = ntohs(*(unsigned short *)(buffer + 20 + 2)); 
	// Destination port is at offset 2 in the UDP header
        
        buffer[n] = '\0';
        if (received_port == PORT) {
	    printf("The total length of the packet is %d\n",n);
            printf("Received packet from %s:%d\n", 
            inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
            read_iphdr(buffer);
        }
        
    }

    close(sockfd);
    return 0;
}

void read_iphdr(char *packet){
    printf("///////// ip header info /////////\n");
    for(int i = 0; i < 20; i++){
        if(i == 0){
            printf("version: %d\n", (unsigned char)packet[i]/16);
            printf("helen: %d\n", (unsigned char)packet[i]%16);
            
        }
        else if(i == 1){
            printf("service type: %d\n", (unsigned char)packet[i]);
        }
        else if(i == 2){
            int temp;
            temp = (unsigned char)packet[2]*256 + (unsigned char)packet[3];
            printf("total length: %d\n", temp);
        }
        else if(i == 4){
            int temp;
            temp = (unsigned char)packet[4]*256 + (unsigned char)packet[5];
            printf("identification: %d\n", temp);
        }
        else if(i == 6){
            printf("flag: %d\n", (unsigned char)packet[6]/32);
            printf("offset: %d\n", ((unsigned char)packet[6]%32)*256 
            + ((unsigned char)packet[7]));
        }
        else if(i == 8){
            printf("time to live: %d\n", (unsigned char)packet[8]);
        }
        else if(i == 9){
            printf("portocal: %d\n", (unsigned char)packet[9]);
        }
        else if(i == 10){
            int temp;
            temp = (unsigned char)packet[10]*256 + (unsigned char)packet[11];
            printf("checksum: %d\n", temp);
        }
        else if(i == 12){
            printf("source ip: %d.%d.%d.%d\n", (unsigned char)packet[12],
            (unsigned char)packet[13],(unsigned char)packet[14]
            ,(unsigned char)packet[15]);
        }
        else if(i == 16){
            printf("destination ip: %d.%d.%d.%d\n", (unsigned char)packet[16],
            (unsigned char)packet[17],(unsigned char)packet[18]
            ,(unsigned char)packet[19]);
        }
    }
    printf("///////// end of ip header info /////////\n");
	
}


