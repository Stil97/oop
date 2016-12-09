#include "TNtree.h"

template <class T> TNtree<T>::TNtree() : root(0), N(0) {};

template <class T>
void TNtree<T>::TNtreeCreate(int n)  {
	N = n;
	root = 0;
};
template <class T>
int TNtree<T>::GetN() {
	return N;
}

template <class T>
std::shared_ptr<TNtreeItem<T>> TNtree<T>::NewTNtreeItem(const char *idNew, std::shared_ptr<T>& fig) {
	auto newItem = std::shared_ptr<TNtreeItem<T>>(new TNtreeItem<T>);
	newItem->data = fig;
	newItem->child = 0;
	newItem->brother = 0;
	size_t size = strlen(idNew) + 1;
	newItem->id = new char[size];
	strcpy_s(newItem->id, size, idNew);
	newItem->numItems = 1;
	return newItem;
}

template <class T>
std::shared_ptr<TNtreeItem<T>> TNtree<T>::DepthFirstSearch(std::shared_ptr<TNtreeItem<T>> root, const char *idSearch) {
	auto son = root->child;
	std::shared_ptr<TNtreeItem<T>> temp = 0;
	if (!root)
		return temp;
	else if (!(strcmp(root->id, idSearch)))
		return root;
	else
	while (son) {
		temp = DepthFirstSearch(son, idSearch);
		if (temp)
			return temp;
		son = son->brother;
	}
	return temp;
}

template <class T>
void TNtree<T>::SetNewItem(const char *idDad, const char *idNew, std::shared_ptr<T>& fig) {
	if (N == 0)
	{
		std::cout << "Not created Ntree" << std::endl;
		return;
	}
	if (!root)
	{
		root = NewTNtreeItem(idNew, fig);
		return;
	}
	if (N == root->numItems) {
		std::cout << "Limit elements exhausted" << std::endl;
		return;
	}
	std::shared_ptr<TNtreeItem<T>> item = SearchSetItem(root, idDad);
	if (!item)
		std::cout << "Item with this id is not found" << std::endl;
	else
	{
		auto son = item->child;
		while (son && son->brother)
			son = son->brother;
		if (!son) {
			try {
				item->child = NewTNtreeItem(idNew, fig);
			} catch (std::bad_alloc) {
				std::cerr << "Error: Memory limit" << std::endl;
				return;
			}
			item->child->father = item;
		}
		else {
			try {
				son->brother = NewTNtreeItem(idNew, fig);
			} catch(std::bad_alloc) {
				std::cerr << "Error: Memory limit" << std::endl;
				return;
			}
			son->brother->father = item;
		}
	}
}

template <class T>
std::shared_ptr<TNtreeItem<T>> TNtree<T>::SearchSetItem(std::shared_ptr<TNtreeItem<T>> root, const char *idSearch) {
	auto son = root->child;
	std::shared_ptr<TNtreeItem<T>> temp = 0;
	if (!root)
		return temp;
	else if (!(strcmp(root->id, idSearch))){
		root->numItems++;
		return root;
	}
	else
	while (son) {
		temp = SearchSetItem(son, idSearch);
		if (temp) {
			root->numItems++;
			return temp;
		}
		son = son->brother;
	}
	return temp;
}

template <class T>
std::ostream& operator <<(std::ostream &os, TNtree<T>& tree) {
	if (tree.N == 0)
	{
		os << "\nTNtree not ctreated\n" << std::endl;
		return os;
	}
	os << std::endl << "currentN=";
	if (tree.root)
		os << tree.root->GetCurrentN() << "\n\n";
	else
		os << 0 << "\n\n";
	tree.PrintNtree(tree.root, os, 0);
	os << std::endl;
	return os;
}

template <class T>
void TNtree<T>::PrintNtree(std::shared_ptr<TNtreeItem<T>> root, std::ostream& os, int indent) {
	if (!root)
		return;
	for (int i = 0; i < indent; i++)
		os << "   ";
	os << "id:" << root->id << " " << *root->data;
	auto son = root->child;
	while (son) {
		PrintNtree(son, os, indent + 3);
		son = son->brother;
	}
}

template <class T>
std::shared_ptr<T> TNtree<T>::GetItem(const char *idItem) {
	if (N == 0)
	{
		std::cout << "\nTNtree not ctreated\n" << std::endl;
		return 0;
	}
	std::shared_ptr<TNtreeItem<T>> item = DepthFirstSearch(root, idItem);
	if (!item)
		return 0;
	else
		return item->data;
}

template <class T>
void TNtree<T>::DeleteItem(const char *idItem) {
	if (N == 0)
	{
		std::cout << "\nTNtree not ctreated\n" << std::endl;
		return;
	}
	std::shared_ptr<TNtreeItem<T>> deletedItem = 0;
	deletedItem = SearchDeletedItem(root, idItem);
	if (!deletedItem)
		std::cout << "Item with this id is not found" << std::endl;
	else if (deletedItem == root)
		root = 0;
	else
	{
		auto father = deletedItem->father.lock();
		auto son = father->child;
		while (son != deletedItem && son->brother != deletedItem)
			son = son->brother;
		if (son == deletedItem) {
			father->child = son->brother;
			deletedItem = 0;
		}
		else {
			son->brother = deletedItem->brother;
			deletedItem = 0;
		}
	}
} 

int dec;

template <class T>
std::shared_ptr<TNtreeItem<T>> TNtree<T>::SearchDeletedItem(std::shared_ptr<TNtreeItem<T>> root, const char *idItem) {
	auto son = root->child;
	std::shared_ptr<TNtreeItem<T>> temp = 0;
	if (!root)
		return temp;
	else if (!(strcmp(root->id, idItem))){
		dec = root->numItems;
		return root;
	}
	else
	while (son) {
		temp = SearchDeletedItem(son, idItem);
		if (temp) {
			root->numItems -= dec;
			return temp;
		}
		son = son->brother;
	}
	return temp;
}

template <class T>
TNtree<T>::~TNtree()  {
	root = 0;
	N = 0;
}

template<class T>
TIterator<TNtreeItem<T>, T> TNtree<T>::begin() {
	if (root)
		return TIterator<TNtreeItem<T>, T>(root->Begin());
	else
		return TIterator<TNtreeItem<T>, T>(nullptr);
}

template<class T>
TIterator<TNtreeItem<T>, T> TNtree<T>::end() {
	return TIterator<TNtreeItem<T>, T>(nullptr);
}

#include "Figure.h"
template class TNtree<Figure>;
template std::ostream& operator << (std::ostream& os, TNtree<Figure>& tree);