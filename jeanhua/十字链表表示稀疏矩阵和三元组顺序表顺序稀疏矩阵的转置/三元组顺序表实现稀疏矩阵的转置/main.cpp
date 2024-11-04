#include <iostream>
#include <vector>
using namespace std;

struct Triple {
    int row, col, value;
};

class SparseMatrix {
public:
    int rows, cols, nonZeroCount;
    vector<Triple> data;

    SparseMatrix(int rows, int cols, int nonZeroCount) : rows(rows), cols(cols), nonZeroCount(nonZeroCount) {
        data.reserve(nonZeroCount);
    }

    void addTriple(int row, int col, int value) {
        data.push_back({row, col, value});
    }

    void print() const {
        cout << "Row\tCol\tValue\n";
        for (const auto &triple : data) {
            cout << triple.row << "\t" << triple.col << "\t" << triple.value << endl;
        }
    }

    SparseMatrix transpose() const {
        SparseMatrix transposed(cols, rows, nonZeroCount);

        vector<int> colCount(cols, 0);
        for (const auto &triple : data) {
            colCount[triple.col]++;
        }

        vector<int> startPosition(cols, 0);
        for (int i = 1; i < cols; i++) {
            startPosition[i] = startPosition[i - 1] + colCount[i - 1];
        }

        for (const auto &triple : data) {
            int pos = startPosition[triple.col]++;
            transposed.data.push_back({triple.col, triple.row, triple.value});
        }

        return transposed;
    }
};

int main() {
    int rows = 4, cols = 5;
    SparseMatrix matrix(rows, cols, 4);
    matrix.addTriple(0, 1, 5);
    matrix.addTriple(1, 0, 3);
    matrix.addTriple(2, 3, 6);
    matrix.addTriple(3, 4, 8);

    cout << "Original Matrix:\n";
    matrix.print();

    SparseMatrix transposedMatrix = matrix.transpose();

    cout << "\nTransposed Matrix:\n";
    transposedMatrix.print();
    system("pause");
    return 0;
}
