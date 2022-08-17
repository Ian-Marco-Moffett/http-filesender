#include <content.h>
#include <server.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void cleanup(void) {
  server_stop();
}


int send_data(char* file_content, size_t file_content_size) {
  atexit(cleanup);

  printf("Waiting for connection..\n");
  
  int tmp = server_start();

  if (tmp < 0) {
    return tmp;
  }

  server_client_wait();
  printf("Connected!\n");

  server_send(file_content, file_content_size);

  printf("When ready, press CTRL-C to close the connection!\n");
  pause();
  printf("Connection closed!\n");
  server_close_client();

  return 0;
}
