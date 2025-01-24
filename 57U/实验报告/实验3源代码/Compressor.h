//
// Created by Administrator on 2024/11/7.
//
#include "vector"
#include "map"
#include "Huffman.h"
using  namespace  std;
#ifndef EXP3_COMPRESSOR_H
#define EXP3_COMPRESSOR_H
#define byte char


class Compressor {

public:
    vector<byte> decompress(const vector<byte>& raw){
        //the first 4 byte is the length of meta (not include self)
        int metaLength=*((int*)raw.data());
        //the first 4 byte of tree is content length
        int length=*((int*)(raw.data()+4));
        int huffmanLen=(metaLength-4)/5;
        vector<byte> data(raw.data() + 8, raw.data() + 8 + huffmanLen);
        int* w=(int*)(raw.data() + 8 + huffmanLen);
        vector<int> weights(w,w+huffmanLen);
        vector<byte> content(raw.data()+4+metaLength,raw.data()+raw.size());
        auto huffman=Huffman::fromWeights(data,weights);
        return huffman.decoding(content,length);
    }

/// File structure:metaLength(int),contentLength(int),char1(byte),,,freq(int),,,content
/// \param raw
/// \return
    vector<byte> compress(const vector<byte>& raw){
        map<byte,int> map;
        for(auto i:raw){
            if(map.find(i)!=map.end()){
                map[i]=map[i]+1;
            }else{
                map[i]=1;
            }
        }
        vector<byte> data(map.size());
        vector<int> weights(map.size());
        int index=0;
        for(auto i:map){
            data[index]=i.first;
            weights[index]=i.second;
            index++;
        }
        auto huffman=Huffman::fromWeights(data,weights);
        auto content= huffman.encoding(raw);
        vector<byte> result;

        int metaLength= 4 + data.size()*5;
        byte* metaLengthByte=(byte*)&metaLength;
        //meta length
        result.reserve(4);
        for(int i=0;i<4;i++){
            result.push_back(*(metaLengthByte+i));
        }
        //meta
        result.reserve(metaLength);
        int contentLength=raw.size();
        byte* contentLengthByte=(byte*)&contentLength;
        for(int i=0;i<4;i++){
            result.push_back(contentLengthByte[i]);
        }
        for(auto i:data){
            result.push_back(i);
        }
        for(auto i:weights){
            byte* p=(byte*)&i;
            for(int j=0;j<4;j++){
                result.push_back(p[j]);
            }
        }
        //content
        for(auto i:content){
            result.push_back(i);
        }


        return result;
    }
};


#endif //EXP3_COMPRESSOR_H
