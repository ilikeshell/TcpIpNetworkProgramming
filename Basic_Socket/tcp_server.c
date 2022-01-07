#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

void error_handling(char* message);

int main(int argc, char** argv) {

    /* 参数检查，需用户传入端口 */
    if(argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char msg[] = "Hello,World!";

    /* 创建套接字 */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("Create socket error!");

    /* 正确设置套接字地址的各种值 */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* 为套接字分配"电话号码" */
    if((bind(serv_sock, (struct sockaddr* )(&serv_addr), sizeof(serv_addr))) == -1)
        error_handling("bind server address failed! ");

    /* 套接字转化为可接收连接状态 */
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() failed!");


    /* 受理对方连接请求,clnt_addr_size返回实际soket地址长度 */
    clnt_sock = accept(serv_sock, (struct sockaddr*)(&clnt_addr), &clnt_addr_size);
    if(clnt_sock == -1)
        error_handling("accept() failed!");

    /* 向对方传输数据 */
    //write(clnt_sock, msg, sizeof(msg));
    printf("the length of string is : %lu.\n", strlen(msg));
    for (int i = 0; i < strlen(msg); ++i) {
        sleep(1);
        write(clnt_sock, &msg[i], 1);
    }
    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}