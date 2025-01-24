//
// Created by Administrator on 2024/4/8.
//

#include <chrono>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Utils.h"

void Utils::writeTextFile(const string &path, const string &text) {
    std::ofstream outfile(path);
    if (!outfile.is_open()) {
        //std::cerr << "无法打开文件：" << path << std::endl;
        throw "can not open file:" + path;
        return;
    }
    outfile << text;
    outfile.close();
    std::cout << "文件写入成功：" << path << std::endl;
}

string Utils::readTextFile(const string &path) {
    std::ifstream infile(path);
    if (!infile.is_open()) {
        std::cerr << "无法打开文件：" << path << std::endl;
        throw "can not open file:" + path;
    }
    std::string content;
    std::string line;
    while (std::getline(infile, line)) {
        content += line + "\n";
    }
    infile.close();
    return content;
}


string Utils::getLine() {
    string s;
    getline(cin, s, '\n');   // 遇到换行符结束
    return s;
}

string Utils::getLine(const string &hint) {
    cout << hint;
    return getLine();
}


