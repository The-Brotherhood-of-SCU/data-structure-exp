//
// Created by Administrator on 2024/11/14.
//

#ifndef EXP4_UTILS_H
#define EXP4_UTILS_H
#define byte char

#include <vector>
#include <fstream>
#include <sstream>
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
    static string readFile(const std::string& filePath) {
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "无法打开文件: " << filePath << std::endl;
            return "";
        }

        return std::string((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
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
    static std::vector<std::string> splitString(const std::string &str, char delim='\n') {
        std::vector<std::string> lines;
        std::istringstream iss(str);
        std::string line;
        while (std::getline(iss, line, delim)) {
            lines.push_back(line);
        }
        return lines;
    }

};


#endif //EXP4_UTILS_H
