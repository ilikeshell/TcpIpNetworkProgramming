//
// Created by kaiyan on 2022/1/6.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024
void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
        error_handling("socket() failed!");

    struct sockaddr_in target_sa;
    bzero(&target_sa, sizeof(target_sa));
    target_sa.sin_family = AF_INET;
    target_sa.sin_port = htons(atoi(argv[2]));
    target_sa.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sockfd, &target_sa, sizeof(target_sa)) == -1)
        error_handling("connect() failed!");

    char msg[BUF_SIZE];

    while(1)
    {
        fgets(msg, BUF_SIZE, stdin);
        if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
            break;

        write(sockfd, msg, strlen(msg));
        int str_len = read(sockfd, msg, BUF_SIZE - 1);
        msg[str_len] = 0;
        printf("the server says: %s", msg);
    }
    close(sockfd);
}

