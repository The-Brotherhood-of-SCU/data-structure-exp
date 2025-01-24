//
// Created by Administrator on 2024/11/14.
//
#pragma once
#ifndef EXP3_UTILS_H
#define EXP3_UTILS_H
#define byte char

#include <vector>
#include <fstream>
#include <iomanip>
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
    static std::vector<std::string> splitString(const std::string &str, char delim='\n',bool ignoreEmpty=true) {
        std::vector<std::string> lines;
        std::istringstream iss(str);
        std::string line;
        while (std::getline(iss, line, delim)) {
            if(ignoreEmpty&&line.empty())continue;
            lines.push_back(line);
        }
        return lines;
    }
    static vector<string> splitStringByChars(const std::string &str, const vector<char>& chars){
        vector<string> list;
        stringstream ss;
        for(auto i:str){
            //find weather i is in chars
            if(std::find(chars.begin(),chars.end(),i)!=chars.end()){
                auto s=(ss.str());
                if(!s.empty()){
                    list.push_back(s);
                }
                if (i=='=') {
                    list.push_back(char2string(i));
                }
                ss.str("");
                ss.clear();
            }else{
                if (i!=' ') {
                    ss << i;
                }
            }
        }
        auto s=ss.str();
        if(!s.empty()){
            list.push_back(s);
        }

        return list;
    }
    static vector<string> getArguments(){
        return splitString(getLine(">>>"), ' ');
    }
    static bool isContain(vector<string>& array,const string& target){
        for(auto &item:array){
            if(item==target)return true;
        }
        return false;
    }
    static bool isContain(const string& array,const char target){
        for(auto &item:array){
            if(item==target)return true;
        }
        return false;
    }
    static bool isContain(char* array[],int length,const string& target) {
        for (int i = 0; i < length; i++) {
            if (array[i] == target) {
                return true;
            }
        }
        return false;
    }

    static int find(const string& str,const char target){
        for(int i=0;i<str.size();i++){
            if(str[i]==target)return i;
        }
        return -1;
    }
    static int find(const vector<string>& array,const string& target) {
        for(int i=0;i<array.size();i++){
            if(array[i]==target)return i;
        }
        return -1;
    }
    static string char2string(char c){
        return string(1, c);
    }
    static  std::string toUpperCase(const std::string& input) {
        // 创建一个新字符串，复制输入字符串
        std::string output = input;
        // 使用 std::transform 将字符串中的所有字符转换为大写
        std::transform(output.begin(), output.end(), output.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        // 返回转换后的字符串
        return output;
    }
    static bool assert(const bool condition, const std::string& message="") {
        if (!condition) {
            throw Exception("Assertion Failed! "+message);
        }
        return condition;
    }

    static std::string to_string_with_precision(const double a_value, const int n = 3)
    {
        std::ostringstream out;
        out << std::fixed << std::setprecision(n) << a_value;
        return out.str();
    }
    static string removeComments(string s) {
        const auto p = s.find('#');
        if (p == string::npos) {
            return s;
        }
        string s2 = s.substr(0, p);
        return s2;
    }

};


#endif //EXP3_UTILS_H
