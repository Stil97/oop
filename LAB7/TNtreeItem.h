#ifndef TNTREEITEM_H_
#define TNTREEITEM_H_

#include <iostream>
#include <memory>
#include <cstdlib>
#include <string.h>
#include "TList.h"
#include "Figure.h"
#include "TAllocationBlock.h"

template <class TT,class T> class TNtree;

template <class T> class TNtreeItem : public std::enable_shared_from_this<TNtreeItem<T>>{
public:

	friend class TNtree<TList<Figure>, Figure>;

	std::shared_ptr<TNtreeItem<T>> GetFather() const;
	std::shared_ptr<T> GetValue() const;
	std::shared_ptr<TNtreeItem<T>> GetChild() const;
	std::shared_ptr<TNtreeItem<T>> GetBrother() const;
	char* GetId() const;
	
	std::shared_ptr<TNtreeItem> Getptr();

	std::shared_ptr<TNtreeItem<T>> Begin();

	std::shared_ptr<TNtreeItem<T>> Next();

	void* operator new(size_t size);
	void operator delete(void* ptr);


private:
	std::shared_ptr<T> data;
	std::shared_ptr<TNtreeItem> child;
	std::shared_ptr<TNtreeItem> brother;
	std::weak_ptr<TNtreeItem> father;

	static TAllocationBlock ntreeitem_allocator;
};

#endif