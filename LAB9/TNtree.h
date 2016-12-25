#include <iostream>
#include <memory>
#include <cstdlib>
#include <string.h>
#include <future>

#include "TNtreeItem.h"
#include "TIterator.h"

using namespace std;

template <class T> class TNtree {
public:
	TNtree();
	void InsertItem(shared_ptr<T>& fig);

	void PrintNtree(std::shared_ptr<TNtreeItem<T>> root, std::ostream& os, int indent);
	template <class T> friend std::ostream& operator << (std::ostream& os,TNtree<T>& tree);
	void DeleteItem(TIterator<TNtreeItem<T>, T>);
	TIterator<TNtreeItem<T>, T> begin();
	TIterator<TNtreeItem<T>, T> end();
	

	bool Empty(){
		return root == nullptr;
	}

	virtual ~TNtree();
private:
	std::shared_ptr<TNtreeItem<T>> NewTNtreeItem( std::shared_ptr<T>& fig);
	void LevelRest();

	std::shared_ptr<TNtreeItem<T>> root;
	int* arrLevelWidth;
	int numLevel;
};
