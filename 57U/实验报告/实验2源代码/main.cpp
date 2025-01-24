#include <iostream>
#include "Editor.h"

using  namespace std;
int main() {
    system("chcp 65001");
    while (true){
        auto input=Utils::getLine("Which file do you want to open?(default 'file_in.txt')( / to quit):");
        if(input=="/"){
            break;
        }
        if(input.empty()){
            input="file_in.txt";
        }
        try{
            auto editor=Editor(input);
            if(editor.beginEventLoop()){
                break;
            }
        }catch (const char* t){
            cerr<<"Failed opening this file: "<<t<<endl;
        }catch (const string& t){
            cerr<<"Failed opening this file: "<<t<<endl;
        }
    }
    Utils::getLine("see you next time!");
    return 0;
}
