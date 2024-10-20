#define _CRT_SECURE_NO_WARNINGS

#include "http_connection.h"
#include "socket_connection.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int accept_http_connection(int http_socket_port)
{
  int socket_http_connection = accept(http_socket_port, (struct sockaddr*)NULL, NULL);
  return socket_http_connection;
}
