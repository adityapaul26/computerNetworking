#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/lab_socket"

int main() {
  char msg[100];
  strcpy(msg, "lightangel");

  // server
  int server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
  if (server_socket == -1) {
    perror("Socket creation failed");
    exit(1);
  }

  // address
  struct sockaddr_un socket_address;
  socket_address.sun_family = AF_UNIX;
  strcpy(socket_address.sun_path, SOCKET_PATH);

  unlink(SOCKET_PATH);

  int bind_status = bind(server_socket, (struct sockaddr *)&socket_address,
                         sizeof(socket_address));

  if (bind_status == -1) {
    perror("Bind failed!");
    exit(1);
  }

  listen(server_socket, 5);

  printf("Server is listening on %s..\n", SOCKET_PATH);

  int client_socket = accept(server_socket, NULL, NULL);

  if (client_socket == -1) {
    perror("Accept failed!");
    exit(1);
  }

  char reply_buffer[100];

  int byte_write = write(client_socket, msg, strlen(msg) + 1);
  int bytes_read = read(client_socket, reply_buffer, sizeof(reply_buffer));

  if (bytes_read > 0) {
    printf("[SERVER] Client replied: %s\n", reply_buffer);
  }

  close(server_socket);
  close(client_socket);
  unlink(SOCKET_PATH);

  return 0;
}
