//
// Created by Administrator on 2024/10/24.
//
#include "string"
#include "Utils.h"
#include "char_string.h"
#include "vector"

#ifndef EXP2_EDITOR_H
#define EXP2_EDITOR_H


class Editor {
protected:
    static void clearConsole(){
        //cout << "\033c";
        system("cls");
    }
    vector<LinkList<CharString>> history;
    int historySnapshot=-1;
    string originFilePath;
    LinkList<CharString> list;
    bool isUnsavedModifies=false;
    int currentLine=1;
    void saveFile(){
        string str;
        CharString _line;
        for(int i=1;i<list.Length();i++){
            list.GetElem(i,_line);
            str+=_line.ToCStr();
            str+='\n';
        }
        list.GetElem(list.Length(),_line);
        str+=_line.ToCStr();
        Utils::writeTextFile(originFilePath,str);
        isUnsavedModifies= false;
    }
    void findStr(){
        auto l=Utils::getLine("Input the line to find: ");
        auto pattern=CharString(l.data());
        int i=currentLine;
        CharString s;
        int offset=-1;
        for(;i<=list.Length();i++){
            list.GetElem(i,s);
            offset= Index(s,pattern);
            if(offset!=-1){
                break;
            }
        }
        if(offset!=-1){
            cout<<"find '"<<l<<"' @line "<<i<<" offset "<<offset<<":"<<endl;
            currentLine=i;//redirect to the line
        }else{
            cout<<"nothing find"<<endl;
        }
    }
    void pushHistory(){
        //clear the history behind the history-snapshot
        int itemsToPop=history.size()-historySnapshot-1;
        for(int i=0;i<itemsToPop;i++){
            history.pop_back();
        }
        history.emplace_back(list);
        historySnapshot++;
    }
    void undo(){
        int temp=historySnapshot-1;
        if(temp<0){
            cout<<"nothing to recovery"<<endl;
        }else{
            historySnapshot=temp;
            list=history[historySnapshot];
            isUnsavedModifies= true;
        }
    }
    void unundo(){
        int temp=historySnapshot+1;
        if(temp<history.size()){
            historySnapshot=temp;
            list=history[historySnapshot];
            isUnsavedModifies= true;
        }else{
            cout<<"nothing to un-undo"<<endl;
        }

    }
    void makeChanges(){
        pushHistory();
        isUnsavedModifies= true;
    }
public:

    explicit Editor(const string& path){
        originFilePath=path;
        auto text=Utils::readTextFile(path);
        for(const auto& i:Utils::splitStringByNewLine(text)){
            list.Insert(list.Length()+1,CharString(i.data()));
        }
        if(list.Empty()){
            list.Insert(1,CharString());
        }
        pushHistory();
    }
    ///
    /// \return whether truly exit
    bool beginEventLoop(){
        auto printHelp=[&]{
            //clearConsole();
            cout<<"---HELP---"<<endl
                <<"(v)iew all"<<endl
                <<"(h)elp aka (?)"<<endl
                <<"(n)ext line"<<endl
                <<"(p)revious line"<<endl
                <<"(b)egin of the file"<<endl
                <<"(e)nd of the file"<<endl
                <<"(g)oto <line>"<<endl
                <<"(q)uit"<<endl
                <<"(s)ave the file"<<endl
                <<"(c)hange thr current line to another"<<endl
                <<"(d)elete current line"<<endl
                <<"(f)ind string from current line"<<endl
                <<"(i)nsert <line?=currentLine> #-1 represents the last line"<<endl
                <<"(r)ead another file"<<endl
                <<"(u)ndo"<<endl
                <<"(z) 重做"<<endl
                <<"--------"<<endl;
        };
        while (true){
            //clearConsole();
            try{
                CharString line;
                list.GetElem(currentLine,line);
                cout<<"Line "<<currentLine<<":"<<line.ToCStr()<<endl;
                auto input=Utils::getArguments();
                if(input.empty()){
                    throw "empty command, input 'H' or '?' to get help";
                }
                auto command=input[0];
                if(command=="q"){
                    if(isUnsavedModifies){
                        if(Utils::getLine("There are unsaved changes, are you sure to exit?(y)")=="y"){
                            break;
                        } else{
                            continue;
                        }
                    }
                    break;
                }else if(command=="v"){
                    list.Traverse([](auto i){
                        cout<<i.ToCStr()<<endl;
                    });
                    //Utils::getLine("Press Any Key to Continue...");
                }else if(command=="?"||command=="h"){
                    printHelp();
                }else if(command=="p"){
                    int prev=currentLine-1;
                    currentLine=prev<1?1:prev;
                }else if(command=="n"){
                    int next=currentLine+1;
                    currentLine=next>list.Length()?list.Length():next;
                }else if(command=="b"){
                    currentLine=1;
                }else if(command=="e"){
                    currentLine=list.Length();
                }else if(command=="g"){
                    int l= stoi(input[1]);
                    if(l<1||l>list.Length()){
                        throw "line not in range";
                    }
                    currentLine=l;
                }else if(command=="s"){
                    saveFile();
                }else if(command=="c"){

                    auto l=Utils::getLine("Input the line to replace: ");
                    list.SetElem(currentLine,CharString(l.data()));
                    makeChanges();
                }else if(command=="d"){

                    list.Delete(currentLine);
                    makeChanges();
                }else if(command=="f"){
                    findStr();
                } else if(command=="i"){

                    int l=currentLine;
                    if(input.size()>1){
                        l= stoi(input[1]);
                    }
                    if(l==-1){
                        l=list.Length()+1;
                    }
                    auto s=Utils::getLine("Insert line @"+ to_string(l));
                    if(!list.Insert(l,CharString(s.data()))){
                        throw "can not insert";
                    } else{
                        makeChanges();
                    }

                }else if(command=="r"){//read another file
                    return false;
                }else if(command=="u"){//undo
                    undo();
                }else  if(command=="z"){//undo
                    unundo();
                }else{
                    throw "unknown command";
                }
            }catch (const string& t){
                cerr<<"INVALID: "<<t<<endl;
            }catch (const char* t){
                cerr<<"INVALID: "<<t<<endl;
            }

        }
        return true;
    }
};


#endif //EXP2_EDITOR_H
