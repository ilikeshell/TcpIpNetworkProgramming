//
// Created by kaiyan on 2022/1/5.
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

int main(int argc, char *argv[])
{
    char message[BUF_SIZE];
    /** 检查参数 */
    if(argc != 3){
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

   // signal(SIGINT, error_handling);
    /** 创建UDP套接字*/
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
        error_handling("socket() failed!");

    /** 设置套接字地址 */
    struct sockaddr_in serv_sa, from_sa;
    bzero(&serv_sa, sizeof(serv_sa));
    serv_sa.sin_family = AF_INET;
    serv_sa.sin_port = htons(atoi(argv[2]));
    serv_sa.sin_addr.s_addr = inet_addr(argv[1]);


    /** 发送并接收数据 */
    while(1){
        fputs("Insert message (q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&serv_sa, sizeof(serv_sa));

        int adr_sz = sizeof(from_sa);
        int str_len = recvfrom(sockfd, message, BUF_SIZE, 0, (struct sockaddr*)&from_sa, &adr_sz);
        message[str_len] = 0;
        printf("Message from server says: %s", message);

    }

    close(sockfd);
    return 0;
}
