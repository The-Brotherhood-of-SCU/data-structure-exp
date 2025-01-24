//
// Created by Administrator on 2024/12/12.
//

#ifndef EXP1_EXCEPTION_H
#define EXP1_EXCEPTION_H
#include <utility>

#include "exception"
#include "string"
#include "iostream"
using namespace std;
class Exception :exception {
public:
    string msg;
    explicit Exception(string msg){
        this->msg = std::move(msg);
    }
};


#endif //EXP1_EXCEPTION_H
