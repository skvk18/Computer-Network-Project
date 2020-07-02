#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5115
int main()
{
    int sd, nsd, clen;
    struct sockaddr_in server, client;
    char msg[512];
    bzero((char*)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sd, (struct sockaddr *)&server, sizeof(server));
    listen(sd, 5);
    clen = sizeof(client);
    while(1)
    {
        nsd = accept(sd,(struct sockaddr*)&client, &clen);
        do{
	memset(msg, 0x0, 512);
        recv(nsd, msg, 512, 0);
        printf("\nMessage from client : %s", msg);
        printf("\nClient's IP address : %s ",inet_ntoa(client.sin_addr));
        printf("\nClient's Port number : %u\n",ntohs(client.sin_port));
	send(nsd,msg,strlen(msg)+1,0);
	}while(strcmp(msg,"STOP"));
    }
    return 0;
}
