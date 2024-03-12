#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void send_tcp_message(const char *server_ip, int port, const char *file_path) {
    int sock;
    struct sockaddr_in serv_addr;
    FILE *file;
    char *buffer;
    long file_size;

    // Open file
    file = fopen(file_path, "rb"); // Open in binary mode for compatibility
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for file content
    buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read file into buffer
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Null-terminate the buffer

    // Close the file
    fclose(file);

    // Create the socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        close(sock);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    // Send the file contents
    send(sock, buffer, file_size, 0);
    printf("File content sent.\n");

    // Free the buffer and close the socket
    free(buffer);
    close(sock);
}

int main() {
    // Example usage
    send_tcp_message("192.168.19.135", 8082, "/home/eason/Documents/target");
    return 0;
}

