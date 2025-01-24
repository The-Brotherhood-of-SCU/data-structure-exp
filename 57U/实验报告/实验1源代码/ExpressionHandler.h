//
// Created by Administrator on 2024/10/10.
//
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include "string"
#include "stack"
#include <cmath>
#include "AstNode.h"

#ifndef EXP1_EXPRESSIONHANDLER_H
#define EXP1_EXPRESSIONHANDLER_H

using namespace std;
class ExpressionHandler {
public:
    ExpressionHandler()= default;
public:
    bool debug=false;
    void try_eval(const string& expression){
        try{
            cout<<expression<<"  #RESULT-> "<<eval(expression)<<endl;
        }catch (const char* t){
            cerr<<t<<endl;
        }catch (string& t ){
            cerr<<t<<endl;
        }catch (exception& e){
            cerr<<e.what()<<endl;
        }
    }
    double eval(const string& expression){
        auto infix=analyze(expression);
        auto postfix=infix2postfix(infix);
        if(debug){
            cout<<"POSTFIX: ";
            prettyPrint(postfix);
        }
        auto astRoot=postfix2Ast(postfix);
        auto result= astRoot->eval();
        AstNode::destory(astRoot);
        return result;
    }
    map<char,int> operators{
        {'=',-1},
        {'(',0},{')',0},
        {'+',1},{'-',1},
        {'*',2},{'/',2},
        {'!',3},{'^',3}
        ,{'F',114514}//函数
    };
    std::vector<std::string> analyze(const std::string& src_raw){
        bracket_validate(src_raw);
        string src(src_raw);
        if(src_raw[src_raw.size()-1]=='='){
            src=src.substr(0,src.size()-1);
        }
        src= toUpperCase(src);
        replaceChar(src, '[', '(');
        replaceChar( src, '{', '(');
        replaceChar( src, ']', ')');
        replaceChar( src, '}', ')');
        vector<string> list;
        stringstream ss;
        for(auto i:src){
            if(this->operators.find(i)!=operators.end()){//is operator
                auto s=(ss.str());
                if(!s.empty()){
                    list.push_back(s);
                }
                list.push_back(char2string(i));
                ss.str("");
                ss.clear();
            }else{
                ss<<i;
            }
        }
        auto s=ss.str();
        if(!s.empty()){
            list.push_back(s);
        }

        return list;
    }
    map<char,char> bracket_pair={
            {')','('},
            {']','['},
            {'}','{'}
    };
    vector<char> bracket_start={'(','[','{'};
    void bracket_validate(const string& s){
        stack<char> bracket_stack;
        for(auto i :s){
            if(std::find(bracket_start.begin(), bracket_start.end(),i)!=bracket_start.end()){
                bracket_stack.push(i);
                continue;
            }
            if(bracket_pair.find(i)!=bracket_pair.end()){
                char mapped=bracket_pair[i];
                if(mapped!=bracket_stack.top()){
                    throw "invalid brackets: brackets not match";
                } else{
                    bracket_stack.pop();
                }
            }
        }
        if(!bracket_stack.empty()){
            throw "invalid brackets: brackets not closed";
        }
    }
    vector<string> infix2postfix(const vector<string>& infix){
        stack<string> operatorStack;
        vector<string> postfix;
        for(const auto& i:infix){
            if(isOperator(i)){
                if(i=="("){
                    operatorStack.push(i);
                }else if(i==")"){
                    auto top=operatorStack.top();
                    operatorStack.pop();
                    while (top!="("){
                        postfix.push_back(top);
                        top=operatorStack.top();
                        operatorStack.pop();
                    }
                }else{
                    while(!operatorStack.empty()&& getPriority(operatorStack.top())>= getPriority(i)){
                        postfix.push_back(operatorStack.top());
                        operatorStack.pop();
                    }
                    operatorStack.push(i);
                }
            }else{
                postfix.push_back(i);
            }
        }
        while(!operatorStack.empty()){
            postfix.push_back(operatorStack.top());
            operatorStack.pop();
        }
        return postfix;
    }
    AstNode* postfix2Ast(const vector<string>& postfix){
        stack<AstNode*> stack;
        for(auto i:postfix){
            if(isOperator(i)){
                if(isFunction(i)){
                    if(stack.size()<1){
                        throw "function has no parameter: "+i;
                    }
                    auto function=new AstNode(ElementType::function);
                    function->op=i;
                    function->left=stack.top();
                    stack.pop();
                    stack.push(function);
                }else{
                    auto op=new AstNode(ElementType::op);
                    op->op=i;
                    if(i=="!"){
                        if(stack.empty()){
                            throw "parameter not enough: "+i;
                        }
                        auto ele=stack.top();
                        stack.pop();
                        op->left= ele;
                    }else if(i=="-"){//减号可能既是一元又是二元
                        if(stack.size()>=2){
                            auto right=stack.top();
                            stack.pop();
                            auto left=stack.top();
                            stack.pop();
                            op->left=left;
                            op->right=right;
                        }else if(stack.size()==1){
                            auto ele=stack.top();
                            stack.pop();
                            op->right= ele;
                        }else{
                            throw "parameter not enough: "+i;
                        }
                    }else{
                        if(stack.size()<2){
                            throw "parameter not enough: "+i;
                        }
                        auto right=stack.top();
                        stack.pop();
                        auto left=stack.top();
                        stack.pop();
                        op->left=left;
                        op->right=right;
                    }
                    stack.push(op);
                }
            }else{
                auto immediate=new AstNode(ElementType::immediate);
                immediate->immediateNumber= stod(i);
                stack.push(immediate);
            }
        }
        if(stack.size()==1){
            return stack.top();
        }else{
            throw ("parameter is too many");
        }
    }

    int getPriority(string op){
        if(isFunction(op)){
            return operators['F'];
        }
        char c=*(op.data());
        return this->operators[c];
    }
    bool isOperator(string c){
        if(isFunction(c)){
            return true;
        }
        if(c.size()!=1){
            return false;
        }
        char a=*(c.data());
        return  this->operators.find(a)!=operators.end();
    }
    static void prettyPrint(vector<string> list){
        cout<<'|';
        for(const auto& i:list){
            cout<<i<<'|';
        }
        cout<<endl;
    }
    static void replaceChar(string& str, char to_replace, char replacement){
        std::replace(str.begin(), str.end(), to_replace, replacement);
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
    static string char2string(char c){
        return std::string(1, c);
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
    static bool isFunction(const string& s){//如果全为大写，那么就是函数
        for(auto i:s){
            if(!('A'<=i && i<='Z')){
                return false;
            }
        }
        return true;
    }

};



#endif //EXP1_EXPRESSIONHANDLER_H
