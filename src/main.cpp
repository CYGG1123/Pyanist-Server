//
// Created by 郭淳宇 on 2022/2/5.
//

#include <iostream>

#include "PicProcess.h"
#include "dataTrans.h"

using namespace std;

int main(int argc, const char *argv[]) {
    //图片处理只需要把收到的图片当作参数执行就可以了
    //所以开场应该先要建立socket，接收client端传入的图片
    socketServiceStart();

    return 0;
}
