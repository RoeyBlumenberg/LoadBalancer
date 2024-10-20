#ifndef SOCKET_CONNECTION_H
#define SOCKET_CONNECTION_H
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#define SERVER_ARRAY_SIZE 3

void create_socket_connection(FILE* file_port, int* ptr_socket);
void accept_socket_connection(int server_socket, int* server_array);

#endif
