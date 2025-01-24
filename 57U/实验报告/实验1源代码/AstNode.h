//
// Created by Administrator on 2024/10/10.
//

#include "string"
#include "cmath"

#ifndef EXP1_ASTNODE_H
#define EXP1_ASTNODE_H

using namespace std;

enum ElementType{immediate,function,op};
class AstNode{
public:
    const ElementType type;
    AstNode(ElementType type):type(type){

    }
    string op;
    AstNode* left= nullptr;
    AstNode* right= nullptr;
    double immediateNumber;
    double eval(){
        if(type==ElementType::immediate){
            return immediateNumber;
        }
        if(type==ElementType::function){
            auto p=left->eval();
            if(op=="SIN"){
                return sin(p);
            }
            if(op=="COS"){
                return cos(p);
            }
            if(op=="EXP"){
                return exp(p);
            }
            //TODO:more function
            throw "function ("+op+") not supported";
        }
        //else
        if(op=="-"){
            if(left!= nullptr){
                return left->eval()-right->eval();
            }
            return -right->eval();
        }
        if(op=="+"){
            return left->eval()+right->eval();
        }
        if(op=="*"){
            return left->eval()*right->eval();
        }
        if(op=="/"){
            return left->eval()/right->eval();
        }
        if(op=="!"){
            return factorial(left->eval());
        }
        if(op=="^"){
            return pow(left->eval(),right->eval());
        }
        throw "operator ("+op+") not supported";
    }

    static void destory(AstNode* root){
        if(root->left!= nullptr){
            destory(root->left);
        }
        if(root->right!= nullptr){
            destory(root->right);
        }
        delete root;
    }
private:
    static int factorial(double value){
        int n=(int)value;
        int result=1;
        for(int i=n;i>1;i--){
            result*=i;
        }
        return result;
    }
};


#endif //EXP1_ASTNODE_H
