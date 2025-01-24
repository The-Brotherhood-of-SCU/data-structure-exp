//
// Created by Administrator on 2024/11/7.
//

#ifndef EXP3_BITBUFFER_H
#define EXP3_BITBUFFER_H


#include <cstddef>
#include <utility>
#define byte char
using namespace std;

class BitInputBuffer {
protected:
    byte* p;
    int offset=0;//avaliable
    byte* current;
public:
    ///
    /// \param len byte length
    explicit BitInputBuffer(int len){
        p=new byte[len];
        current=p;
    }
    void push0(){
        *current= (*current) & static_cast<byte>(~(1 << offset));
        if(offset==7){
            offset=0;
            current++;
        } else{
            offset++;
        }
    }
    void push1(){
        *current= (*current) | static_cast<byte>(1 << offset);
        if(offset==7){
            offset=0;
            current++;
        } else{
            offset++;
        }
    }
    void push1(int times){
        for(int i=0;i<times;i++){
            push1();
        }
    }
    byte* getArray() const{
        return p;
    }
    void dispose(){
        delete p;
    }
};
#include "vector"
class BitOutputBuffer{
protected:
    vector<byte> source;
    int offset=0;
    int index=0;
public:
    BitOutputBuffer(vector<byte> source){
        this->source=std::move(source);
    }
    /// return the next bit
    /// \return one bit
    byte get(){
        byte b=source[index];
        byte v= b & static_cast<byte>(1 << offset);
        v= v>>offset;
        if(offset==7){
            offset=0;
            index++;
        }else{
            offset=offset+1;
        }
        return v;
    }
};

#endif //EXP3_BITBUFFER_H
