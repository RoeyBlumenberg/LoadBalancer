#define _CRT_SECURE_NO_WARNINGS

#include "http_connection.h"
#include "socket_connection.h"
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define HTTP_MESSAGE 1
#define SERVER_MESSAGE 2

bool is_recieved_whole_massage(const int* size_buffer_massage, char* buffer_massage, int message_type)
{
  *(buffer_massage + *size_buffer_massage) = '\0';
  char* ptr_first_occurence = NULL;
  if (message_type == HTTP_MESSAGE) {
    if (strstr(buffer_massage, "\r\n\r\n")) {

      return true;
    }
  }
  if (message_type == SERVER_MESSAGE) {
    if ((ptr_first_occurence = strstr(buffer_massage, "\r\n\r\n")) != NULL) {
      // the strstr function look at four chars after the first occurence.
      if (strstr((ptr_first_occurence + strlen("\r\n\r\n")), "\r\n\r\n") != NULL) {
        return true;
      }
    }
  }
  return false;
}

bool need_to_realloc(int size_buffer_massage, int capacity)
{
  if (capacity - size_buffer_massage < BUFFER_SIZE) {
    return true;
  } else {
    return false;
  }
}

char* recieve_message(int socket_massege, int* size_buffer_massage, int message_type)
{
  char* buffer_massage = NULL;

  buffer_massage = (char*)malloc(BUFFER_SIZE * sizeof(char) + 1);
  if (buffer_massage == NULL) {
    printf("Error allocate\n");
    exit(1);
  }

  int capacity = BUFFER_SIZE;

  while (true) {
    *size_buffer_massage += recv(socket_massege, &buffer_massage[*size_buffer_massage], BUFFER_SIZE, 0);

    if (is_recieved_whole_massage(size_buffer_massage, buffer_massage, message_type)) {
      break;
    }

    if (need_to_realloc(*size_buffer_massage, capacity)) {
      capacity += capacity;
      buffer_massage = realloc(buffer_massage, capacity + 1);
    }
  }

  return buffer_massage;
}

void handle_requests(int http_socket, int* socket_array)
{
  char* clinet_buffer_massage;
  char* server_buffer_massage;
  int flags = 0;
  int server_index = 0;
  while (true) {
    int size_buffer_massage = 0;
    int socket_http_massege = accept_http_connection(http_socket);
    clinet_buffer_massage = recieve_message(socket_http_massege, &size_buffer_massage, HTTP_MESSAGE);
    send(socket_array[server_index], clinet_buffer_massage, strlen(clinet_buffer_massage), flags);
    size_buffer_massage = 0;
    free(clinet_buffer_massage);
    server_buffer_massage = recieve_message(socket_array[server_index], &size_buffer_massage, SERVER_MESSAGE);
    send(socket_http_massege, server_buffer_massage, strlen(server_buffer_massage), flags);
    free(server_buffer_massage);

    server_index++;
    server_index = server_index % SERVER_ARRAY_SIZE;
  }
}

int main()
{
  FILE* file_server_port = fopen("server_port", "w");
  FILE* file_http_port = fopen("http_port", "w");
  int server_socket, http_socket;
  int server_array[SERVER_ARRAY_SIZE] = {0};

  srand((unsigned)time(0));
  create_socket_connection(file_server_port, &server_socket);
  create_socket_connection(file_http_port, &http_socket);

  accept_socket_connection(server_socket, server_array);

  handle_requests(http_socket, server_array);
}