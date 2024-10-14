#include<iostream>
#include "LinkNode.h"
using namespace std;

#define WriteLine(text) cout<<text<<endl

// 链表测试
void link_node_test() {
	LinkNode<int>* list = new LinkNode<int>();
	list->add(333);
	list->add(555);
	list->add(111);
	list->add(111);
	list->add(333);
	list->add(222);
	list->add(444);
	list->add(222);
	WriteLine("<---------原链表--------->");
	list->print_all();
	WriteLine("<---------list->sort();--------->");
	list->sort();
	list->print_all();
	WriteLine("<---------delete_by_position(1);--------->");
	list->delete_by_position(1);
	list->print_all();
	WriteLine("<---------remove_all(222);--------->");
	list->remove_all(222);
	list->print_all();
	WriteLine("<---------insert_after(2, 83);--------->");
	list->insert_after(2, 83);
	list->print_all();
	WriteLine("<---------contain()--------->");
	cout << "contain(111):" << list->contain(111) << endl;
	cout << "contain(222):" << list->contain(222) << endl;
	WriteLine("<---------list->find_first(111) = 100;--------->");
	list->find_first(111) = 100;
	list->print_all();
	WriteLine("<---------foreach--------->");
	list->foreach([](int& value)->void {
		cout << value << endl;
		});
	cout << "链表长度：" << list->length() << endl;
	WriteLine("<---------list->clear()  list->add(666)--------->");
	list->clear();
	list->add(666);
	list->print_all();
	cout << "链表长度：" << list->length() << endl;
	delete list;
}


// 一元多项式表示，求值
class item {
public:
	int cons;
	int ex;
	item(int cons,int ex):cons(cons),ex(ex){}
	item():cons(0),ex(0){}
	bool operator>(item& it) {
		if (this->ex > it.ex) {
			return true;
		}
		else {
			return false;
		}
	}
};
void univariate_polynomial() {
	LinkNode<item>* items_1 = new LinkNode<item>();
	WriteLine("输入多项式项数:");
	int item_num;
	cin >> item_num;
	WriteLine("分别输入系数和指数");
	for (int i = 0; i < item_num; i++) {
		int cons, ex;
		cin >> cons >> ex;
		items_1->foreach([&](item& value)->void {
			if (value.ex == ex) {
				value.cons += cons;
				cons = 0;
			}
			});
		if (cons != 0) {
			items_1->add(item(cons, ex));
		}
	}
	items_1->sort();
	WriteLine("多项式为：");
	items_1->foreach([](item& value)->void{
		if (value.cons > 0) { 
			cout << "+" << value.cons << "x^" << value.ex;
		}
		else {
			cout << value.cons << "x^" << value.ex;
		}
	});
	cout << endl;
	WriteLine("输入x的取值");
	float x;
	cin >> x;
	float result = 0;
	items_1->foreach([&](item& value)->void {
		result += value.cons * pow(x, value.ex);
	});
	cout << "结果为:" << result << endl;
	
	delete items_1;
}

int main() {
	link_node_test();
	univariate_polynomial();
}