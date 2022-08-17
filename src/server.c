#include <server.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BACKLOG 1


static int sock_fd = -1;
static int client_sock_fd = -1;
static struct sockaddr_in client;


void server_stop(void) {
  if (sock_fd == -1) {
    printf("Attempt to close a closed socket.\n");
    return;
  }

  close(sock_fd);
  sock_fd = -1;
}


void server_send(char data[], size_t data_len) {
  static uint8_t first_transmission = 1;

  if (client_sock_fd == -1) {
    return;
  }

  if (first_transmission) {
    first_transmission = 0;
  } else {
    return;
  }

  dprintf(client_sock_fd, "HTTP/1.0 200 OK\r\n");
  dprintf(client_sock_fd, "Content-Type: text\r\n");
  dprintf(client_sock_fd, "Content-Disposition: attachment;\r\n");
  dprintf(client_sock_fd, "Content-Length: %d\r\n\r\n", data_len);
  write(client_sock_fd, data, data_len);
  write(client_sock_fd, "\r\n\r\n", 4);
}


void server_close_client(void) {
  if (client_sock_fd == -1) {
    return;
  }

  shutdown(client_sock_fd, SHUT_RDWR);
  close(client_sock_fd);
}

int server_client_wait(void) {
  size_t client_len = sizeof(client);
  client_sock_fd = accept(sock_fd, (struct sockaddr*)&client, (socklen_t*)&client_len);
  return client_sock_fd;
}


int server_start(void) {
  struct sockaddr_in server;
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_fd < 0) {
    perror("socket");
    printf("Failed to create socket!\n");
    return sock_fd;
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(80);

  int tmp;
  if ((tmp = bind(sock_fd, (struct sockaddr*)&server, sizeof(server))) < 0) {
    perror("bind");
    printf("Failed to bind socket!\n");
    close(sock_fd);
    return tmp;
  }

  return listen(sock_fd, BACKLOG);
}
