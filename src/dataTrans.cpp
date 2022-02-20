#include "dataTrans.h"

using namespace std;

struct PacketHeader {
    int size;            // 大小：字节
    PacketHeader() {
        size = 0;
    }
};

void *receiveMsg(void *sock) {
    // system("pwd");
    char buffer[1024];
    int *socket = (int *) sock;
    while (1) {
        usleep(500);
        int nRecv = recv(*socket, buffer, 1024, 0);
        if (nRecv <= 0) {
            continue;
        } else if (nRecv == sizeof(PacketHeader)) {
            PacketHeader ph;
            memcpy(&ph, buffer, nRecv);
            cout << "大小：" << ph.size << "Bytes" << endl;
            string filename = ("../Received/" + getCurrentTime() + ".jpg");
            FILE *fp = fopen(filename.c_str(), "wb");
            if (fp == NULL) {
                cout << "file not found" << endl;
            }
            cout << "开始接收图片" << endl;
            nRecv = 0;
            while (nRecv < ph.size) {
                memset(buffer, 0, sizeof(buffer));
                int byteCount = recv(*socket, buffer, 1024, 0);
                if (byteCount <= 0) {
                    continue;
                }
                fwrite(buffer, 1, byteCount, fp);
                nRecv += byteCount;
                cout << "已接收 " << nRecv << " Bytes" << endl;
            }
            cout << "共接收 " << nRecv << " Bytes" << endl;
            fclose(fp);
        } else {
            buffer[nRecv] = '\0';
            cout << buffer << endl;
        }
    }
    close(*socket);
    // string command = "python3 PaddleOCR.py " + filename;
    // system(command.c_str());
}

void *sendMsg(void *sock) {
    while (1) {
        usleep(500);
        char buffer[1024];
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