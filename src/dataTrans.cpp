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

using namespace std;

void *receiveMsg(void *sock) {
    system("pwd");
    FILE *fp = fopen(("../Received/" + getCurrentTime() + ".jpg").c_str(), "wb");
    if (fp == NULL) {
        cout << "file not found" << endl;
    }

    char buffer[4096];
    int *socket = (int *) sock;
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t byteCount = recv(*socket, buffer, 4096, 0);
        if (byteCount <= 0) {
            continue;
        }
        fwrite(buffer, 1, byteCount, fp);
    }
}

void *sendMsg(void *sock) {
    while (1) {
        usleep(500);
        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));
        cin >> buffer;
        if (strlen(buffer) < 0) {
            continue;
        }
        ssize_t byteCount = send(*(int *) sock, buffer, 4096, 0);
        if (byteCount < 0) {
            cout << "send failed" << endl;
        }
    }
}