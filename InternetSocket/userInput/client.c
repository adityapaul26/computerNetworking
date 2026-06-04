// client.c

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  // Step 1: Create socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Step 2: Server address
  struct sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);

  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Step 3: Connect
  connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

  // Step 4: Receive message
  char buffer[100];

  int bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

  buffer[bytes] = '\0';

  printf("Server says: %s\n", buffer);
  char msg[100];
  fgets(msg, sizeof(msg), stdin);

  send(client_socket, msg, strlen(msg), 0);
  // Step 5: Close
  close(client_socket);

  return 0;
}
