//
// Created by kaiyan on 2022/1/6.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 32

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char **argv)
{
    /** 检查参数数量 */
    if(argc != 2){
        printf("Usage: %s <port>", argv[0]);
        exit(1);
    }
    /** 创建socket */
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
        error_handling("socket() failed!");

    /** 初始化socket地址*/
    struct sockaddr_in local_addr;
    bzero(&local_addr, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1]));
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /** 绑定socket地址 */
    if(bind(sockfd, (struct sockaddr*)&local_addr, sizeof(local_addr)) == -1)
        error_handling("bind() failed!");

    /** 循环接收数据 */
    for (int i = 0; i < 4; ++i) {
        char message[BUF_SIZE];
        struct sockaddr_in from_addr;
        socklen_t from_addr_len = sizeof(from_addr);

        sleep(5);

        int str_len = recvfrom(sockfd, message, BUF_SIZE, 0, (struct sockaddr*)&from_addr, &from_addr_len);

        if(str_len == -1)
            error_handling("recvfrom() failed!");
        else
            message[str_len] = 0;

        printf("Message: %d: %s \n", i + 1, message);
    }
    /** 关闭套接字并返回 */
    close(sockfd);
    return 0;
}
