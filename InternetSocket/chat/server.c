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

  // communication loop

  char msg[100];
  char buffer[100];

  while (1) {
    // send
    fgets(msg, sizeof(msg), stdin);

    send(client_socket, msg, strlen(msg), 0);

    if (strncmp(msg, "bye", 3) == 0) {
      printf("Chat ended.\n");
      close(server_socket);
      close(client_socket);

      return 0;
    }

    // recieve
    memset(buffer, 0, sizeof(buffer));

    int bytes = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes <= 0) {
      printf("Client disconnected");
      break;
    }
    buffer[bytes] = '\0';

    printf("Client:%s", buffer);

    // check if client wants to quit
    if (strncmp(buffer, "bye", 3) == 0) {
      printf("Client ended the chat.\n");

      break;
    }
  }
  close(client_socket);
  return 0;
}
