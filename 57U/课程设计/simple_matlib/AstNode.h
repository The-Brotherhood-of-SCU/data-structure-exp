//
// Created by Administrator on 2024/10/10.
//
#pragma once

#include <utility>

#include "string"
#include "cmath"
#include "map"
#include "Exception.h"

#ifndef EXP1_ASTNODE_H
#define EXP1_ASTNODE_H

using namespace std;

enum ElementType{immediate,function,op,variable};
class AstNode{
public:
    static AstNode* add(AstNode* left,AstNode* right){
        auto result=new AstNode(ElementType::op);
        result->op="+";
        result->left=left;
        result->right=right;
        return result;
    }
    static AstNode* sub(AstNode* left,AstNode* right){
        auto result=new AstNode(ElementType::op);
        result->op="-";
        result->left=left;
        result->right=right;
        return result;
    }
    static AstNode* mul(AstNode* left,AstNode* right){
        auto result=new AstNode(ElementType::op);
        result->op="*";
        result->left=left;
        result->right=right;
        return result;
    }
    static AstNode* div(AstNode* left,AstNode* right){
        auto result=new AstNode(ElementType::op);
        result->op="/";
        result->left=left;
        result->right=right;
        return result;
    }
    static AstNode* power(AstNode* left,AstNode* right){
        auto result=new AstNode(ElementType::op);
        result->op="^";
        result->left=left;
        result->right=right;
        return result;
    }
    static AstNode* ln(AstNode* node){
        auto result=new AstNode(ElementType::function);
        result->op="LN";
        result->left=node;
        return result;
    }
    AstNode* operator+(AstNode* node){
        return AstNode::add(this, node);
    }
    AstNode* operator-(AstNode* node){
        return AstNode::sub(this, node);
    }
    AstNode* operator*(AstNode* node){
        return AstNode::mul(this, node);
    }
    AstNode* operator/(AstNode* node){
        return AstNode::div(this, node);
    }
    const ElementType type;
    explicit AstNode(ElementType type):type(type){

    }
    explicit AstNode(double immediateNumber):type(ElementType::immediate){
        this->immediateNumber=immediateNumber;
    }
    explicit AstNode(string variableName):type(ElementType::variable){
        this->variableName=std::move(variableName);
    }

    /// copy constructor(deep copy)
    /// @param node
    explicit AstNode(const AstNode* node):type(node->type) {
        this->op=node->op;
        if(node->left!= nullptr){
            this->left=new AstNode(node->left);
        }
        if(node->right!= nullptr){
            this->right=new AstNode(node->right);
        }
        this->immediateNumber=node->immediateNumber;
        this->variableName=node->variableName;
    }

    [[nodiscard]] AstNode* copy() const {
        return new AstNode(this);
    }
    int validTag=0x12345678;
    string op;
    AstNode* left= nullptr;
    AstNode* right= nullptr;
    double immediateNumber=NAN;
    string variableName;
    ~ AstNode() {
        validTag=~validTag;
    }
    /// calculate the value of the node
    /// @param variables math-variable
    /// @return eval
    [[nodiscard]] double eval(const map<string,double>& variables) const{
        if(type==ElementType::immediate){
            return immediateNumber;
        }
        if(type==ElementType::variable){
            if(variables.find(variableName)==variables.end()){
                throw Exception("variable ("+variableName+") not found");
            }
            return variables.at(variableName);
        }

        if(type==ElementType::function){
            if(left== nullptr){
                throw Exception("null child node find");
            }
            auto p=left->eval(variables);
            if(op=="SIN"){
                return sin(p);
            }
            if(op=="COS"){
                return cos(p);
            }
            if(op=="EXP"){
                return exp(p);
            }
            if(op=="LN"){
                return log(p);
            }
            //TODO:more function
            throw Exception("function ("+op+") not supported");
        }
        //else
        if(op=="-"){
            if(left!= nullptr){
                return left->eval(variables)-right->eval(variables);
            }
            return -right->eval(variables);
        }
        if(op=="+"){
            return left->eval(variables)+right->eval(variables);
        }
        if(op=="*"){
            return left->eval(variables)*right->eval(variables);
        }
        if(op=="/"){
            return left->eval(variables)/right->eval(variables);
        }
        if(op=="!"){
            return factorial(left->eval(variables));
        }
        if(op=="^"){
            return pow(left->eval(variables),right->eval(variables));
        }
        throw Exception("operator ("+op+") not supported");
    }

    /// calc a derivative,return a new node
    /// @param variable derivative variable
    /// @return a new node
    AstNode* derivative(const string& variable) {
        AstNode* result = nullptr;
        if (type == ElementType::immediate) {
            result= new AstNode(ElementType::immediate);
            result->immediateNumber=0;
        }
        else if (type == ElementType::variable) {
            result = new AstNode(ElementType::immediate);
            if (variableName == variable) {
                result->immediateNumber = 1;
            } else {
                result->immediateNumber = 0;
            }
        }
        else if (type == ElementType::function) {
            if (op == "SIN") {
                auto cos=new AstNode(ElementType::function);
                cos->op="COS";
                cos->left=left->copy();
                result= mul(cos,left->derivative(variable));
            }else if(op=="COS"){
                auto sin=new AstNode(ElementType::function);
                sin->op="SIN";
                sin->left=left->copy();
                auto neg= sub(new AstNode(0.0),sin);
                result= mul(neg,left->derivative(variable));
            }else if(op=="EXP"){
                result= mul(this->copy(),left->derivative(variable));
            }else if(op=="LN"){
                auto d= div(new AstNode(1),left->copy());
                result= mul(d,left->derivative(variable));
            }else{
                throw Exception("function ("+op+") not supported");
            }
        }
        else if (type == ElementType::op) {
            if (op == "+") {
                result = add(left->derivative(variable), right->derivative(variable));
            } else if (op == "-") {
                result = sub(left->derivative(variable), right->derivative(variable));
            } else if (op == "*") {
                auto leftDerivative = left->derivative(variable);
                auto rightDerivative = right->derivative(variable);
                result = add(mul(left->copy(), rightDerivative), mul(leftDerivative, right->copy()));
            } else if (op == "/") {
                auto leftDerivative = left->derivative(variable);
                auto rightDerivative = right->derivative(variable);
                auto rightCopy= right->copy();
                auto up=sub(mul(leftDerivative, rightCopy), mul(left->copy(), rightDerivative));
                auto down=mul(rightCopy,rightCopy);
                result = div(up, down);
            }else if(op=="!"){
                //not support
                throw Exception("factorial is not supported in derivative");
            }else if(op=="^"){
                auto leftDerivative = left->derivative(variable);
                auto rightDerivative = right->derivative(variable);
                auto leftCopy= left->copy();
                auto a= power(leftCopy,right->copy());
                auto b=mul(rightDerivative,ln(leftCopy));
                auto c=mul(right->copy(),div(leftDerivative,leftCopy));
                result=mul(a,add(b,c));
            }
        }
        return result;
    }

    static void destroy(const AstNode* root){
        if (root==nullptr||root->validTag!=0x12345678) {
            return;
        }
        if(root->left!= nullptr){
            destroy(root->left);
        }
        if(root->right!= nullptr){
            destroy(root->right);
        }
        delete root;
    }
    static void destroySingle(const AstNode* node){
        delete node;
    }

private:
    static int factorial(double value){
        int n=static_cast<int>(value);
        int result=1;
        for(int i=n;i>1;i--){
            result*=i;
        }
        return result;
    }
public:
    /// simplify the node itself
    static void simplifySingle(AstNode** node_raw){
        AstNode* node=*node_raw;
        if(node->op=="+") {
            if(node->left!=nullptr&&
                node->left->type==immediate&&
                node->left->immediateNumber==0){
                destroySingle(node->left);
                destroySingle(node);
                *node_raw=node->right;
                return;
            }
            if(node->right!=nullptr&&
                node->right->type==immediate&&
                node->right->immediateNumber==0){
                destroySingle(node->right);
                destroySingle(node);
                *node_raw=node->left;
                return;
            }
            if(node->right!=nullptr&&
                node->left!=nullptr&&
                node->right->type==immediate&&
                node->left->type==immediate){
                auto value=node->left->immediateNumber+node->right->immediateNumber;
                destroy(node);
                *node_raw=new AstNode(value);
                return;
            }
        }
        if(node->op=="*"){
            if((node->left!=nullptr&&node->left->type==immediate&&node->left->immediateNumber==0)||
                (node->right!=nullptr&&node->right->type==immediate&&node->right->immediateNumber==0)){
                destroy(node);
                *node_raw=new AstNode(0.0);
                return;
            }
            if(node->right!=nullptr&&
                node->right->type==immediate&&
                node->left->type==immediate){
                auto value=node->left->immediateNumber*node->right->immediateNumber;
                destroy(node);
                *node_raw=new AstNode(value);
                return;
            }
            if(node->left!=nullptr&&
                node->left->type==immediate&&
                node->left->immediateNumber==1){
                destroySingle(node->left);
                destroySingle(node);
                *node_raw=node->right;
                return;
            }
            if(node->right!=nullptr&&
                node->left!=nullptr&&
                node->right->type==immediate&&
                node->right->immediateNumber==1){
                destroySingle(node->right);
                destroySingle(node);
                *node_raw=node->left;
                return;
            }
        }
        if(node->op=="-"){
            if(node->right!=nullptr&&
                node->right->type==immediate&&
                node->right->immediateNumber==0){
                destroySingle(node->left);
                destroySingle(node);
                *node_raw=node->right;
                return;
            }
            if(node->right!=nullptr&&
                node->left!=nullptr&&
                node->right->type==immediate&&
                node->left->type==immediate){
                auto value=node->left->immediateNumber-node->right->immediateNumber;
                destroy(node);
                *node_raw=new AstNode(value);
                return;
            }
        }
        if(node->op=="/"){
            if(node->right->type==immediate&&node->right->immediateNumber==1){
                destroySingle(node->right);
                destroySingle(node);
                *node_raw=node->left;
                return;
            }
            if(node->left->type==immediate&&node->right->type==immediate){
                auto value=node->left->immediateNumber/node->right->immediateNumber;
                destroy(node);
                *node_raw=new AstNode(value);
                return;
            }
        }
    }
    [[nodiscard]] double integrate(const string& variable, const double from, const double to,double step=0.01) const {
        double sum=0;
        map<string,double> values;
        for (double i=from;i<to;i=i+step) {
            values[variable]=i;
            sum+=this->eval(values)*step;
        }
        return sum;
    }
};


#endif //EXP1_ASTNODE_H
