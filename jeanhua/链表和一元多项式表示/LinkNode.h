#pragma once
#include<iostream>
#include<functional>

template<class T>class LinkNode;
template<class T>class Node;

template<class T>
class Node {
	friend class LinkNode<T>;
public:
	T value;
private:
	Node* next;
	Node(T data);
	Node();
};

template<class T>
class LinkNode {
private:
	// ����ͷ
	Node<T>* head;
	// ������
	int _length = 0;
public:
	// ���캯������ʼ������
	LinkNode();
	// ��������
	~LinkNode();
	// ȡ������
	int length();
	// ��ӽڵ�
	void add(T data);
	// ɾ����һ��ƥ��Ľڵ�
	bool remove_first(T data);
	// ɾ������ƥ��Ľڵ�
	void remove_all(T data);
	// �����ɾ���ڵ�
	bool delete_by_position(int position);
	// Ѱ�ҵ�һ��ƥ��Ľڵ�
	T& find_first(T data);
	// ����
	void foreach(std::function<void(T& value)> expression);
	// ����ð�ݣ�
	void sort();
	// ����Ų���ڵ�
	bool insert_after(int position, T data);
	// ��ӡȫ��
	void print_all();
	// �ж��Ƿ����ĳ�ڵ�
	bool contain(T data);
	// ɾ��ȫ���ڵ�
	void clear();
};


template<class T>
Node<T>::Node(T data) {
	this->value = data;
	this->next = nullptr;
}

template<class T>
Node<T>::Node() {
	this->next = nullptr;
}

template<class T>
LinkNode<T>::LinkNode() {
	head = new Node<T>();
}

template<class T>
inline LinkNode<T>::~LinkNode()
{
	this->clear();
	delete this->head;
	this->head = nullptr;
}

template<class T>
int LinkNode<T>::length() {
	return _length;
}

template<class T>
void LinkNode<T>::add(T data) {
	Node<T>* node = new Node<T>(data);
	Node<T>* endNode = this->head;
	while (endNode->next != nullptr) {
		endNode = endNode->next;
	}
	endNode->next = node;
	_length++;
}

template<class T>
bool LinkNode<T>::remove_first(T data) {
	Node<T>* node = this->head;
	while (node->next != nullptr) {
		if (node->next->value == data) {
			Node<T>* deletedNode = node->next;
			node->next = node->next->next;
			delete deletedNode;
			deletedNode = nullptr;
			_length--;
			return true;
		}
		else
		{
			node = node->next;
		}
	}
	return false;
}

template<class T>
void LinkNode<T>::remove_all(T data) {
	Node<T>* node = this->head;
	while (node->next != nullptr) {
		if (node->next->value == data) {
			Node<T>* deletedNode = node->next;
			node->next = node->next->next;
			delete deletedNode;
			deletedNode = nullptr;
			_length--;
		}
		else
		{
			node = node->next;
		}
	}
}

template<class T>
inline bool LinkNode<T>::delete_by_position(int position)
{
	if (position > _length || position <= 0) {
		return false;
	}
	int index = 0;
	for (Node<T>* node = this->head; node != nullptr; node = node->next) {
		if (position == index + 1) {
			Node<T>* node_deleted = node->next;
			node->next = node->next->next;
			delete node_deleted;
			return true;
		}
		index++;
	}
	return false;
}

template<class T>
T& LinkNode<T>::find_first(T data) {
	Node<T>* node = this->head;
	while (node->next != nullptr) {
		if (node->value == data) {
			return node->value;
		}
		node = node->next;
	}
}

template<class T>
void LinkNode<T>::foreach(std::function<void(T& value)> expression) {
	if (_length == 0)return;
	for (Node<T>* node = this->head->next; node != nullptr; node = node->next) {
		expression(node->value);
	}
}

template<class T>
inline void LinkNode<T>::sort()
{
	Node<T>* end = this->head->next;
	while (end->next!=nullptr){
		end = end->next;
	}
	while (end != this->head->next) {
		for (Node<T>* node = this->head->next; node != end; node = node->next) {
			if (node->value > node->next->value) {
				T swap_value = node->value;
				node->value = node->next->value;
				node->next->value = swap_value;
			}
		}
		Node<T>* now = end;
		end = this->head->next;
		while (end->next != now) {
			if (end == now)break;
			end = end->next;
		}
	}
}

template<class T>
bool LinkNode<T>::insert_after(int position, T data) {
	int i = 0;
	if (this->_length < position)return false;
	if (position < 0)return false;
	if (position == _length) {
		add(data);
		return true;
	}
	for (Node<T>* node = this->head; node->next != nullptr; node = node->next) {
		if (i < position) {
			i++;
			continue;
		}
		Node<T>* newNode = new Node<T>(data);
		newNode->next = node->next;
		node->next = newNode;
		_length++;
		return true;
	}
	return false;
}

template<class T>
void LinkNode<T>::print_all() {
	for (Node<T>* node = this->head->next; node != nullptr; node = node->next) {
		std::cout << node->value << std::endl;
	}
}

template<class T>
bool LinkNode<T>::contain(T data) {
	Node<T>* node = this->head->next;
	while (node != nullptr)
	{
		if (node->value == data) {
			return true;
		}
		node = node->next;
	}
	return false;
}

template<class T>
void LinkNode<T>::clear() {
	Node<T>* node = this->head->next;
	while (node != nullptr)
	{
		Node<T>* deletedNode = node;
		node = node->next;
		delete deletedNode;
		deletedNode = nullptr;
	}
	this->head->next = nullptr;
	_length = 0;
}