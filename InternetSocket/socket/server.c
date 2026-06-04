// server

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // creating the socket
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (server_socket < 0) {
    printf("Socket creation failed\n");
    return 1;
  }

  // create the address structure
  struct sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // bind socket

  bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

  listen(server_socket, 1);

  printf("Waiting for client!");

  int client_socket = accept(server_socket, NULL, NULL);

  printf("Client connected!");

  char msg[] = "Hello Client!";

  send(client_socket, msg, sizeof(msg), 0);

  printf("Message sent successfully");

  // close socket

  close(server_socket);
  close(client_socket);

  return 0;
}
