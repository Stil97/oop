#include "TNtree.h"

template <class T,class TT> TNtree<T,TT>::TNtree() : root(0) {
	arrLevelWidth = (int*)malloc(sizeof(int)* 2);
	numLevel = 0;
	arrLevelWidth[0] = 0;
};


template <class T,class TT>
std::shared_ptr<TNtreeItem<T>> TNtree<T,TT>::NewTNtreeItem(std::shared_ptr<T>& list) {
	auto newItem = std::shared_ptr<TNtreeItem<T>>(new TNtreeItem<T>);
	newItem->data = list;
	newItem->child = 0;
	newItem->brother = 0;
	return newItem;
}

template <class T,class TT>
std::shared_ptr<TNtreeItem<T>> TNtree<T,TT>::SearchInsert(std::shared_ptr<TNtreeItem<T>> root) {
	std::shared_ptr<TNtreeItem<T>> temp = 0;
	if (!root)
		return temp;
	
	std::shared_ptr<TNtreeItem<T>> son = root->child;
	
	if ( root->data->Size() < 2)
		return root;
	else while (son) {
			temp = SearchInsert(son);
			if (temp)
				return temp;
			son = son->brother;
		}
	return temp;
}

template <class T, class TT>
void TNtree<T,TT>::PushNode(std::shared_ptr<T>& val) {
	auto node = NewTNtreeItem(val);
	if (!root) {
		root = node;
		numLevel++;
		arrLevelWidth[0] = 1;
		arrLevelWidth = (int*)realloc(arrLevelWidth, sizeof(int)* 2);
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

template <class T,class TT>
void TNtree<T,TT>::InsertItem(std::shared_ptr<TT>& fig) {
	auto item = SearchInsert(root);
	if (!item) {
		auto list = std::shared_ptr<T>(new T);
		list->Insert(1, fig);
		PushNode(list);
	}
	else 
		item->data->InsertOrder(fig);

}

template <class T,class TT>
std::ostream& operator <<(std::ostream &os, TNtree<T,TT>& tree) {
	if (tree.root == 0)
	{
		os << "\nTNtree empty\n" << std::endl;
		return os;
	}
	tree.PrintNtree(tree.root, os, 0);
	os << std::endl;
	return os;
}

template <class T,class TT>
void TNtree<T,TT>::PrintNtree(std::shared_ptr<TNtreeItem<T>> root, std::ostream& os, int indent) {
	if (!root)
		return;
	for (int i = 0; i < indent; i++)
		os << "   ";
	os << "{List: " << *root->data << "}" << std::endl;
	auto son = root->child;
	while (son) {
		PrintNtree(son, os, indent + 3);
		son = son->brother;
	}
}

template <class T,class TT>
void TNtree<T,TT>::DeleteItem(TIterator<TNtreeItem<T>, T> it) {
	auto deletedItem = it.GetNode();
	if (deletedItem == root && !root->child) {
		deletedItem = 0;
		root = 0;
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
		return;
	}

	std::shared_ptr<TNtreeItem<T>> iter = deletedItem->child;
	while (iter->child || iter->brother) {
		while (iter->brother)
			iter = iter->brother;
		if (iter->child)
			iter = iter->child;
	}
	deletedItem->data = iter->data;
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
}

template <class T,class TT>
void TNtree<T, TT>::RemoveItemType(std::shared_ptr<TT>& type) {
	for (auto i = begin(); i != end(); ) {
		for (auto ii = (*i)->begin(); ii != (*i)->end(); ) {
			auto value = *ii;
			auto temp = ii;
			ii++;
			if (typeid(*type) == typeid(*value))
				(*i)->Delete(temp);
		}
		auto temp = i;
		i++;
		if ((*temp)->Empty())
			DeleteItem(temp);
	}
}

template <class T,class TT>
void TNtree<T,TT>::RemoveItemSquare(double square) {
	for (auto i = begin(); i != end();) {
		for (auto ii = (*i)->begin(); ii != (*i)->end();) {
			auto value = (*ii)->Square();
			auto temp = ii;
			ii++;
			if (value < square)
				(*i)->Delete(temp);
		}
		auto temp = i;
		i++;
		if ((*temp)->Empty())
			DeleteItem(temp);
	}
}


template<class T,class TT>
TIterator<TNtreeItem<T>, T> TNtree<T,TT>::begin() {
	if (root)
		return TIterator<TNtreeItem<T>, T>(root->Begin());
	else
		return TIterator<TNtreeItem<T>, T> (nullptr);
}

template<class T,class TT>
TIterator<TNtreeItem<T>, T> TNtree<T,TT>::end() {
	return TIterator<TNtreeItem<T>, T>(nullptr);
}

template <class T, class TT>
TNtree<T, TT>::~TNtree()  {
	root = 0;
}

#include "TList.h"
#include "Figure.h"
template class TNtree<TList<Figure>,Figure>;
template std::ostream& operator << (std::ostream& os, TNtree<TList<Figure>, Figure>& tree);