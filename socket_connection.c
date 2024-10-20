#define _CRT_SECURE_NO_WARNINGS

#include "socket_connection.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define MAX_NUMBER_PORT 64000
#define MIN_NUMBER_PORT 1024
#define BACKLOG 10
#define SOCKET_ERROR -1
#define PORT_EIGHTY 80
#define LOCAL_ADDR "127.0.0.1"

void init_adder(struct sockaddr_in* addr, int port_number)
{
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = inet_addr(LOCAL_ADDR);
  addr->sin_port = htons(port_number);
  return;
}

void bind_socket(const int* ptr_socket, FILE* file_port)
{
  int port_number;
  struct sockaddr_in* service_addr = NULL;
  service_addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
  if (service_addr == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
  }

  do {
    if (rand() % 2 == 0) {
      port_number = (rand() % (MAX_NUMBER_PORT - MIN_NUMBER_PORT)) + MIN_NUMBER_PORT;
    } else {
      port_number = PORT_EIGHTY;
    }

    init_adder(service_addr, port_number);

  } while (bind(*ptr_socket, (struct sockaddr*)service_addr, sizeof(*service_addr)) == SOCKET_ERROR);

  fprintf(file_port, "%d", port_number);
  fclose(file_port);
}

void create_socket_connection(FILE* file_port, int* ptr_socket)
{
  *ptr_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  /* Intializes random number generator */
  bind_socket(ptr_socket, file_port);
  if (listen(*ptr_socket, BACKLOG) == SOCKET_ERROR) {
    printf("ERROR: Failed to listen.\n");
    exit(1);
  }
}

void accept_socket_connection(int server_socket, int* server_array)
{
  int i = 0;
  for (i = 0; i < SERVER_ARRAY_SIZE; i++) {
    server_array[i] = accept(server_socket, (struct sockaddr*)NULL, NULL);
    if (server_array[i] == 0) {
      printf("connection successful\n");
    }
  }
  return;
}
