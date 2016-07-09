#pragma once
#include <iostream>
#include <string>
#include <sstream>

template < class T, class S >
class BST {

private:
	class Node {
	public:
		T data;
		S key;
		Node * left;
		Node * right;
		Node * parent;
		Node(const T d, const S e) : data(d), key(e), left(NULL), right(NULL), parent(NULL) {};
		~Node() {};
	};

	Node * root;
	Node * leftMost;

public:
	typedef std::pair<T, S> value_type; // a pair value key

	class iterator
	{
	public:
		typedef iterator self_type;
		typedef Node value_type;
		typedef Node& reference;
		typedef Node* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		iterator(pointer ptr) : traverse(ptr) { }
		self_type operator++(int);
		self_type& operator++();
		self_type operator+(const int& pos);
		reference operator*() { return *traverse; }
		pointer operator->() { return traverse; }
		bool operator==(const self_type& rhs) { return traverse == rhs.traverse; }
		bool operator!=(const self_type& rhs) { return traverse != rhs.traverse; }
	private:
		pointer traverse;
	};

	int size;
	BST() : root(NULL), leftMost(NULL), size(0) {};
	~BST();
	std::pair<BST<T, S>::iterator, bool> insert(const value_type& val); // return false if the key already exists and the iterator points to the new element or the key location
	void erase(S k);
	void erase(BST<T, S>::iterator it);
	BST<T, S>::iterator find(S k);

	Node * begin() { return leftMost; }
	Node * end() { return NULL; }
	std::string toString();

	typedef int size_type;

	template <class R, class U>
	friend std::ostream& operator<< (std::ostream& stream, BST<R, U>& tree);
};


