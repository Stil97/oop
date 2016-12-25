#ifndef TITEMLIST_H_
#define TITEMLIST_H_

#include <iostream>
#include <memory>
#include "TAllocationBlock.h"

template <class T> class  TList;

template <class T>
class TItemList{
public:

	friend class TList<T>;

	std::shared_ptr<T> GetValue() const;
	std::shared_ptr<TItemList<T>> Next();


	void* operator new(size_t size);
	void operator delete(void* ptr);

private:
	std::weak_ptr<TItemList> prev;
	std::shared_ptr<TItemList> next;
	std::shared_ptr<T> value;

	static TAllocationBlock tlistitem_allocator;
};

#endif
