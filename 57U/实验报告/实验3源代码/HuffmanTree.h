//
// Created by Administrator on 2024/11/7.
//
#include <queue>
#ifndef EXP3_HUFFMANTREE_H
#define EXP3_HUFFMANTREE_H
#define byte char
using namespace std;
struct HuffmanNode {
    byte data; // 字节
    int freq; // 频率
    HuffmanNode *left, *right;

    HuffmanNode(byte data, int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
    bool isAbstractNode(){
        return this->left!= nullptr;
    }
    void destory(){
        if(this->isAbstractNode()){
            this->left->destory();
            this->right->destory();
            delete this->left;
            delete this->right;
        }
    }
};
struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->freq > r->freq);
    }
};
class HuffmanTree {
private:
    HuffmanTree() = delete;

public:
    static HuffmanNode* buildHuffmanTree(const vector<byte>& data,const vector<int>& freq) {
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap;

        for (int i = 0; i < data.size(); ++i) {
            minHeap.push(new HuffmanNode(data[i], freq[i]));
        }

        while (minHeap.size() != 1) {
            HuffmanNode *left = minHeap.top();
            minHeap.pop();
            HuffmanNode *right = minHeap.top();
            minHeap.pop();

            auto *top = new HuffmanNode((byte)0, left->freq + right->freq);
            top->left = left;
            top->right = right;
            minHeap.push(top);
        }

        return minHeap.top();
    }

};


#endif //EXP3_HUFFMANTREE_H
