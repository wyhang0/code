#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

void server(int argc, char* argv[]);

void client(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    client(argc, argv);

    return 0;
}

void server(int argc, char* argv[])
{
    if(argc != 2){
        fprintf(stderr, "%s usage:\n", argv[0]);
        fprintf(stderr, "%s  [port]\n", argv[0]);
        return;
    }
    int port = atoi(argv[1]);
    if(port == 0){
        fprintf(stderr, "%s not a number\n", argv[1]);
        return;
    }
    int fd;
    if(-1 == (fd = socket(AF_INET, SOCK_DGRAM, 0))){
        fprintf(stderr, "create socket error\n");
        return;
    }
    sockaddr_in server, client;
    socklen_t addrLen = sizeof(sockaddr);
    bzero(&server, addrLen);
    bzero(&client, addrLen);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);
    if(-1 == (bind(fd, (sockaddr*)&server, addrLen))){
        perror("bind error\n");
        close(fd);
        return;
    }
    char recv_buf[15];
    int recvnum;
    while(true){
        if(-1 == (recvnum = recvfrom(fd, recv_buf, sizeof(recv_buf), 0, (sockaddr*)&client, &addrLen)))
        {
            perror("recvfrom error\n");
            close(fd);
            return;
        }
        printf("%s:%d->%s\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), recv_buf);

        if(-1 == (sendto(fd, recv_buf, sizeof(recv_buf), 0, (sockaddr*)&client, addrLen))){
            perror("sendto error\n");
        }

        if(strcmp(recv_buf, "q\n") == 0){
            break;
        }
    }
    close(fd);
}

void client(int argc, char* argv[])
{
    if(argc != 3){
        fprintf(stderr, "%s usage:\n", argv[0]);
        fprintf(stderr, "%s [address] [port]\n", argv[0]);
        return;
    }
    int port = atoi(argv[2]);
    if(port == 0){
        fprintf(stderr, "%s not a number\n", argv[2]);
        return;
    }
    int fd;
    if(-1 == (fd = socket(AF_INET, SOCK_DGRAM, 0))){
        fprintf(stderr, "create socket error\n");
        return;
    }
    sockaddr_in server, client;
    socklen_t addrLen = sizeof(sockaddr);
    bzero(&server, addrLen);
    bzero(&client, addrLen);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(port);

    char send_buf[15];
    char recv_buf[15];
    while(true){
        fgets(send_buf, sizeof(send_buf), stdin);
        if(-1 == (sendto(fd, send_buf, sizeof(send_buf), 0, (sockaddr*)&server, addrLen)))
        {
            perror("sendto error\n");
            close(fd);
            return;
        }

        if(-1 == (recvfrom(fd, recv_buf, sizeof(recv_buf), 0, (sockaddr*)&server, &addrLen)))
        {
            perror("recvfrom error\n");
        }
        printf("%s:%d->%s\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port), recv_buf);

        if(strcmp(send_buf, "q\n") == 0){
            break;
        }
    }
    close(fd);
}

