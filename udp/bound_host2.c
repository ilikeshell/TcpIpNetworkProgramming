//
// Created by kaiyan on 2022/1/6.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 32

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char **argv)
{
    char* msg1 = "Hi!";
    char* msg2 = "I'm another UDP HOST.";
    char* msg3 = "Nice to meet you!";
    char* msg4 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";

    /** 检查参数数量 */
    if(argc != 3){
        printf("Usage: %s <IP> <port>", argv[0]);
        exit(1);
    }

    /** 创建socket */
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
        error_handling("socket() failed!");

    /** 初始化目标socket地址*/
    struct sockaddr_in target_addr;
    bzero(&target_addr, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(atoi(argv[2]));
    target_addr.sin_addr.s_addr = inet_addr(argv[1]);

    /** 发送三次数据 */
    sendto(sockfd, msg1, strlen(msg1),0, (struct sockaddr*)&target_addr, sizeof(target_addr));
    sendto(sockfd, msg2, strlen(msg2),0, (struct sockaddr*)&target_addr, sizeof(target_addr));
    sendto(sockfd, msg3, strlen(msg3),0, (struct sockaddr*)&target_addr, sizeof(target_addr));
    sendto(sockfd, msg4, strlen(msg4),0, (struct sockaddr*)&target_addr, sizeof(target_addr));
    /** 关闭套接字并返回 */
    close(sockfd);
    return 0;
}
