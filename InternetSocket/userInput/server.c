// server.c

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  // Step 1: Create socket
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (server_socket < 0) {
    printf("Socket creation failed\n");
    return 1;
  }

  // Step 2: Create address structure
  struct sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Step 3: Bind socket
  bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

  // Step 4: Listen
  listen(server_socket, 1);

  printf("Waiting for client...\n");

  // Step 5: Accept client
  int client_socket = accept(server_socket, NULL, NULL);

  printf("Client connected!\n");

  // Step 6: Send message
  char msg[100];

  fgets(msg, sizeof(msg), stdin);

  send(client_socket, msg, strlen(msg), 0);

  printf("Message sent!\n");

  // recieve message from client
  char buffer[100];

  int bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

  buffer[bytes] = '\0';

  printf("Client says: %s\n", buffer);
  // Step 7: Close sockets
  close(client_socket);
  close(server_socket);

  return 0;
}
