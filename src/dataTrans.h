//
// Created by 郭淳宇 on 2022/2/6.
//

#ifndef SERVER_DATATRANS_H
#define SERVER_DATATRANS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include "getTime.h"
#include <string>
void *sendMsg(void *sock);

void *receiveMsg(void *sock);

#endif //SERVER_DATATRANS_H
