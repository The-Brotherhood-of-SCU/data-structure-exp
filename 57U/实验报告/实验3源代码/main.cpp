#include <iostream>
#include "vector"
#include "Compressor.h"
#include "Utils.h"
#define byte char
using  namespace  std;


void testBitArray(){
    vector<byte> array={(byte)1,(byte)2,(byte)3};
    BitOutputBuffer buffer(array);
    cout<<"Test bit output";
    for(int i=0;i<24;i++){
        cout << static_cast<bool>(buffer.get()) << ",";
    }
    BitInputBuffer inputBuffer(3);
    for(int i=0;i<24;i++){
        if(i%2){
            inputBuffer.push0();
        }else{
            inputBuffer.push1();
        }
    }
    auto a=inputBuffer.getArray();
    vector<byte> a2(a,a+3);

}
void testHuffman(){
    vector<byte> data={(byte)3,(byte)1};
    vector<int> w={10,1};
    Huffman huffman=Huffman::fromWeights(data,w);
    vector<byte> raw={(byte)3,(byte)3,(byte)3,(byte)3,(byte)3,(byte)3,(byte)3,(byte)3,(byte)3,(byte)1};
    cout<<"**"<<endl;
    auto compressed=huffman.encoding(raw);
    for(auto i:compressed){
        cout<<(int)i<<",";
    }
    cout<<endl;
    auto decompressed=huffman.decoding(compressed,raw.size());
    for(int i=0;i<raw.size();i++){
        cout<<(int)decompressed[i]<<",";
    }
}
void testCompression(){
    Compressor compressor;
    vector<byte> raw={(byte)3,(byte)3,(byte)3,(byte)3,(byte)3,(byte)3,(byte)3,(byte)3,(byte)3,(byte)1};
    auto compressed=compressor.compress(raw);
    auto decompressed=compressor.decompress(compressed);
    for(auto i:decompressed){
        cout<<(int)i<<",";
    }
}
int main() {
    Compressor compressor;
    while (true){
        cout<<"choose mode: \n1.compress\n2.decompress\n3.quit"<<endl;
        auto mode=Utils::getLine();
        if(mode=="1"){
            auto path=Utils::getLine("Input File Path: ");
            auto file=Utils::readFile(path);
            auto compressed=compressor.compress(file);
            Utils::writeFile(path+".compressed",compressed);
            cout<<"done"<<endl;
        }else if(mode=="2"){
            auto path=Utils::getLine("Input File Path: ");
            auto file=Utils::readFile(path);
            auto decompressed=compressor.decompress(file);
            Utils::writeFile(path+".decompressed",decompressed);
            cout<<"done"<<endl;
        }else if(mode=="3"){
            break;
        }else{
            cout<<"unknown command\n";
        }
    }


    return 0;
}

