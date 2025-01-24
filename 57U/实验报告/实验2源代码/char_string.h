#ifndef __CharString_H__
#define __CharString_H__

#include <cstddef>														// 含NULL的声明（stddef.h与cstddef是C的头文件）
#include <iostream>														// 编译预处理命令
#include <cstring>														// 包含C函数strlen()和strcmp()的声明（string.h与cstring是C的头文件）
#include <cstdio>														// 包含EOF的声明（stdio.h与cstdio是C的头文件）
using namespace std;													// 使用命名空间std
#include "lk_list.h"                                                    // 线性链表

// 串类
class CharString 
{
protected:
// 数据成员:
	mutable char *strVal;												// 串值
	int length;															// 串长	

public:                           
// 抽象数据类型方法和相关方法声明及重载编译系统默认方法声明:
	CharString();														// 构造函数 
	virtual ~CharString();												// 析构函数
	CharString(const CharString &source);								// 复制构造函数
	CharString(const char *source);										// 从C风格串转换的构造函数
	CharString(LinkList<char> &source);									// 从线性表转换的构造函数
	int Length() const;													// 求串长度			 
	bool Empty() const;													// 判断串是否为空
	CharString &operator =(const CharString &source);					// 重载赋值运算符
	const char *ToCStr() const { return (const char *)strVal; }			// 将串转换成C风格串
	char &operator [](int pos) const;									// 重载下标运算符
};

// 串相关操作
CharString Read(istream &input);										// 从输入流读入串
CharString Read(istream &input, char &terminalChar);					// 从输入流读入串，并用terminalChar返回串结束字符
void Write(const CharString &s);										// 输出串
char *CStrConcat(char *target, const char *source);						// C风格将串source连接到串target的后面
void Concat(CharString &target, const CharString &source);				// 将串source连接到串target的后面
char *CStrCopy(char *target, const char *source);						// C风格将串source复制到串target
void Copy(CharString &target, const CharString &source);				// 将串source复制到串target
void Copy(CharString &target, const CharString &source);				// 将串source复制到串target
char *CStrCopy(char *target, const char *source, int n);				// C风格将串source复制n个字符到串target 
void Copy(CharString &target, const CharString &source, int n);			// 将串source复制n个字符到串target 
int Index(const CharString &target, const CharString &pattern, int pos = 0);// 查找模式串pattern第一次在目标串target中从第pos个字符开始出现的位置
CharString SubString(const CharString &s, int pos, int len);		// 求串s的第pos个字符开始的长度为len的子串
bool operator ==(const CharString &first, const CharString &second);	// 重载关系运算符==
bool operator <(const CharString &first, const CharString &second);		// 重载关系运算符<
bool operator >(const CharString &first, const CharString &second);		// 重载关系运算符>
bool operator <=(const CharString &first, const CharString &second);	// 重载关系运算符<=
bool operator >=(const CharString &first, const CharString &second);	// 重载关系运算符>=
bool operator !=(const CharString &first, const CharString &second);	// 重载关系运算符!=

// 串类及相关操作的实现部分
CharString::CharString()
//  操作结果：初始化串 
{
	length = 0;															// 串长度为0
	strVal = NULL;														// 空串
}

CharString::~CharString()
// 操作结果：销毁串，释放串所占用空间
{
	delete []strVal;													// 释放串strVal
}

CharString::CharString(const CharString &source)
// 操作结果：由串source构造新串——复制构造函数
{
	length = strlen(source.ToCStr());									// 串长
	strVal = new char[length + 1];										// 分配存储空间
	CStrCopy(strVal, source.ToCStr());									// 复制串值
}

CharString::CharString(const char *source)
// 操作结果：从C风格串转换构造新串——转换构造函数
{
	length = strlen(source);											// 串长
	strVal = new char[length + 1];										// 分配存储空间 
	CStrCopy(strVal, source);											// 复制串值
}

CharString::CharString(LinkList<char> &source)
// 操作结果：从线性表转换构造新串——转换构造函数
{
	length = source.Length();											// 串长
	strVal = new char[length + 1];										// 分配存储空间 
	for (int pos = 0; pos < length; pos++) 
	{	// 复制串值
		source.GetElem(pos + 1, strVal[pos]);
	}
	strVal[length] = '\0';												// 串值以'\0'结束	
}

int CharString::Length() const
// 操作结果：返回串长度			 
{
	return length;
}

bool CharString::Empty() const
// 操作结果：如果串为空，返回true，否则返回false
{
	return length == 0;
}

CharString &CharString::operator =(const CharString &source)
// 操作结果：重载赋值运算符
{
	if (&source != this)
	{
		delete []strVal;												// 释放原串存储空间
		length = strlen(source.ToCStr());								// 串长
		strVal = new char[length + 1];									// 分配存储空间 
		CStrCopy(strVal, source.ToCStr());								// 复制串值
	}
	return *this;
}

char &CharString::operator [](int pos) const
// 操作结果：重载下标运算符
{
	return strVal[pos];
}

CharString Read(istream &input)
// 操作结果：从输入流读入串
{
	LinkList<char> temList;												// 临时线性表
	char ch;															// 临时字符
	while ((ch = input.peek()) != EOF &&								// peek()从输入流中取一个字符,输入流指针不变
		(ch = input.get()) != '\n')										// get()从输入流中取一个字符,输入流指针指向下一字符
	{	// 将输入的字符追加线性表中
		temList.Insert(temList.Length() + 1, ch);
	}
	return temList;														// 返回由temList生成的串
}

CharString Read(istream &input,char &terminalChar)
// 操作结果：从输入流读入串，并用terminalChar返回串结束字符
{
	LinkList<char> temList;												// 临时线性表
	char ch;															// 临时字符
	while ((ch = input.peek()) != EOF &&								// peek()从输入流中取一个字符,输入流指针不变
		(ch = input.get()) != '\n')										// get()从输入流中取一个字符,输入流指针指向下一字符
	{	// 将输入的字符追加线性表中
		temList.Insert(temList.Length() + 1, ch);
	}
	terminalChar = ch;													// 用terminalChar返回串结束字符
	return temList;														// 返回由temList生成的串
}

void Write(const CharString &s)
// 操作结果：输出串
{
	cout << s.ToCStr() << endl;											// 输出串值
}

char* CStrConcat(char *target, const char *source)
// 操作结果：C风格将串source连接到串target的后面
{
	char *tar = target + strlen(target);								// tar指向target的结尾处
	while((*tar++ = *source++) != '\0');								// 逐个字符连接到target的后面，直到'\0'为止
	return target;														// 返回target
}

void Concat(CharString &target, const CharString &source)
// 操作结果：将串source连接到串target的后面
{
	const char *cFirst = target.ToCStr();								// 指向第一个串
	const char *cSecond = source.ToCStr();								// 指向第二个串
	char *cTarget = new char[strlen(cFirst) + strlen(cSecond) + 1];		// 分配存储空间
	CStrCopy(cTarget, cFirst);											// 复制第一个串
	CStrConcat(cTarget, cSecond);										// 连接第二个串
	target = cTarget;													// 串赋值
	delete []cTarget;													// 释放cTarget
}

char *CStrCopy(char *target, const char *source)						// 将串source复制到串target
// 操作结果：C风格将串source复制到串target
{
	char *tar = target;													// 暂存target
	while((*tar++ = *source++) != '\0');								// 逐个字符进行复制，直到'\0'为止
	return target;														// 返回target
}

void Copy(CharString &target, const CharString &source)
// 操作结果：将串source复制到串target
{
	const char *cSource = source.ToCStr();								// 初始串
	char *cTarget = new char[strlen(cSource) + 1];						// 分配存储空间
	CStrCopy(cTarget, cSource);											// 复制串
	target = cTarget;													// 串赋值
	delete []cTarget;													// 释放串cTarget
}

char *CStrCopy(char *target, const char *source, int n)
// 操作结果：C风格将串source复制n个字符到串target 
{
	int len = (int)strlen(source) < n ? (int)strlen(source) : n;		// 目标串长
	for (int pos = 0; pos < len; pos++) target[pos] = source[pos];		// 逐个字符进行复制
	target[len] = '\0';													// 串结束符
	return target;														// 返回target
}

void Copy(CharString &target, const CharString &source, int n)
// 操作结果：将串source复制n个字符到串target 
{
	const char *cSource = source.ToCStr();								// 初始串
	int len = (int)strlen(cSource) < n ? (int)strlen(cSource) : n;		// 目标串长
	char *cTarget = new char[len + 1];									// 分配存储空间
	CStrCopy(cTarget, cSource, n);										// 复制串
	target = cTarget;													// 串赋值
	delete []cTarget;													// 释放串cTarget
}

int Index(const CharString &target, const CharString &pattern, int pos)
// 操作结果：如果匹配成功，返回模式串pattern第一次在目标串target中从第pos
//	个字符开始出现的位置, 否则返回-1
{
	const char *cTarget = target.ToCStr();								// 目标串
	const char *cPattern = pattern.ToCStr();							// 模式串
	const char *ptr=strstr(cTarget + pos, cPattern);					// 模式匹配
	if (ptr == NULL)
	{	// 匹配失败	
		return -1; 
	}
	else
	{	// 匹配成功	
		return ptr - cTarget;
	}
}

CharString SubString(const CharString &s, int pos, int len)
// 初始条件：串s存在，0 <= pos < s.Length()且0 <= len <= s.Length() - pos
// 操作结果：返回串s的第pos个字符开始的长度为len的子串
{
	if (0 <= pos && pos < s.Length() && 0 <= len)
	{	// 返回串s的第pos个字符开始的长度为len的子串
		len = (len < s.Length() - pos) ? len : (s.Length() - pos);		// 子串长
		char *sub = new char[len + 1];									// 分配存储空间
		const char *str = s.ToCStr();									// 生成C风格串
		CStrCopy(sub, str + pos, len);									// 复制串
		return sub;														// 返回子串sub
	}
	else
	{	// 返回空串
		return "";														// 返回空串
	}
}

bool operator ==(const CharString &first, const CharString &second)
// 操作结果：重载关系运算符==
{
	return strcmp(first.ToCStr(), second.ToCStr()) == 0;
}

bool operator <(const CharString &first, const CharString &second)
// 操作结果：重载关系运算符<
{
	return strcmp(first.ToCStr(), second.ToCStr()) < 0;
}

bool operator >(const CharString &first, const CharString &second)
// 操作结果：重载关系运算符>
{
	return strcmp(first.ToCStr(), second.ToCStr()) > 0;
}

bool operator <=(const CharString &first, const CharString &second)
// 操作结果：重载关系运算符<=
{
	return strcmp(first.ToCStr(), second.ToCStr()) <= 0;
}

bool operator >=(const CharString &first, const CharString &second)
// 操作结果：重载关系运算符>=
{
	return strcmp(first.ToCStr(), second.ToCStr()) >= 0;
}

bool operator !=(const CharString &first, const CharString &second)
// 操作结果：重载关系运算符!=
{
	return strcmp(first.ToCStr(), second.ToCStr()) != 0;
}


#endif