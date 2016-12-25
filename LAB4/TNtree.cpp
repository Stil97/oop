#include "TNtree.h"

template <class T>
int TNtreeItem<T>::currentN;

template <class T> TNtree<T>::TNtree() : root(0), N(0) {};

template <class T>
void TNtree<T>::TNtreeCreate(int n)  {
	N = n;
	root = 0;
	TNtreeItem<T>::currentN = 0;
};

template <class T>
std::shared_ptr<TNtreeItem<T>> TNtree<T>::NewTNtreeItem(const char *idNew, std::shared_ptr<T>& fig) {
	auto newItem = std::shared_ptr<TNtreeItem<T>>(new TNtreeItem<T>);
	newItem->data = fig;
	newItem->child = 0;
	newItem->brother = 0;
	size_t size = strlen(idNew) + 1;
	newItem->id = new char[size];
	strcpy_s(newItem->id, size, idNew);
	newItem->currentN++;
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
	std::shared_ptr<TNtreeItem<T>> item = DepthFirstSearch(root, idDad);
	if (!item)
		std::cout << "Item with this id is not found" << std::endl;
	else if (N == root->currentN)
		std::cout << "Limit elements exhausted" << std::endl;
	else
	{
		auto son = item->child;
		while (son && son->brother)
			son = son->brother;
		if (!son)
			item->child = NewTNtreeItem(idNew, fig);
		else
			son->brother = NewTNtreeItem(idNew, fig);
	}
}

template <class T>
std::ostream& operator <<(std::ostream &os, TNtree<T>& tree) {
	if (tree.N == 0)
	{
		os << "\nTNtree not ctreated\n" << std::endl;
		return os;
	}
	os << std::endl << "currentN=" << tree.root->GetCurrentN() << "\n\n";
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

bool deletedRoot;

template <class T>
void TNtree<T>::DeleteItem(const char *idItem) {
	if (N == 0)
	{
		std::cout << "\nTNtree not ctreated\n" << std::endl;
		return;
	}
	std::shared_ptr<TNtreeItem<T>> item = 0;
	std::shared_ptr<TNtreeItem<T>> deletedItem = 0;
	deletedRoot = false;
	item = SearchDeletedItem(root, idItem);
	if (!item)
		std::cout << "Item with this id is not found" << std::endl;
	else if (item == root && deletedRoot) {
		root = 0;
		item = 0;
	}
	else
	{
		auto son = item->child;
		bool end = false;
		while (son && !end) {
			if (!strcmp(son->id, idItem)) {
				deletedItem = son;
				end = true;
			}
			son = son->brother;
		}
		son = item->child;
		while (son != deletedItem && son->brother != deletedItem)
			son = son->brother;
		if (son == deletedItem) {
			item->child = son->brother;
			deletedItem = 0;
		}
		else {
			son->brother = deletedItem->brother;
			deletedItem = 0;
		}
	}
}

template <class T>
std::shared_ptr<TNtreeItem<T>> TNtree<T>::SearchDeletedItem(std::shared_ptr<TNtreeItem<T>> root, const char *idItem) {
	auto son = root->child;
	std::shared_ptr<TNtreeItem<T>> temp = 0;
	if (!root)
		return temp;
	else if (!strcmp(root->id, idItem)) {
		temp = root;
		deletedRoot = true;
	}
	else
	{
		while (son) {
			if (!strcmp(son->id, idItem))
			{
				temp = root;
				//deletedItem = son;
				return temp;
			}
			son = son->brother;
		}
		son = root->child;
		while (son) {
			SearchDeletedItem(son, idItem);
			son = son->brother;
		}
	}
	return temp;
}

template <class T>
TNtree<T>::~TNtree()  {
	root = 0;
	N = 0;

}


#include "Figure.h"
template class TNtree<Figure>;
template std::ostream& operator << (std::ostream& os, TNtree<Figure>& tree);