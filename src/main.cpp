#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include "dataTrans.h"
#include "getTime.h"

using namespace std;

int main()
{
    cout << getCurrentTime() << ": Server is running..." << endl;
    pthread_t sendPthread;
    pthread_t recvPthread;

    in_port_t servPort = 7777;
    int servSock;
    if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) //创建socket
    {
        cout << "socket error" << endl;
    }

    struct sockaddr_in servAddr;
    memset(&servAddr, '\0', sizeof(struct sockaddr_in));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //让系统自动填充地址，不用自己去查明本机的地址是多少
    servAddr.sin_port = htons(servPort);

    if (::bind(servSock, (struct sockaddr *)&servAddr, sizeof(struct sockaddr_in)) < 0) //绑定端口
    {
        cout << "bind error" << endl;
    }
    //    if (bind(servSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) //把套接字绑定到指定的地址与端口
    //    {
    //        cout << "bind error" << endl;
    //    }

    if (listen(servSock, 5) < 0) //开始监听，等待客户端的连接，listen调用之前，客户端无法连接到服务端，第二个参数为最大连接数
    {
        cout << "listen filed" << endl;
    }

    struct sockaddr_in clntAddr;
    socklen_t clntAddrLen = sizeof(clntAddr);
    int clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &clntAddrLen);

    if (clntSock < 0)
    {
        cout << "accept error" << endl;
    }

    char clntName[1024];
    if (inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL)
    {
        cout << "Handling client: " << clntName << " port: " << ntohs(clntAddr.sin_port) << endl;
        ;
    }
    else
    {
        cout << "client address get failed " << endl;
    }

    pthread_create(&sendPthread, NULL, sendMsg, &clntSock);
    pthread_create(&recvPthread, NULL, receiveMsg, &clntSock);
    pthread_join(sendPthread, 0);
    pthread_join(recvPthread, 0);
}