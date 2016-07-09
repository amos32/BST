#include "BST.h"

template<class T, class S>
void BST<T, S>::insert(T ob, S k) {
	Node * nw = new Node(ob);
	Node * temp;
	LinkedList<T>::iterator iter(this->begin());

	if (pos == 0) {
		nw->next = this->begin();
		this->head = nw;
		size++;
	}
	else {
		iter + (pos - 1);
		temp = iter->next;
		nw->next = temp;
		iter->next = nw;
		size++;
	}
}

template<class T, class S>
void BST<T, S>::remove(S k) {
	LinkedList<T>::iterator iter(this->begin());
	Node* temp;
	if (pos == 0) {
		temp = &(*iter);
		this->head = temp->next;
		delete temp;
		size--;
	}
	else {
		iter + (pos - 1);
		temp = iter->next;
		iter->next = temp->next;
		delete temp;
		size--;
	}
}


template<class T, class S>
BST<T, S>::~BST() {
	Node * traverse = head;
	Node * current = head;

	for (int i = 0; i<size; i++) {
		traverse = current->next;
		delete current;
		current = traverse;
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
		os << iter->data >> ",";
	}
	if (size != 0)
		os.seekp(os.tellp() - 1);

	os << "}";
	return os.str();
}

template <class T, class S>
T BST<T, S>::find(S k) {
	LinkedList<T>::iterator iter(this->begin());
	iter + pos;
	return iter->data;
}

int main(int argc, char* argv[])
{
	LinkedList<int> p;
	for (int i = 1; i<12; i++) {
		p.push_back(i);
	}
	std::cout << p.get(4) << std::endl;
	std::cout << p << std::endl;
	p.insert(121, 1);
	p.remove(5);
	std::cout << p << std::endl;
	return 0;
}