#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int shr_transfer(int socket, const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("[-] Error in reading file");
        return -1;
    }

    char buffer[1024];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (send(socket, buffer, bytes_read, 0) < 0) {
            perror("[-] Failed to send file");
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return 0;
}

int server(char *ip_addr)
{
    // Server IP and Port
    //char *server_ip = "127.0.0.1";
    int port = 42069;

    // File descriptors and return value
    int server_fd, client_fd, ret;
    socklen_t addr_size;
    char buffer[1024];

    // Server and Client address structures
    struct sockaddr_in server_addr, client_addr;

    // Create a TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("[-] Failed to create socket");
        exit(EXIT_FAILURE);
    }
    printf("[+] TCP server socket created.\n");

    // Set the server address and port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);
    server_addr.sin_port = port;
    
    // Bind the socket to the server address
    ret = bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret < 0) {
        perror("[-] Failed to bind socket");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("[+] Bind to port number: %d\n", port);

    // Start listening on the socket
    if (listen(server_fd, 5) < 0) {
        perror("[-] Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Listening...\n");
 
    // Server loop to accept clients
    while(1) {
        addr_size = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);
        if (client_fd < 0) {
            perror("[-] Accept failed");
            continue;
        }
        printf("[+] Client connected.\n");
    
        memset(buffer, 0, sizeof(buffer));
        
        // Receive data from the client
        ret = recv(client_fd, buffer, sizeof(buffer), 0);
        if (ret <= 0) {
            if (ret == 0) {
                printf("Client disconnected.\n");
            } else {
                perror("[-] Failed to receive data");
            }
            close(client_fd);
            continue;
        }

        printf("Client: %s\n", buffer);
    
        // Prepare the server's message
        memset(buffer, 0, sizeof(buffer));
        strcpy(buffer, "Welcome to the TCP server!\n");
        printf("Server: %s\n", buffer);

        // Send the server's message to the client
        if (send(client_fd, buffer, strlen(buffer), 0) < 0) {
            perror("[-] Send failed");
        }
    
        // Close the client socket after sending the message
        close(client_fd);
        printf("[+] Client disconnected.\n\n");
    }
  
  return 0;
}
