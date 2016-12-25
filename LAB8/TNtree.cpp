#include "TNtree.h"

template <class T> TNtree<T>::TNtree() : root(0) {};

template <class T>
std::shared_ptr<TNtreeItem<T>> TNtree<T>::NewTNtreeItem(const char *idNew, std::shared_ptr<T>& fig) {
	auto newItem = std::shared_ptr<TNtreeItem<T>>(new TNtreeItem<T>);
	newItem->data = fig;
	newItem->child = 0;
	newItem->brother = 0;
	size_t size = strlen(idNew) + 1;
	strcpy_s(newItem->id, size, idNew);
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
	if (!root)
	{
		root = NewTNtreeItem(idNew, fig);
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
void TNtree<T>::PushItem(const char *idItem, shared_ptr<T>& fig) {
	if (!root) {
		root = NewTNtreeItem(idItem, fig);
		return;
	}
	else if (!root->child) {
		root->child = NewTNtreeItem(idItem, fig);
		root->child->father = root;
		return;
	}
	auto iter = root->child;
	while (iter->brother)
		iter = iter->brother;
	iter->brother = NewTNtreeItem(idItem, fig);
	iter->brother->father = root;
	iter = 0;
}

template <class T>
std::shared_ptr<TNtreeItem<T>> TNtree<T>::SearchSetItem(std::shared_ptr<TNtreeItem<T>> root, const char *idSearch) {
	auto son = root->child;
	std::shared_ptr<TNtreeItem<T>> temp = 0;
	if (!root)
		return temp;
	else if (!(strcmp(root->id, idSearch))){
		return root;
	}
	else
	while (son) {
		temp = SearchSetItem(son, idSearch);
		if (temp) {
			return temp;
		}
		son = son->brother;
	}
	return temp;
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
	os << "{ id:" << root->id << " " << *root->data << " }" << endl;
	auto son = root->child;
	while (son) {
		PrintNtree(son, os, indent + 3);
		son = son->brother;
	}
}

template <class T>
std::shared_ptr<T> TNtree<T>::GetItem(const char *idItem) {
	std::shared_ptr<TNtreeItem<T>> item = DepthFirstSearch(root, idItem);
	if (!item)
		return 0;
	else
		return item->data;
}

template <class T>
void TNtree<T>::DeleteItem(const char *idItem) {
	if (Empty())
	{
		std::cout << "\nTree empty" << std::endl;
		return;
	}
	std::shared_ptr<TNtreeItem<T>> deletedItem = 0;
	deletedItem = SearchDeletedItem(root, idItem);
	if (!deletedItem)
		std::cout << "Item with this id is not found" << std::endl;
	else if (deletedItem == root && !root->child) {
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
	size_t size = strlen(iter->id) + 1;
	strcpy_s(deletedItem->id, size, iter->id);

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

template <class T>
void TNtree<T>::DeleteItem(TIterator<TNtreeItem<T>, T> it) {
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
	size_t size = strlen(iter->id) + 1;
	strcpy_s(deletedItem->id, size, iter->id);

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

template <class T>
std::shared_ptr<TNtreeItem<T>> TNtree<T>::SearchDeletedItem(std::shared_ptr<TNtreeItem<T>> root, const char *idItem) {
	auto son = root->child;
	std::shared_ptr<TNtreeItem<T>> temp = 0;
	if (!root)
		return temp;
	else if (!(strcmp(root->id, idItem))){
		return root;
	}
	else
	while (son) {
		temp = SearchDeletedItem(son, idItem);
		if (temp) {
			return temp;
		}
		son = son->brother;
	}
	return temp;
}

template <class T>
void TNtree<T>::Sort() {
	if (Empty())
		return;
	if (root->child) {
		auto iter = begin();
		auto middle = *iter;
		char idMiddle[15];
		size_t size = strlen(iter.GetNode()->id) + 1;
		strcpy_s(idMiddle, size, iter.GetNode()->id);
		DeleteItem(iter);
		TNtree<T> less, more;
		
		for (iter = begin(); iter != end();) {
			auto item = *iter;
			char idItem[15];;
			size_t size = strlen(iter.GetNode()->id) + 1;
			strcpy_s(idItem, size, iter.GetNode()->id);
			auto temp = iter;
			iter++;
			DeleteItem(temp);
			if (*item < *middle)
				less.PushItem(idItem, item);
			else
				more.PushItem(idItem, item);
		}
		
		less.Sort();
		more.Sort();

		auto item = NewTNtreeItem(idMiddle, middle);
		item->child = less.root;
		if (!less.Empty())
			less.root->father = item;

		if (more.Empty()) {
			root = item;
		}
		else if (!more.root->child) {
			root = more.root;
			root->child = item;
			root->child->father = root;
		}
		else {
			root = more.root;
			item->brother = root->child;
			root->child = item;
			root->child->father = root;
		}

	}
}

template < class T>
void TNtree<T>::ParallelSort() {
	if (Empty())
		return;
	if (root->child) {
		auto iter = begin();
		auto middle = *iter;
		char idMiddle[15];
		size_t size = strlen(iter.GetNode()->id) + 1;
		strcpy_s(idMiddle, size, iter.GetNode()->id);
		DeleteItem(iter);
		TNtree<T> less, more;

		for (iter = begin(); iter != end();) {
			auto item = *iter;
			char idItem[15];;
			size_t size = strlen(iter.GetNode()->id) + 1;
			strcpy_s(idItem, size, iter.GetNode()->id);
			auto temp = iter;
			iter++;
			DeleteItem(temp);
			if (*item < *middle)
				less.PushItem(idItem, item);
			else
				more.PushItem(idItem, item);
		}

		future<void> futureLess = async(launch::async, &TNtree<T>::ParallelSort, &less);
		future<void> futureMore = async(launch::async, &TNtree<T>::ParallelSort, &more);


		auto item = NewTNtreeItem(idMiddle, middle);

		futureLess.get();

		item->child = less.root;
		if (!less.Empty())
			less.root->father = item;

		futureMore.get();

		if (more.Empty()) {
			root = item;
		}
		else if (!more.root->child) {
			root = more.root;
			root->child = item;
			root->child->father = root;
		}
		else {
			root = more.root;
			item->brother = root->child;
			root->child = item;
			root->child->father = root;
		}

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