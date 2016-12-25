#ifndef _tlist_h_
#define _tlist_h_

#include <iostream>
#include <memory>
#include <functional>
#include "TIterator.h"
#include "TItemList.h"

template<class T>
class TList {
public:
	TList();
	bool Empty();
	size_t Size();
	bool Insert(int num, std::shared_ptr<T>& item);
	bool Delete(int num);
	bool Delete(TIterator<TItemList<T>, T> it);
	template<class T> friend std::ostream& operator<<(std::ostream& os, const TList<T>& list);

	TIterator<TItemList<T>, T> begin();
	TIterator<TItemList<T>, T> end();

	~TList();
private:
	std::shared_ptr<TItemList<T>> head;
	std::shared_ptr<TItemList<T>> last;//терминальный эл-т
	size_t size;

};

#endif