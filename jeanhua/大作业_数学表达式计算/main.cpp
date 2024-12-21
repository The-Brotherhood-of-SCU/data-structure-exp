#include "calculator.h"
#include<iostream>
using namespace std;

int main()
{
	Calculator<int> c;
	bool cont = true;
	while (cont)
	{
		cout<<"输入表达式，以等于(=)结尾"<<endl;
		c.Run();
		cout << "是否继续？(y/n)" << endl;
		char i;
		cin >> i;
		if (i == 'y')continue;
		else
		{
			break;
		}
	}
}