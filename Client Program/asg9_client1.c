#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define CLIENT_IP "128.0.0.2"
#define SERVER_PORT 5115
#define CLIENT_PORT 7502

int main(){
    int sd, nsd, slen,sd1;
    struct sockaddr_in server, client;
    char msg[512],nmsg[512];
    bzero((char*)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    
    bzero((char*)&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    slen = sizeof(server);
    connect(sd, (struct sockaddr*)&server, slen);
    do{
    printf("\nEnter a message : ");
    scanf("%s", msg);
    send(sd, msg, strlen(msg)+1, 0);
    memset(nmsg,0x0,512);
    recv(sd,nmsg,512,0);
    printf("Echo MSG is : %s\n",nmsg);
    }while(strcmp(msg,"STOP"));
    close(sd);
    return 0;
}
