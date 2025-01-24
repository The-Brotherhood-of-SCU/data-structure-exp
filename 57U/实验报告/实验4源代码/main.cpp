#include <iostream>
#include "string"
#include "Table.h"

using namespace std;

int main() {
    system("chcp 65001");
    string file="course_inf.csv";
    string content=Utils::readFile(file);
    auto table=Table(content);
    table.print();
    table.dispose();//free memory
    system("pause");
    return 0;
}
