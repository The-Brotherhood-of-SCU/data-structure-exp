#include <iostream>
#include <vector>

const int HASH_TABLE_SIZE = 16;

// 哈希函数，使用除留余数法
int hashFunction(int key, int divisor) {
    return key % divisor;
}

// 线性探测再散列处理冲突
int linearProbing(const std::vector<int>& hashTable, int key, int divisor) {
    int index = hashFunction(key, divisor);
    int originalIndex = index;
    int comparisons = 1; // 比较次数，初始为1

    while (hashTable[index] != key && hashTable[index] != 0) {
        index = (index + 1) % HASH_TABLE_SIZE; // 线性探测下一个位置
        if (index == originalIndex) { // 如果回到了原点，表示哈希表已满
            break;
        }
        comparisons++;
    }

    // 如果找到了key，则返回比较次数，否则返回-1表示查找失败
    return (hashTable[index] == key) ? comparisons : -comparisons;
}

int main() {
    int elem[] = {19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79};
    int divisor = 13;
    std::vector<int> hashTable(HASH_TABLE_SIZE, 0); // 初始化哈希表，所有位置设为0

    // 将元素插入哈希表
    for (int key : elem) {
        int index = hashFunction(key, divisor);
        while (hashTable[index] != 0) { // 如果位置已被占用，则线性探测下一个位置
            index = (index + 1) % HASH_TABLE_SIZE;
        }
        hashTable[index] = key; // 存储元素
    }

    // 输出哈希表的数据存储状态
    std::cout << "哈希表的数据存储状态:" << std::endl;
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        std::cout << "位置[" << i << "]: " << hashTable[i] << std::endl;
    }

    // 从键盘读取一个整数
    int searchKey;
    std::cout << "请输入一个整数进行查找: ";
    std::cin >> searchKey;

    // 查找整数并输出比较次数
    int comparisons = linearProbing(hashTable, searchKey, divisor);
    if (comparisons > 0) {
        std::cout << "查找成功，比较次数: " << comparisons << std::endl;
    } else {
        std::cout << "查找失败，比较次数: " << -comparisons << std::endl;
    }
    system("pause");
    return 0;
}
