#include<iostream>
#include<stack>
#include<cmath>
using namespace std;

template<class T>
class  Calculator
{
private:
	stack<T> opnd;
	stack<char> optr;

	char Getchar();
	int operPrior(char op);
	void get2Operands(T& left, T& right);
	T operate(T left, char op, T right);
	bool isOperator(char ch);

public:
	Calculator() {};
	virtual ~Calculator() {};
	void Run();
};

template<class T>
inline char Calculator<T>::Getchar()
{
	char ch;
	cin >> ch;
	return ch;
}

template<class T>
inline int Calculator<T>::operPrior(char op)
{
	switch (op)
	{
	case'=':
		return 1;
	case '(':
	case ')':
		return 2;
	case  '+':
	case'-':
		return 3;
	case '*':
	case '/':
	case '%':
		return 4;
	case '^':
		return 5;
	default:
		return 0;
	}
}

template<class T>
inline void Calculator<T>::get2Operands(T& left, T& right)
{
	if (opnd.size() > 1) {
		right = opnd.top();
		opnd.pop();
		left = opnd.top();;
		opnd.pop();
	}
	else {
		throw "����ʽ����!";
	}
}

template<class T>
inline T Calculator<T>::operate(T left, char op, T right)
{
	switch (op)
	{
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left * right;
	case '/':
		if (right == 0)throw "��������Ϊ0";
		return left / right;
	case '^':
		return pow(left, right);
	case '%':
		if (is_integral<T>::value) {
			return left % right;
		}
		else {
			throw "ȡģ����ֻ����������";
		}
	}
}

template<class T>
inline bool Calculator<T>::isOperator(char ch)
{
	if (operPrior(ch) > 0) {
		return true;
	}
	else {
		return false;
	}
}

template<class T>
inline void Calculator<T>::Run()
{
	while (optr.empty() == false)
	{
		optr.pop();
	}
	while (opnd.empty() == false)
	{
		opnd.pop();
	}
	optr.push('=');
	char ch;
	char priorChar;
	char optrTop;
	T operand;
	char op;
	priorChar = '=';
	ch = Getchar();
	if (optr.empty())throw "����ʽ����!";
	optrTop = optr.top();

	while (optrTop != '=' || ch != '=')
	{
		if (isdigit(ch) || ch == '.')
		{
			cin.putback(ch);
			cin >> operand;
			opnd.push(operand);
			priorChar = '0';
			ch = Getchar();
		}
		else  if (!isOperator(ch))
		{
			throw "����ʽ����!";
		}
		else
		{
			if ((priorChar == '=' || priorChar == '(') && (ch == '+' || ch == '-'))
			{
				opnd.push(0);
				priorChar = '0';
			}
			if (optrTop == ')' && ch == '(' || optrTop == '(' && ch == '=' || optrTop == '=' && ch == ')')throw "�����ϴ���!";
			else if (optrTop == '(' && ch == ')')
			{
				if (optr.empty())throw "����ʽ����!";
				optrTop = optr.top();
				optr.pop();
				ch = Getchar();
				priorChar = ')';
			}
			else if (ch == '(' || operPrior(optrTop) < operPrior(ch))
			{
				optr.push(ch);
				priorChar = ch;
				ch = Getchar();
			}
			else
			{
				if (optr.empty())
					throw "����ʽ����!";
				op = optr.top();
				optr.pop();
				T left, right;
				get2Operands(left, right);
				opnd.push(operate(left, op, right));
			}
		}
		if (optr.empty())throw "����ʽ����!";
		optrTop = optr.top();
	}
	if (opnd.empty())throw "����ʽ����!";
	operand = opnd.top();
	cout << operand << endl;
}
