#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void main() {
  struct sockaddr_in address;
  char buff[1024];
  int connections = 10;
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    perror("server_socket < 0");
    exit(3);
  }

  address.sin_family = AF_INET;
  address.sin_port = 8646;
  address.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(server_socket, (struct sockaddr *)&address, sizeof(address));
  listen(server_socket, connections);
  printf("server started in port %i\n", address.sin_port);

  while (connections) {
    int sock = accept(server_socket, NULL, NULL);
    if (sock < 0) {
      perror("sock < 0");
      exit(3);
    }

    while(connections) {
      int bytes_read = recv(server_socket, buff, 1024, 0);
      if (bytes_read < 0) break;
      send(server_socket, buff, bytes_read, 0);
    }

    close(sock);
  }
}