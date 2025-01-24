//
// Created by Administrator on 2024/12/12.
//
#pragma once
#ifndef EXP1_INTERFACE_H
#define EXP1_INTERFACE_H
#include "ExpressionHandler.h"
#include "Utils.h"

class Interface {
private:
    map<string ,AstNode*> symbolTable;
    ExpressionHandler expressionHandler;
    vector<char> splits;
    bool isContainVariable(const string& str){
        if (symbolTable.find(str) != symbolTable.end()) {
            return true;
        }
        return false;
    }
public:
    bool debug=false;
    bool gcEnabled=true;
    Interface(){
        splits={' ','=',','};
    }
    void startEventLoop(){
        while (true) {
            const auto line=Utils::getLine(">>>");
            try{
                handleCommand(line);
            }catch (const Exception& e){
                std::cerr<<e.msg<<endl;
            }catch (const exception& e) {
                std::cerr << "An error occurred: " << e.what() << endl;
            }
        }
    }
    void handleCommand(string command){
        command=Utils::removeComments(command);
        if (command=="exit") {
            Utils::getLine("See you next time...");
            //release memory
            for (const auto& i:symbolTable) {
                AstNode::destroy(i.second);
            }
            exit(0);
        }
        const auto split=Utils::splitStringByChars(command,splits);
        if (debug) {
            ExpressionHandler::prettyPrint(split);
        }
        if(split.empty()){
            return;
        }
        if(split.size()==1){
            //display
            if(symbolTable.find(split[0])==symbolTable.end()){
                throw Exception("variable not found:"+split[0]);
            }
            auto node=symbolTable[split[0]];
            cout<<expressionHandler.toString(node)<<endl;
            return;
        }
        string assignment="";
        int eq_index=Utils::find(split,"=");
        if(eq_index>0) {
            assignment = split[eq_index-1];
        }
        if (debug) {
            cout<<"Assignment:"<<assignment<<endl;
        }

        AstNode* result = nullptr;
        string operation=Utils::toUpperCase(split[eq_index+1]);
        //处理let特殊情况
        if (split[0]=="let"){
            if (debug) {
                cout<<"let assignment started"<<endl;
            }
            const auto& expression=split[eq_index+1];
            if (debug) {
                cout<<"Expression:"<<expression<<endl;
            }
            result=expressionHandler.parse(expression);
        }else {
            if(operation=="DERIV") {
                if (debug) {
                    cout<<"derivative operation started"<<endl;
                }
                Utils::assert(split.size()-eq_index==4,"wrong format");
                const auto node=getNode(split[eq_index+2]);
                const auto& math_variable=split[eq_index+3];
                result=node->derivative(math_variable);
            }else if(operation=="EVAL") {
                if (debug) {
                    cout<<"eval operation started"<<endl;
                }
                map<string,double> values;
                int variable_num=split.size()-eq_index-3;
                Utils::assert(variable_num>=0);
                int offset=eq_index+3;
                for(int i=0;i<variable_num;i++) {
                    auto t=Utils::splitString(split[offset+i],':');
                    Utils::assert(t.size()==2,"variable format error");
                    values[t[0]]=atof(t[1].c_str());
                }
                const auto node=getNode(split[eq_index+2]);
                result=new AstNode(node->eval(values));
            }else if(operation=="SIM") {
                if (debug) {
                    cout<<"simplify operation started"<<endl;
                }
                Utils::assert(split.size()-1==eq_index+2,"format error");
                const auto node=getNode(split[eq_index+2]);
                auto node2=new AstNode(node);
                ExpressionHandler::simplify(&node2);
                result=node2;
            }else if (operation=="INT") {
                if (debug) {
                    cout<<"integrate operation started"<<endl;
                }
                Utils::assert(split.size()-1==eq_index+6,"format error");
                const auto node=getNode(split[eq_index+2]);
                string symbol=split[eq_index+3];
                double from=atof(split[eq_index+4].c_str());
                double to=atof(split[eq_index+5].c_str());
                double step=atof(split[eq_index+6].c_str());
                result=new AstNode(node->integrate(symbol,from,to,step));
            }else {
                auto var_name=split[eq_index+1];
                if (isContainVariable(var_name)) {
                    //copy variable
                    result=new AstNode(symbolTable[var_name]);
                }else {
                    throw Exception("copy failed, can not find this variable: "+var_name);
                }
            }
        }

        if (result==nullptr) {
            throw Exception("internal error");
        }
        if (assignment.empty()) {
            //display
            cout<<expressionHandler.toString(result)<<endl;
        }else {
            //assign
            if (gcEnabled && isContainVariable(assignment)) {
                //gc the previous memory
                AstNode::destroy(symbolTable[assignment]);
                if (debug) {
                    cout<<"gc:"<<assignment<<endl;
                }
            }
            cout<<assignment<<":="<<expressionHandler.toString(result)<<endl;
            symbolTable[assignment]=result;
        }





    }
    AstNode* getNode(const string& name){
        if (isContainVariable(name)) {
            return symbolTable[name];
        }
        throw Exception("variable not found: "+name);
    }
};


#endif //EXP1_INTERFACE_H
