#pragma once
#include <iostream>
#include <string>
#include <sstream>

template < class T, class S >
class BST {

	typedef std::pair<T, S> value_type; // a pair value key	

private:
	class Node {
	public:
		T data;
		S key;
		Node * left;
		Node * right;
		Node * parent;
		Node(const value_type val) : data(val.first), key(val.second), left(NULL), right(NULL), parent(NULL) {};
		~Node() { delete left; delete right; }
	};

	Node * root;
	Node * leftMost;

public:
	

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
		iterator() {}
		self_type operator++(int);
		self_type& operator++() {
			if (traverse->right != NULL) { // if you can go right go
				traverse = traverse->right;
				while (traverse->left != NULL) // go left as much as you can
					traverse = traverse->left;

				return *this;
			}
			else{
				Node * temp=traverse;
				while (traverse->parent != NULL) {
					traverse = traverse->parent;
					if (traverse->left == temp) {
						return *this;
					}
					else
						temp = traverse;
				}
				traverse = traverse->parent;
				return *this;
			}
		}
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
	std::pair<typename BST<T,S>::iterator, bool> insert(const value_type& val); // return false if the key already exists and the iterator points to the new element or the key location
	int erase(const S& k);
	void erase(typename BST<T, S>::iterator it);
	typename BST<T, S>::iterator find(const S& k);

	Node * begin() {
		Node * temp = root;
		while (temp->left != NULL)
			temp = temp->left;

		return temp;
	}

	Node * end() { return NULL; }
	std::string toString();

	typedef int size_type;

	template <class R, class U>
	friend std::ostream& operator<< (std::ostream& stream, BST<R, U>& tree);
};


