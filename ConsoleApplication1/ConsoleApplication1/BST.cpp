#include "BST.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

template<class T, class S>
BST<T, S>::~BST() {
	delete this->root;
}

template<class T, class S>
std::pair<typename BST<T, S>::iterator, bool> BST<T, S>::insert(const value_type & val)
{
	Node * nw = new Node(val);
	BST<T, S>::iterator iter(this->root);

	if (size == 0) {
		root = nw;
		iter = nw;
		std::cout << "insert size 0" << std::endl;
		size++;
		return std::make_pair(iter,true);
	}

	while (true) {

		if (val.second > iter->key)
			if (iter->right != NULL)
				iter = iter->right;
			else {
				iter->right = nw;
				nw->parent = &(*iter);
				iter = nw;
				size++;
				std::cout << "insert right" << std::endl;
				return std::make_pair(iter, true);
			}

		else if (val.second < iter->key)
			if (iter->left != NULL)
				iter = iter->left;
			else {
				iter->left = nw;
				nw->parent = &(*iter);
				iter = nw;
				size++;
				std::cout << "insert left" << std::endl;
				return std::make_pair(iter, true);
			}
		else {
			delete nw;
			return std::make_pair(iter, false); // no insertion position of the key
		}
	}
	//return std::make_pair(iter, false);
}

template <class T, class S>
std::ostream& operator<< (std::ostream& os, BST<T, S>& link) {
	os << link.toString();
	return os;
}

template <class T, class S>
std::string BST<T, S>::toString() {
	std::stringstream os;
	BST<T, S>::iterator iter(this->begin());

	os << "{";
	for (iter = this->begin(); iter != this->end(); ++iter) {
		os << iter->data <<",";
	}
	std::streamoff	 pos = os.tellp();
	if (size != 0)
		os.seekp(pos - 1);

	os << "}";
	return os.str();
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	BST<int,int> p;
	int temp;
	for (int i = 1; i<=20; i++) {
		temp = rand() % 20 + i;
		if (!p.insert(std::make_pair(i, temp)).second)
			std::cout << "the key "<<temp<<" already exists" << std::endl;
		else
			std::cout << "inserting key " << temp << std::endl;
	}
	std::cout << p << std::endl;
	return 0;
}