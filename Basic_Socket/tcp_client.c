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
void error_handling(char* message);

int main(int argc, char** argv) {

    /* 参数检查，需用户传入端口 */
    if(argc != 3)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }


    /* 创建套接字 */
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("Create socket error!");

    /* 正确设置服务器地址 */
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    /* 连接服务器 */
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("Connect() failed!");


    /* 循环读取数据 */
    int len, str_len = 0, index = 0;
    char buf[BUF_SIZE];
//    while( len = read(sock, &buf[index++], 1)){
//        if(len < 0)
//            error_handling("read() failed!");
//        str_len += len;
//    }
    len = read(sock, buf, BUF_SIZE);
    if(len < 0)
        error_handling("read() failed!\n");

    printf("Message from server: %s \n", buf);
    //printf("Function read() call count: %d\n", str_len);
    close(sock);

    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
