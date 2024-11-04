#include <iostream>
using namespace std;

struct Node {
    int row;
    int col;
    int value;
    Node* right;
    Node* down;
};

class SparseMatrix {
private:
    Node* rowHead;
    Node* colHead;
    int rows;
    int cols;
    int nums;

public:
    SparseMatrix(int r, int c, int num) : rows(r), cols(c), nums(num) {
        rowHead = new Node[rows];
        colHead = new Node[cols];
        for (int i = 0; i < rows; ++i) {
            rowHead[i].right = nullptr;
        }
        for (int j = 0; j < cols; ++j) {
            colHead[j].down = nullptr;
        }
    }
    ~SparseMatrix() {
        for (int i = 0; i < rows; ++i) {
            Node* current = rowHead[i].right;
            while (current) {
                Node* toDelete = current;
                current = current->right;
                delete toDelete;
            }
        }
        delete[] rowHead;
        delete[] colHead;
    }

    void insert(int r, int c, int val) {
        if (val == 0) return; 
        Node* newNode = new Node{r, c, val, nullptr, nullptr};
        if (!rowHead[r].right) {
            rowHead[r].right = newNode;
        } else {
            Node* current = &rowHead[r];
            while (current->right && current->right->col < c) {
                current = current->right;
            }
            newNode->right = current->right;
            current->right = newNode;
        }
        if (!colHead[c].down) {
            colHead[c].down = newNode;
        } else {
            Node* current = &colHead[c];
            while (current->down && current->down->row < r) {
                current = current->down;
            }
            newNode->down = current->down;
            current->down = newNode;
        }
    }
    void print() {
        for (int i = 0; i < rows; ++i) {
            Node* currentRow = rowHead[i].right;
            for (int j = 0; j < cols; ++j) {
                if (currentRow && currentRow->col == j) {
                    cout << currentRow->value << " ";
                    currentRow = currentRow->right;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    SparseMatrix sm(5, 5, 5);
    sm.insert(0, 0, 1);
    sm.insert(1, 1, 2);
    sm.insert(2, 2, 3);
    sm.insert(3, 3, 4);
    sm.insert(4, 4, 5);

    sm.print();
    system("pause");
    return 0;
}
