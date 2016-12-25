#ifndef TNTREE_H_
#define TNTREE_H_


#include <iostream>
#include <memory>
#include <cstdlib>
#include <string.h>

#include "TNtreeItem.h"
#include "TIterator.h"

template <class T,class TT> class TNtree {
public:
	TNtree();
	void InsertItem(std::shared_ptr<TT>& fig);

	void PrintNtree(std::shared_ptr<TNtreeItem<T>> root, std::ostream& os, int indent);
	template <class T,class TT> friend std::ostream& operator << (std::ostream& os,TNtree<T,TT>& tree);

	void DeleteItem(TIterator<TNtreeItem<T>, T>);
	void RemoveItemType(std::shared_ptr<TT>& type);
	void RemoveItemSquare(double square);
	
	bool Empty() {
		return root == 0;
	}

	TIterator<TNtreeItem<T>, T> begin();
	TIterator<TNtreeItem<T>, T> end();
	
	virtual ~TNtree();
private:
	void PushNode(std::shared_ptr<T>& val);
	std::shared_ptr<TNtreeItem<T>> NewTNtreeItem(std::shared_ptr<T>& list);
	std::shared_ptr<TNtreeItem<T>> SearchInsert(std::shared_ptr<TNtreeItem<T>>);
	void LevelRest();
	
	std::shared_ptr<TNtreeItem<T>> root;

	int* arrLevelWidth;
	int numLevel;
};


#endif