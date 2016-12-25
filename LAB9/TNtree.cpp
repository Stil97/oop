#include "TNtree.h"

template <class T> TNtree<T>::TNtree() : root(0) {
	arrLevelWidth = (int*)malloc(sizeof(int)* 1);
	numLevel = 0;
	arrLevelWidth[0] = 0;
};

template <class T>
std::shared_ptr<TNtreeItem<T>> TNtree<T>::NewTNtreeItem( std::shared_ptr<T>& fig) {
	auto newItem = std::shared_ptr<TNtreeItem<T>>(new TNtreeItem<T>);
	newItem->data = fig;
	newItem->child = 0;
	newItem->brother = 0;
	return newItem;
}

template <class T>
void TNtree<T>::InsertItem(shared_ptr<T>& fig) {
	auto node = NewTNtreeItem(fig);
	if (!root) {
		root = node;
		numLevel++;
		arrLevelWidth[0] = 1;
		arrLevelWidth = (int*)realloc(arrLevelWidth, sizeof(int)* 1);
		arrLevelWidth[1] = 0;
		return;
	}
	auto iter = root;
	int i = 1;
	for (; arrLevelWidth[i] == 4 && i < numLevel; i++)
		iter = iter->child;
	if (i == numLevel) {
		numLevel++;
		arrLevelWidth = (int*)realloc(arrLevelWidth, sizeof(int)* numLevel);
		arrLevelWidth[i] = 1;
		iter->child = node;
		node->father = iter;
	}
	else {
		auto item = iter->child;
		while (item->brother)
			item = item->brother;
		arrLevelWidth[i]++;
		item->brother = node;
		node->father = iter;
	}
}


template <class T>
std::ostream& operator <<(std::ostream &os, TNtree<T>& tree) {
	if (tree.Empty()) {
		os << "Tree empty" << std::endl;
		return os;
	}
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
	os << "{ " << *root->data << " }" << endl;
	auto son = root->child;
	while (son) {
		PrintNtree(son, os, indent + 3);
		son = son->brother;
	}
}

template <class T>
void TNtree<T>::DeleteItem(TIterator<TNtreeItem<T>, T> it) {
	auto deletedItem = it.GetNode();
	if (deletedItem == root && !root->child) {
		deletedItem = 0;
		root = 0;
		LevelRest();
		return;
	}
	if (!deletedItem->child) {
		auto father = deletedItem->GetFather();
		auto son = father->child;
		while (son != deletedItem && son->brother != deletedItem)
			son = son->brother;
		if (son == deletedItem)
			father->child = son->brother;
		else {
			son->brother = deletedItem->brother;
		}
		deletedItem = 0;
		LevelRest();
		return;
	}

	std::shared_ptr<TNtreeItem<T>> iter = deletedItem->child;
	while (iter->child || iter->brother) {
		while (iter->brother)
			iter = iter->brother;
		if (iter->child)
			iter = iter->child;
	}

	auto father = iter->GetFather();
	auto son = father->child;
	while (son != iter && son->brother != iter)
		son = son->brother;
	if (son == iter)
		father->child = 0;
	else
		son->brother = 0;
	deletedItem = 0;
	iter = 0;
	LevelRest();
}

template <class T>
void TNtree<T>::LevelRest() {
	auto iter = root;
	numLevel = 0;
	free(arrLevelWidth);
	arrLevelWidth = (int*)malloc(sizeof(int)* 1);
	if (!iter)
		arrLevelWidth[0] = 0;
	while (iter) {
		numLevel++;
		arrLevelWidth = (int*)realloc(arrLevelWidth, sizeof(int)* numLevel);
		auto iter2 = iter;
		int i;
		for (i = 0; iter2 != nullptr; i++)
			iter2 = iter2->brother;
		arrLevelWidth[numLevel - 1] = i;
		iter = iter->child;
	}

}

template <class T>
TNtree<T>::~TNtree()  {
	root = 0;
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