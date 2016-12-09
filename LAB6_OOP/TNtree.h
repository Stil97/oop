#include <iostream>
#include <memory>
#include <cstdlib>
#include <string.h>

#include "TNtreeItem.h"
#include "TIterator.h"

template <class T> class TNtree {
public:
	TNtree();
	void TNtreeCreate(int n);
	void SetNewItem(const char *idDad, const char *idNew, std::shared_ptr<T>& trapezer);
	void PrintNtree(std::shared_ptr<TNtreeItem<T>> root, std::ostream& os, int indent);
	template <class T> friend std::ostream& operator << (std::ostream& os,TNtree<T>& tree);
	std::shared_ptr<T> GetItem(const char *idItem);
	void DeleteItem(const char *idItem);
	int GetN();

	TIterator<TNtreeItem<T>, T> begin();
	TIterator<TNtreeItem<T>, T> end();
	
	virtual ~TNtree();
private:
	std::shared_ptr<TNtreeItem<T>> NewTNtreeItem(const char *idNew, std::shared_ptr<T>& fig);
	std::shared_ptr<TNtreeItem<T>> DepthFirstSearch(std::shared_ptr<TNtreeItem<T>> root,const char *idSearch);
	std::shared_ptr<TNtreeItem<T>> SearchSetItem(std::shared_ptr<TNtreeItem<T>> root, const char *idSearch);
	std::shared_ptr<TNtreeItem<T>> SearchDeletedItem(std::shared_ptr<TNtreeItem<T>>, const char*);
	
	std::shared_ptr<TNtreeItem<T>> root;
	int N;
};
