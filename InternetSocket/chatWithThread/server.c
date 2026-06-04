#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int server_socket, client_socket;
pthread_t send_tid, recv_tid;

void *send_msg(void *arg) {
  char msg[100];

  while (1) {
    fgets(msg, sizeof(msg), stdin);

    send(client_socket, msg, strlen(msg), 0);

    if (strncmp(msg, "bye", 3) == 0) {
      printf("Chat ended.\n");

      close(client_socket);
      close(server_socket);

      exit(0);
    }
  }

  return NULL;
}

void *recv_msg(void *arg) {
  char msg[100];

  while (1) {
    memset(msg, 0, sizeof(msg));

    int bytes = recv(client_socket, msg, sizeof(msg) - 1, 0);

    if (bytes <= 0) {
      printf("\nClient disconnected.\n");

      close(client_socket);
      close(server_socket);

      exit(0);
    }

    msg[bytes] = '\0';

    printf("\nClient: %s", msg);

    if (strncmp(msg, "bye", 3) == 0) {
      printf("Chat ended.\n");

      close(client_socket);
      close(server_socket);

      exit(0);
    }
  }

  return NULL;
}

int main() {
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (server_socket < 0) {
    perror("Socket");
    return 1;
  }

  struct sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_socket, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) < 0) {
    perror("Bind");
    return 1;
  }

  if (listen(server_socket, 5) < 0) {
    perror("Listen");
    return 1;
  }

  printf("Waiting for client...\n");

  client_socket = accept(server_socket, NULL, NULL);

  if (client_socket < 0) {
    perror("Accept");
    return 1;
  }

  printf("Client Connected!\n");

  pthread_create(&send_tid, NULL, send_msg, NULL);

  pthread_create(&recv_tid, NULL, recv_msg, NULL);

  pthread_join(send_tid, NULL);
  pthread_join(recv_tid, NULL);

  close(client_socket);
  close(server_socket);

  return 0;
}
