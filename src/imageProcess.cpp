//
// Created by ElderBacon on 2022/2/5.
//
#include "imageProcess.h"

string imageProcess(const string &filename) {
   char result[1024];
   // system("pwd");
   // executeCMD(("python3 ../src/imageProcess.py -HelloWorld"), result);
   executeCMD(("python3 ../src/imageProcess.py " + string(filename)).c_str(), result);


   string str;
   //字符串处理有点问题
   for (int i = 0; i < sizeof(result); ++i) {
       if (result[i] == '\0') {
           break;
       } else if ((result[i] >= 'A' && result[i] <= 'Z') ||
                  (result[i] >= 'a' && result[i] <= 'z') ||
                  result[i] >= '0' && result[i] <= '7') {
           str.push_back(result[i]); //提取出来所有乐谱的成分
       } else {
           continue;
       }
   }
   return str;
    // return "HelloWorld";
}