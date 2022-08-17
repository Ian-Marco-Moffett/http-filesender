#ifndef SERVER_H
#define SERVER_H

#include <stddef.h>


int server_start(void);
void server_stop(void);
void server_close_client(void);
int server_client_wait(void);   // Waits for client to connect.
void server_send(char data[], size_t data_len);

#endif
