#include "calculator.h"
#include<iostream>
using namespace std;

int main()
{
	Calculator<int> c;
	bool cont = true;
	while (cont)
	{
		c.Run();
		cout << "�Ƿ������(y/n)" << endl;
		char i;
		cin >> i;
		if (i == 'y')continue;
		else
		{
			break;
		}
	}
}