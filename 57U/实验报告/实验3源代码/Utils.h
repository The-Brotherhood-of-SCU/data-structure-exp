//
// Created by Administrator on 2024/11/14.
//

#ifndef EXP3_UTILS_H
#define EXP3_UTILS_H
#define byte char

#include <vector>
#include <fstream>
#include "string"
#include "iostream"
using namespace std;
class Utils {
private:

public:
    Utils()=delete;
    static string getLine() {
        string s;
        getline(cin, s, '\n');   // 遇到换行符结束
        return s;
    }
    static string getLine(const string &hint) {
        cout << hint;
        return getLine();
    }
    static std::vector<byte> readFile(const std::string& filePath) {
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "无法打开文件: " << filePath << std::endl;
            return std::vector<byte>();
        }

        std::vector<byte> content((std::istreambuf_iterator<byte>(file)), std::istreambuf_iterator<byte>());
        file.close();
        return content;
    }
    static bool writeFile(const std::string& filePath, const std::vector<char>& content) {
        std::ofstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "无法打开文件: " << filePath << " 进行写入。" << std::endl;
            return false;
        }

        file.write(content.data(), content.size());
        file.close();
        return true;
    }

};


#endif //EXP3_UTILS_H
