//
// Created by Administrator on 2024/4/8.
//
#include "string"
#include <iostream>
#include <cerrno> // 用于获取错误代码
#include <cstring> // 用于获取错误消息
#include <io.h>
#include <vector>
#include <sstream>
#include <direct.h>

using  namespace  std;

#ifndef MY_APPLICATION_UTILS_H
#define MY_APPLICATION_UTILS_H

#define INFO() string(const_cast<char*>(__FILE__))+"@"+to_string(__LINE__)

class Utils {
public:
    static const char kPathSeparator =
#ifdef _WIN32
            '\\';
#else
    '/';
#endif


    ///从控制台读取一行
    static string getLine();
    static string getLine(const string& hint);

    ///向路径为 path的文件写入字符串text
    /// \param path 文件路径
    /// \param text 要写入的字符串
    static void writeTextFile(const string &path, const string &text);

    /// 读取路径为 path的文件
    /// \param path 文件路径
    /// \return 文件里面的文本
    static string readTextFile(const string &path);
    static void removeFile(const string& filePath){
        remove(filePath.c_str());
    }


    static std::vector<std::string> splitStringByNewLine(const std::string &str) {
        return splitString(str, '\n');
    }

    static std::vector<std::string> splitString(const std::string &str, char delim='\n') {
        std::vector<std::string> lines;
        std::istringstream iss(str);
        std::string line;
        while (std::getline(iss, line, delim)) {
            lines.push_back(line);
        }
        return lines;
    }
     static std::string& removeSubstring(std::string& str, const std::string& toRemove) {
            size_t pos = str.find(toRemove);
            if (pos != std::string::npos) {
                str.erase(pos, toRemove.length());
            }
         return str;
     }
     static bool isContain(const vector<string>& list,const string& key){
         for (const auto &i: list)
             if (i == key) {
                 return true;
             }


         return false;
    }
    static vector<string> getArguments(){
        return splitString(getLine(">>>"), ' ');
    }


private:
    Utils() = default;
};



#endif //MY_APPLICATION_UTILS_H
