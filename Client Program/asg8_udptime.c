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
#define CLIENT_IP "127.0.0.2"
#define CLIENT_PORT 5137
int main()
{
    int sd,nsd,slen;
    struct sockaddr_in server,client;
    char msg[512],nmsg[512];
    bzero((char*)&client,sizeof(client));

    server.sin_port = htons(SERVER_PORT);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    client.sin_port = htons(CLIENT_PORT);
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);
    
    sd = socket(AF_INET,SOCK_DGRAM,0);
    slen = sizeof(server);
    do{
    memset(msg,0x0,512);
    memset(nmsg,0x0,512);
    printf("Insert msg : ");
    scanf("%s",msg);
    sendto(sd,msg,strlen(msg)+1,0,(struct sockaddr*)&server,slen);
    recvfrom(sd,nmsg,512,0,(struct sockaddr*)&server,&slen);
    printf("Date Time is : %s\n",nmsg);
    }while(strcmp(msg,"STOP")); 
    close(sd);
    return 0;
}
