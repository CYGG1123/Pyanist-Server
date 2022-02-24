#include "dataTrans.h"

#include <utility>

using namespace std;

struct PacketHeader {
    int size;            // 大小：字节
    PacketHeader() {
        size = 0;
    }
};

struct sendMsgPacket {  //pthread_create创建线程只能接受一个void*参数，所以这里用struct打包一下
    int sock;    //参数1
    string msg; //参数2

    sendMsgPacket(int socket, string b) {
        sock = socket;
        msg = std::move(b);
    };

    sendMsgPacket(int socket) {
        sock = socket;
        msg = "HelloWorld";
    };
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
            cout << "图片接收完毕" << endl;
            //创建发送线程
            pthread_t sendThread;
            cout << "创建发送线程" << endl;
            //sendMsgPacket Pac(*socket, imageProcess(filename));

            //错在这里了
            //sendMsgPacket Pac(*socket, (string &) "imageProcess(filename)");
            sendMsgPacket Pac(*socket, imageProcess(filename));
            cout << "打包成功，创建发送线程成功" << endl;
            pthread_create(&sendThread, NULL, sendMsg, &Pac);
            pthread_join(sendThread, NULL);

        } else {
            buffer[nRecv] = '\0';
            cout << buffer << endl;
        }
    }
}

void *sendMsg(void *arg) {
    sendMsgPacket *destructor;
    destructor = (struct sendMsgPacket *) arg;
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    memcpy(buffer, destructor->msg.c_str(), destructor->msg.size());
    // cout << "发送消息：" << buffer << endl; 到这里没问题
    usleep(500);
    ssize_t byteCount = send(destructor->sock, buffer, 1024, 0);
    if (byteCount < 0) {
        cout << "send failed" << endl;
    }
}