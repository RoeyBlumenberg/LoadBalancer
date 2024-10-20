all: lb
.PHONY : all

CC = gcc
CFLAGS = -g -Wall

ex3_lb: ex3_lb.c socket_connection.c http_connection.c
	$(CC) $(CFLAGS) -o ex3_lb ex3_lb.c ocket_connection.c http_connection.c


.PHONY : clean
clean:
	\rm ex3_lb || true
	\rm http_port || true
	\rm server_port || true

tidycode:
	clang-format -i *.c *.h
