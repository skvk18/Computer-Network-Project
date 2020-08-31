#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5115
int main()
{
  int sd, nsd, clen;
  struct sockaddr_in server, client;
  char msg[512];
  bzero((char *)&server, sizeof(server));
  server.sin_port = htons(SERVER_PORT);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(SERVER_IP);
  sd = socket(AF_INET, SOCK_DGRAM, 0);
  bind(sd, (struct sockaddr *)&server, sizeof(server));
  clen = sizeof(client);
  while (1)
  {
    memset(msg, 0x0, 512);
    recvfrom(sd, msg, 512, 0, (struct sockaddr *)&client, &clen);
    sendto(sd, msg, strlen(msg) + 1, 0, (struct sockaddr *)&client, clen);
  }
  return 0;
}
