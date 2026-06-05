#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int socket_server = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(3000);
  server_address.sin_addr.s_addr = INADDR_ANY;

  if (bind(socket_server, (struct sockaddr *)&server_address,
           sizeof(server_address)) < 0) {
    perror("BIND!!");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in client_address;
  socklen_t client_address_size = sizeof(client_address);

  char msg[100];

  recvfrom(socket_server, msg, sizeof(msg), 0,
           (struct sockaddr *)&client_address, &client_address_size);
  printf("[SERVER]: Client responce --> %s\n", msg);
  memset(msg, 0, sizeof(msg));
  strcpy(msg, "Hello from UDP Server");
  sendto(socket_server, msg, strlen(msg) + 1, 0,
         (struct sockaddr *)&client_address, client_address_size);

  close(socket_server);
}
