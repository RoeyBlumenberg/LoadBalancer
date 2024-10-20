#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H
#include <netinet/in.h>
#include <sys/socket.h>

int accept_http_connection(int http_socket);

#endif