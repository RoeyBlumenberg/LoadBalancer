#!/usr/bin/python2.7 -tt
from socket import *



def handle_request(currnt_socket , counter):
    response = currnt_socket.recv(1024)

    while(response.find(b"\r\n\r\n") == -1):#-1 is mean that we do not find sub string \r\n\r\n
        response += currnt_socket.recv(1024)

    response =  response.decode()
    response_array = response.split(" ")  # [GET, /counter, ...]
    if(response_array[0] != "GET") or (response_array[1] != "/counter"):
        ERROR_response = \
            """HTTP/1.1 404 Not Found
            Content-type: text/html
            Content-length: 113

            <html><head><title>Not Found</title></head><body>
            Sorry, the object you requested was not found.
            </body></html>""".encode()
        currnt_socket.send(ERROR_response)
    else:
        counter += 1
        send_response = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: "+str(len(str(counter)))+"\r\n\r\n"+str(counter)+"\r\n\r\n"
        currnt_socket.send(send_response.encode())
    print('Im here 2\n')
    return (counter)











if __name__ == '__main__':
    print('Im working\n')
    file = open("server_port", "r")
    port_number = int(file.read())
    file.close()
    socket_array = []

    for _ in range(3):
        sock = socket()
        socket_array.append(sock)

    for sock in socket_array:
        sock.connect(('localhost', port_number))

    counter = 0
    while(True):
        for sock in socket_array:
            counter = handle_request(sock , counter)


    for sock in socket_array:
        sock.close()




