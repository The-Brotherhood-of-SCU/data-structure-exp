#include <iostream>
#include "string"
#include "ExpressionHandler.h"

#include <iomanip>

using namespace std;
void test(ExpressionHandler& handler){
    cout<<"---Test valid input---"<<endl;
    string input[]={
            "[exp(1)+cos(3.14)+sin(0)+2^2-3/4]*0.5+3!=",
            "{[(114514)]}/1919810",
            "(exp(exp(1)))"
    };
    for(const auto& i:input){
        handler.try_eval(i);
    }
    cout<<"---Test invalid input---"<<endl;
    string input_wrong[]={
            "1=1",
            "NOTEXIST(123)",
            "(1919810+2",
            "[1+2+3)",
            "1+-2"
    };
    for(const auto& i:input_wrong){
        handler.try_eval(i);
    }
    cout<<"---TEST DONE---"<<endl;
}
int main() {
    ExpressionHandler expressionHandler;
    expressionHandler.debug= false;
    test(expressionHandler);

    string expression;
    while (true){
        try{
            cout<<"input infix expression:"<<endl;
            cin>>expression;
            if(expression=="q"){
                break;
            }
            cout<<"answer: "<<expressionHandler.eval(expression)<<endl;
        }catch (const char* t){
            cerr<<t<<endl;
        }catch (string& t ){
            cerr<<t<<endl;
        }catch (exception& e){
            cerr<<e.what()<<endl;
        }
    }
    return 0;
}
