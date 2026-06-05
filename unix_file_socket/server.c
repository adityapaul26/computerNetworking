#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/lab_socket"

int main() {
  // socket for server
  int client_socket = socket(AF_UNIX, SOCK_STREAM, 0);

  if (client_socket == -1) {
    perror("Socket creation failed");
    exit(1);
  }

  // address
  struct sockaddr_un server_address;
  server_address.sun_family = AF_UNIX;
  strcpy(server_address.sun_path, SOCKET_PATH);
  // try to make connection
  int status = connect(client_socket, (struct sockaddr *)&server_address,
                       sizeof(server_address));

  if (status == -1) {
    perror("Connection failed! Is the server running?");
    exit(1);
  }

  // read the data from server
  char buffer[100];

  read(client_socket, buffer, sizeof(buffer));
  printf("[CLIENT] Received from server: %s\n", buffer);

  // send a data to server
  char reply_msg[] = "Hello Server, I got your message!";

  write(client_socket, reply_msg, strlen(reply_msg) + 1);
  printf("Reply sent to server.\n");

  close(client_socket);
  return 0;
}
