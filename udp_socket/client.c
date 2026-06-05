#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int socket_client = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(3000);

  // server_address.sin_addr.s_addr = inet_addr("192.168.29.213");
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

  char msg[100];

  strcpy(msg, "Hello from UDP Client");
  sendto(socket_client, msg, strlen(msg) + 1, 0,
         (struct sockaddr *)&server_address, (socklen_t)sizeof(server_address));
  memset(msg, 0, sizeof(msg));
  socklen_t server_address_size = sizeof(server_address);
  recvfrom(socket_client, msg, sizeof(msg), 0,
           (struct sockaddr *)&server_address, &server_address_size);
  printf("[CLIENT]: Server responce --> %s\n", msg);

  close(socket_client);
}
