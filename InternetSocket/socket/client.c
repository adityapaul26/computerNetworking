// client

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // create the socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (client_socket < 0) {
    printf("Socket creation failed!");
    return 1;
  }

  // address
  struct sockaddr_in socket_addr;
  socket_addr.sin_family = AF_INET;
  socket_addr.sin_port = htons(8080);
  socket_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(client_socket, (struct sockaddr *)&socket_addr, sizeof(socket_addr));

  char buffer[100];

  int bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

  buffer[bytes] = '\0';

  printf("Server says:%s\n", buffer);

  close(client_socket);

  return 0;
}
