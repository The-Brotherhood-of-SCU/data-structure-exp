#include<iostream>
#include "stack_and_queue.h"
#include<functional>
using namespace std;

void stack_test() {
	cout << "<---------------------------stack test--------------------------->" << endl;
	Stack<int>* stack = new Stack<int>();
	stack->push(111);
	stack->push(222);
	stack->push(333);
	stack->push(444);
	cout << "length:" << stack->length() << endl;
	cout << "pop:" << stack->pop() << endl;
	cout << "length:" << stack->length() << endl;
	cout << "pop:" << stack->pop() << endl;
	cout << "length:" << stack->length() << endl;
	cout << "pop:" << stack->pop() << endl;
	cout << "length:" << stack->length() << endl;
	cout << "pop:" << stack->pop() << endl;
	cout << "length:" << stack->length() << endl;
	delete stack;
}

void queue_test() {
	cout << "<---------------------------queue test--------------------------->" << endl;
	Queue<int>* queue = new Queue<int>();
	queue->add(111);
	queue->add(222);
	queue->add(333);
	queue->add(444);
	cout << "get:" << queue->get() << endl;
	cout << "length:" << queue->length() << endl;
	cout << "get:" << queue->get() << endl;
	cout << "length:" << queue->length() << endl;
	cout << "get:" << queue->get() << endl;
	cout << "length:" << queue->length() << endl;
	cout << "get:" << queue->get() << endl;
	cout << "length:" << queue->length() << endl;
	delete queue;
}

void matchBracket(string exp) {
	cout << "<---------------------------matchBracket--------------------------->" << endl;
	Stack<char>* bracket = new Stack<char>();
	cout << exp << endl;
	for (int i = 0; i < exp.length(); i++) {
		char c = exp.c_str()[i];
		if (c == '(' || c == '[' || c == '{') {
			bracket->push(c);
		}
		else if (c == ')' || c == ']' || c == '}') {
			if (c == ')') {
				if (bracket->top() == '(') {
					bracket->pop();
				}
			}
			else if (c == ']') {
				if (bracket->top() == '[') {
					bracket->pop();
				}
			}
			else if (c == '}') {
				if (bracket->top() == '{') {
					bracket->pop();
				}
			}
		}
	}
	if (bracket->length() == 0) {
		cout << "匹配成功" << endl;
	}
	else {
		cout << "匹配失败" << endl;
	}
	delete bracket;
}


void mazeTest() {
	cout << "<---------------------------mazeTest--------------------------->" << endl;
	class point {
	public:
		int row;
		int column;
		int direction = -1;// 0上 1右 2下 3左
		point(int row, int column) :row(row), column(column) {}
		point() {}
	};
	const int direction[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
	const int RowSize = 10;
	const int ColumnSize = 10;
	Stack<point>* path = new Stack<point>();
	int maze[RowSize][ColumnSize] = {
	{ 1, 1, 0, 0, 0, 1,1,1,0,0 },
	{ 0, 1, 0, 1, 1, 1,0,1,0,0 },
	{ 0, 1, 1, 1, 0, 1,0,1,1,1 },
	{ 1, 1, 0, 1, 0, 0,0,0,1,0 },
	{ 0, 1, 0, 1, 0, 1,1,1,1,0 },
	{ 0, 1, 1, 0, 1, 1,1,0,0,0 },
	{ 1, 1, 0, 0, 0, 1,0,0,0,0 },
	{ 0, 1, 1, 0, 0, 1,1,1,1,0 },
	{ 0, 1, 1, 1, 0, 0,1,0,1,0 },
	{ 0, 1, 0, 0, 0, 0,1,0,1,1 },
	};// 0障碍 1通路
	point start(0, 0), end(9, 9);
	path->push(start);
	function<bool(point p,int m[][ColumnSize])> isPath = [](point p, int m[][ColumnSize])->bool {
		switch (p.direction)
		{
		case 0:
		{
			if (p.row > 0 && m[p.row - 1][p.column] == 1) {
				return true;
			}
			else return false;
			break;
		}
		case 1:
		{
			if(p.column+1 < ColumnSize && m[p.row][p.column + 1] == 1) {
				return true;
			}
			else return false;
			break;
		}
		case 2:
		{
			if (p.row < RowSize-1 && m[p.row + 1][p.column] == 1) {
				return true;
			}
			else return false;
			break;
		}
		case 3:
		{
			if (p.column > 0 && m[p.row][p.column-1] == 1) {
				return true;
			}
			else return false;
			break;
		}
		}
	};
	while (path->length())
	{
		point& cur = path->top();
		maze[cur.row][cur.column] = 1;
		if (cur.direction < 3) {
			cur.direction++;
		}
		else {
			path->pop();
			continue;
		}
		if (cur.row == end.row && cur.column == end.column) {
			break;
		}
		if (isPath(cur,maze)) {
			maze[cur.row][cur.column] = 2;
			path->push(point(cur.row+direction[cur.direction][0],cur.column+direction[cur.direction][1]));
		}
	}
	if (path->length() == 0) {
		cout << "找不到路径" << endl;
	}
	else {
		for (int i = 0; i < RowSize; i++) {
			for (int j = 0; j < ColumnSize; j++) {
				if (maze[i][j] == 2 || (i==end.row&&j==end.column)) {
					cout << "■ ";
				}
				else {
					cout << maze[i][j]<<" ";
				}
			}
			cout << '\n';
		}
	}

	delete path;
}


int main() {
	stack_test();
	queue_test();
	matchBracket("{{{()[]}{}");
	matchBracket("{{{()[]}}}");
	mazeTest();
	system("pause");
}