#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<time.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5115
int main()
{
    int sd, nsd, clen;
    time_t t;
    struct sockaddr_in server,client;
    char msg[512],*dtm;
    bzero((char*)&server,sizeof(server));
    server.sin_port = htons(SERVER_PORT);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    sd = socket(AF_INET,SOCK_DGRAM,0);
    bind(sd,(struct sockaddr*)&server,sizeof(server));
    clen = sizeof(client);
    while(1)
    {
	memset(msg, 0x0, 512);
	recvfrom(sd,msg,512,0,(struct sockaddr*)&client,&clen);
        t = time(NULL);
        if((strcmp(msg,"date")==0) || (strcmp(msg,"time")==0))
        	dtm = ctime(&t);
        else
        	strcpy(dtm,"Wrong Command"); 
	sendto(sd,dtm,strlen(dtm)+1,0,(struct sockaddr*)&client,clen);
    }
    return 0;
}
