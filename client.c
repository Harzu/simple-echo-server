#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void main() {
  char message[] = "Hello server";
  int mess_len = sizeof(message);
  char buff[mess_len];
  struct sockaddr_in addr;
  int client = socket(AF_INET, SOCK_STREAM, 0);
  if (client < 0) {
    perror("Not client sockets");
    exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = 8646;
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (connect(client, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("Not client connection");
    exit(2);
  }

  send(client, *message, mess_len, 0);
  recv(client, buff, mess_len, 0);

  printf("%i\n", sizeof(buff));
  close(client);
}