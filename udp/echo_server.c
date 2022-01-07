//
// Created by kaiyan on 2022/1/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
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
    /** 检查参数 */
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    char recv_buf[BUF_SIZE];
    char send_buf[BUF_SIZE];
    socklen_t clnt_adr_sz;
    int str_len;

    //signal(SIGINT, error_handling);

    /** 创建UDP套接字*/
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
        error_handling("socket() failed!");

    /** 设置套接字地址 */
    struct sockaddr_in serv_sa, clnt_sa;
    bzero(&serv_sa, sizeof(serv_sa));
    serv_sa.sin_family = AF_INET;
    serv_sa.sin_port = htons(atoi(argv[1]));
    serv_sa.sin_addr.s_addr = htonl(INADDR_ANY);

    /** 绑定套接字地址 */
    if((bind(sockfd, (struct sockaddr*)&serv_sa, sizeof(serv_sa))) == -1)
        error_handling("bind() failed!");

    /** 循环接收数据，并回应 */
    while(1){
        clnt_adr_sz = sizeof(clnt_sa);
        str_len = recvfrom(sockfd, recv_buf, BUF_SIZE, 0, (struct sockaddr*)&clnt_sa, &clnt_adr_sz);
        recv_buf[str_len] = 0;
        printf("Message from client says: %s", recv_buf);
        sprintf(send_buf, "hello, %s", recv_buf);
        sendto(sockfd, send_buf, strlen(send_buf), 0, (struct sockaddr*)&clnt_sa, clnt_adr_sz);
    }

    close(sockfd);
    return 0;
}
