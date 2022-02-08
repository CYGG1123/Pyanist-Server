//
// Created by 郭淳宇 on 2022/2/8.
//

#include "getTime.h"

using namespace std;

string getCurrentTime() {
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d-%X", localtime(&t));
    return tmp;
}