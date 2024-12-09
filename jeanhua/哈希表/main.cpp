#include <iostream>
#include <vector>

const int HASH_TABLE_SIZE = 16;

// ��ϣ������ʹ�ó���������
int hashFunction(int key, int divisor) {
    return key % divisor;
}

// ����̽����ɢ�д����ͻ
int linearProbing(const std::vector<int>& hashTable, int key, int divisor) {
    int index = hashFunction(key, divisor);
    int originalIndex = index;
    int comparisons = 1; // �Ƚϴ�������ʼΪ1

    while (hashTable[index] != key && hashTable[index] != 0) {
        index = (index + 1) % HASH_TABLE_SIZE; // ����̽����һ��λ��
        if (index == originalIndex) { // ����ص���ԭ�㣬��ʾ��ϣ������
            break;
        }
        comparisons++;
    }

    // ����ҵ���key���򷵻رȽϴ��������򷵻�-1��ʾ����ʧ��
    return (hashTable[index] == key) ? comparisons : -comparisons;
}

int main() {
    int elem[] = {19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79};
    int divisor = 13;
    std::vector<int> hashTable(HASH_TABLE_SIZE, 0); // ��ʼ����ϣ������λ����Ϊ0

    // ��Ԫ�ز����ϣ��
    for (int key : elem) {
        int index = hashFunction(key, divisor);
        while (hashTable[index] != 0) { // ���λ���ѱ�ռ�ã�������̽����һ��λ��
            index = (index + 1) % HASH_TABLE_SIZE;
        }
        hashTable[index] = key; // �洢Ԫ��
    }

    // �����ϣ������ݴ洢״̬
    std::cout << "��ϣ������ݴ洢״̬:" << std::endl;
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        std::cout << "λ��[" << i << "]: " << hashTable[i] << std::endl;
    }

    // �Ӽ��̶�ȡһ������
    int searchKey;
    std::cout << "������һ���������в���: ";
    std::cin >> searchKey;

    // ��������������Ƚϴ���
    int comparisons = linearProbing(hashTable, searchKey, divisor);
    if (comparisons > 0) {
        std::cout << "���ҳɹ����Ƚϴ���: " << comparisons << std::endl;
    } else {
        std::cout << "����ʧ�ܣ��Ƚϴ���: " << -comparisons << std::endl;
    }
    system("pause");
    return 0;
}
