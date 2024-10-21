#pragma once

template<class T>
class Node {
public:
	T value;
	Node* next;
	Node(T value);
};


template<class T>
class Stack {
private:
	Node<T>* _top = nullptr;
	int _length = 0;
public:
	Stack();
	~Stack();
	T pop();
	T& top();
	void push(T value);
	void clear();
	int length();
};

template<class T>
class Queue {
private:
	Node<T>* _head;
	int _length = 0;
public:
	Queue();
	~Queue();
	void add(T value);
	T get();
	T& head();
	void clear();
	int length();
};

template<class T>
inline Node<T>::Node(T value)
{
	this->next = nullptr;
	this->value = value;
}

template<class T>
inline Stack<T>::Stack()
{
	this->_top = nullptr;
}

template<class T>
inline Stack<T>::~Stack()
{
	this->clear();
}

template<class T>
inline T Stack<T>::pop()
{
	if (this->_top == nullptr)return T();
	T value = this->_top->value;
	if (this->_top != nullptr) {
		Node<T>* deleted = this->_top;
		this->_top = this->_top->next;
		delete deleted;
		_length--;
	}
	return value;
}

template<class T>
inline T& Stack<T>::top()
{
	if (this->_top != nullptr) {
		return this->_top->value;
	}
}

template<class T>
inline void Stack<T>::push(T value)
{
	Node<T>* newNode = new Node<T>(value);
	newNode->next = this->_top;
	this->_top = newNode;
	_length++;
}

template<class T>
inline void Stack<T>::clear()
{
	while (_length > 0) {
		this->pop();
	}
}

template<class T>
inline int Stack<T>::length()
{
	return _length;
}

template<class T>
inline Queue<T>::Queue()
{
	this->_head = nullptr;
}

template<class T>
inline Queue<T>::~Queue()
{
	this->clear();
}

template<class T>
inline void Queue<T>::add(T value)
{
	Node<T>* newNode = new Node<T>(value);
	if (this->_head == nullptr) {
		newNode->next = this->_head;
		this->_head = newNode;
	}
	else {
		Node<T>* last = this->_head;
		while (last->next != nullptr) {
			last = last->next;
		}
		last->next = newNode;
	}
	_length++;
}

template<class T>
inline T Queue<T>::get()
{
	T value;
	if (this->_head != nullptr) {
		value = this->_head->value;
		Node<T>* deleted = this->_head;
		this->_head = this->_head->next;
		delete deleted;
		_length--;
	}
	else {
		value = T();
	}
	return value;
}

template<class T>
inline T& Queue<T>::head()
{
	if (this->head != nullptr) {
		return this->_head->value;
	}
	else {
		return T();
	}
}

template<class T>
inline void Queue<T>::clear()
{
	while (_length > 0) {
		this->get();
	}
}

template<class T>
inline int Queue<T>::length()
{
	return _length;
}
