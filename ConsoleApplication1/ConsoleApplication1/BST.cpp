#include "BST.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

template<class T, class S>
BST<T, S>::~BST() {
	delete this->root;
}

template<class T, class S>
typename BST<T, S>::iterator BST<T,S>::find(const S& k) {
	BST<T, S>::iterator iter(this->root);

	while (iter->left != NULL || iter->right != NULL) {
		if (iter->key < k)
			if (iter->right != NULL)
				iter = iter->right;
			else {
				iter = NULL;
				return iter;
			}
		else if (iter->key > k)
			if (iter->left != NULL)
				iter = iter->left;
			else {
				iter = NULL;
				return iter;
			}
		else
			return iter;
	}

	if(iter->key==k)
	return iter;
	else {
		iter = NULL;
		return iter;
	}
}


template<class T, class S>
void BST<T, S>::erase(typename BST<T, S>::iterator iter) {
	if (iter->left == NULL && iter->right == NULL) { // no children
		Node * temp = iter->parent;
		if (iter->parent == NULL) { // its the root
			temp = &(*iter);
			delete temp;
			root = NULL;
			iter = root;
			size--;
			return;
		}
		else {
			if (temp->left == &(*iter))//its a left child
				temp->left = NULL;
			else
				temp->right = NULL; //its a right child

			temp = &(*iter);
			iter = iter->parent;
			temp->left = NULL;
			temp->right = NULL;
			temp->parent = NULL;
			delete temp;
			size--;
			return;
		}
	}
	if (iter->right == NULL ) { // only a left child
		Node * temp = iter->parent; 
		if (temp != NULL) {
			if (temp->left == &(*iter))
				temp->left = iter->left;
			else
				temp->right = iter->left;

			Node * temp2 = iter->left;
			temp2->parent = temp;
			temp = &(*iter);
			iter = iter->left;
			temp->left = NULL;
			temp->right = NULL;
			temp->parent = NULL;
			delete temp;
			size--;
			return;
		}
		else { //its the root
			root = iter->left;
			iter->left = NULL;
			root->parent = NULL;
			temp = &(*iter);
			iter = root;
			delete temp;
			size--;
			return;
		}
	}
	if (iter->left == NULL) { // only a right child
		Node * temp = iter->parent;
		if (temp != NULL) {
			if (temp->left == &(*iter))
				temp->left = iter->right;
			else
				temp->right = iter->right;

			Node * temp2 = iter->right;
			temp2->parent = temp;
			temp = &(*iter);
			iter = iter->right;
			temp->left = NULL;
			temp->right = NULL;
			temp->parent = NULL;
			delete temp;
			size--;
			return;
		}
		else { // its the root
			root = iter->right;
			root->parent = NULL;
			iter->right = NULL;
			temp = &(*iter);
			iter = root;
			delete temp;
			size--;
			return;
		}
	}

	// both children, we dont need to handle root
	Node * temp = iter->right;
	while (temp->left != NULL)
		temp = temp->left;
	//now temp points to the successor	
	iter->data = temp->data;
	iter->key = temp->key;
	Node *temp2;
	temp2 = temp->parent;
	if (temp2->left == temp) {
		temp2->left = temp->right;
		if (temp->right != NULL)
			temp->right->parent = temp2;
	}
	else {
		temp2->right = temp->right; // select right subtree
		if(temp->right!=NULL)
			temp->right->parent = temp2;
	}
	temp->left = NULL;	// the destructor is recursive, you need to null the connections
	temp->right = NULL;
	delete temp; //remove node
	size--;
}

template<class T, class S>
int BST<T, S>::erase(const S& k) {
	BST<T, S>::iterator iter;
	iter = this->find(k);
	if (iter == NULL) {
		std::cout << "didnt find" << std::endl;
		return 0;
	}
	else
		this->erase(iter);

	return 1;
}

template<class T, class S>
std::pair<typename BST<T, S>::iterator, bool> BST<T, S>::insert(const value_type & val)
{
	Node * nw = new Node(val);
	BST<T, S>::iterator iter(this->root);

	if (size == 0) {
		root = nw;
		iter = nw;
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
				return std::make_pair(iter, true);
			}
		else {
			delete nw;
			return std::make_pair(iter, false); // no insertion position of the key
		}
	}
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
	for (iter = this->begin(); iter != this->end(); iter++) {
		if (iter->left != NULL)
			os << iter->left->key << "<-";
		os << iter->key;
		if (iter->right != NULL)
			os << "->"<< iter->right->key;
		os <<",";
	}
	std::streamoff	 pos = os.tellp();
	if (size != 0)
		os.seekp(pos - 1);

	os << "}";
	return os.str();
}

template <class T,class S>
void BST<T, S>::RightRotation(typename BST<T, S>::iterator iter) {
	Node * temp = iter->left; //pivot P 
	iter->left = temp->right; // Q takes right subtree of pivot on left
	if(temp->right!=NULL)
		temp->right->parent = &(*iter); // assign parent
	temp->parent = iter->parent; // change the parent of pivot
	if (iter->parent != NULL) { // if not null
		if (iter->parent->right == &(*iter))
			iter->parent->right = temp; //set child
		else
			iter->parent->left = temp;
	}
	else // its the root node
		root = temp;
	temp->right = &(*iter); // attach Q to the pivot
	iter->parent = temp; // reassign parent
	iter = temp; //move iterator
}

template <class T, class S>
void BST<T, S>::LeftRotation(typename BST<T, S>::iterator iter) {
	Node * temp = iter->right; //pivot Q 
	iter->right = temp->left; // P takes right subtree of pivot on right
	if (temp->left != NULL)
		temp->left->parent = &(*iter); // assign parent
	temp->parent = iter->parent; // change the parent of pivot
	if (iter->parent != NULL) { // if not null
		if (iter->parent->right == &(*iter))
			iter->parent->right = temp; //set child
		else
			iter->parent->left = temp;
	}
	else // its the root node
		root = temp;
	temp->left = &(*iter); // attach Q to the pivot
	iter->parent = temp; // reassign parent
	iter = temp; //move iterator
}

int main(int argc, char* argv[])
{
	srand((unsigned int) time(NULL));
	BST<int,int> p;
	int temp;
	for (int i = 1; i<=10; i++) {
		temp = rand() % 50 + i;
		if (!p.insert(std::make_pair(i, temp)).second)
			std::cout << "the key "<<temp<<" already exists" << std::endl;
		else
			std::cout << "inserting key " << temp << std::endl;
	}
	std::cout << p << std::endl;
	std::cout << "rotate one node" << std::endl;
	int nod;
	std::cin >> nod;
	p.LeftRotation(p.find(nod));
	std::cout << p << std::endl;
	return 0;
}