//
// Created by Administrator on 2024/11/7.
//
#include <cstdlib>
#include "vector"
#include "HuffmanTree.h"
#include "map"
#include "BitBuffer.h"

#ifndef EXP3_HUFFMAN_H
#define EXP3_HUFFMAN_H
#define byte char
#define HuffmanCode vector<int>

using namespace std;

byte BYTE0=(byte)0;
class Huffman {
protected:
    map<byte,HuffmanCode> leafNodes;
    HuffmanNode* treeTop= nullptr;

    void encodingHuffman(HuffmanNode* root,const HuffmanCode& num){
        if(root->isAbstractNode()){
            auto left=HuffmanCode(num);
            left.push_back(0);
            encodingHuffman(root->left,left);
            auto right=HuffmanCode(num);
            right.push_back(1);
            encodingHuffman(root->right,right);
        }else{
            leafNodes[root->data]=num;
        }
    }
    Huffman()=default;

public:

    static Huffman fromWeights(const vector<byte>& data,const vector<int>& weights){
        auto treeTop=HuffmanTree::buildHuffmanTree(data,weights);
        auto huffman=Huffman();
        huffman.treeTop=treeTop;
        huffman.encodingHuffman(treeTop,HuffmanCode());
        return huffman;
    }
    vector<byte> encoding(const vector<byte>& source){
        unsigned long long totalLength=0;
        vector<HuffmanCode> huffmanLen;
        for(auto i:source){
            auto length1=leafNodes[i];
            huffmanLen.push_back(length1);
            totalLength+=(length1.size());
        }
        int byteLen=(totalLength-1)/8+1;
        BitInputBuffer buffer(byteLen);
        for(auto i:huffmanLen){
            for(auto j:i){
                if(j){
                    buffer.push1();
                }else{
                    buffer.push0();
                }
            }
        }
        auto array=buffer.getArray();
        vector<byte> result(array,array+byteLen);
        buffer.dispose();
        return result;

    }
    vector<byte> decoding(const vector<byte>& source,int length){
        vector<byte> decoded;
        BitOutputBuffer buffer(source);
        for(int i=0;i<length;i++){
            HuffmanNode* node=treeTop;
            while (node->isAbstractNode()){
                if(buffer.get()==BYTE0){//left
                    node=node->left;
                }else{
                    node=node->right;
                }
            }
            decoded.push_back(node->data);
        }
        return decoded;
    }

    ~Huffman(){
        treeTop->destory();
    }
};


#endif //EXP3_HUFFMAN_H
