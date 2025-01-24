#ifndef __NODE_H__
#define __NODE_H__

#include <cstddef>				// 含NULL的声明（stddef.h与cstddef是C的头文件）

// 结点类模板
template <class ElemType>
struct Node 
{
// 数据成员:
	ElemType data;				// 数据成分
	Node<ElemType> *next;		// 指针成分

// 构造函数模板:
	Node();						// 无参数的构造函数模板
	Node(const ElemType &e, Node<ElemType> *link = NULL);	// 已知数据元素值和指针建立结点
};

// 结点类模板的实现部分
template<class ElemType>
Node<ElemType>::Node()
// 操作结果：构造指针成分为空的结点
{
	next = NULL;
}

template<class ElemType>
Node<ElemType>::Node(const ElemType &e, Node<ElemType> *link)
// 操作结果：构造一个数据成分为e和指针成分为link的结点
{
	data = e;
	next = link;
}

#endif
