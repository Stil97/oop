#include "TList.h"

template <class T>
TList<T>::TList() {
	try {
		head = last = std::shared_ptr<TItemList<T>>(new TItemList<T>);
	}
	catch (std::bad_alloc) {
		std::cerr << "Error: Memory limit!" << std::endl;
		return;
	}
	head->next = nullptr;
	size = 0;
}

template <class T>
bool TList<T>::Empty(){
	return size == 0;
}

template <class T>
size_t TList<T>::Size(){
	return size;
}

template <class T>
bool TList<T>::Insert(int num, std::shared_ptr<T>& t){
	if (num < 1)
		return false;
	auto iter = head;
	for (int index = 1; iter != last && index < num; index++)
		iter = iter->next;
	if (iter == last) {
		iter->value = t;
		try {
			iter->next = std::shared_ptr<TItemList<T>>(new TItemList<T>);
		}
		catch (std::bad_alloc) {
			std::cerr << "Error: Memory limit!" << std::endl;
			return false;
		}
		iter->next->prev = iter;
		iter->next->next = nullptr;
		last = iter->next;
	}
	else if (num == 1) {
		std::shared_ptr<TItemList<T>> item;
		try {
			item = std::shared_ptr<TItemList<T>>(new TItemList<T>);
		}
		catch (std::bad_alloc) {
			std::cerr << "Error: Memory limit!" << std::endl;
			return false;
		}
		item->value = t;
		item->next = head;
		head->prev = item;
		head = item;
	}
	else {
		std::shared_ptr<TItemList<T>> item;
		try {
			item = std::shared_ptr<TItemList<T>>(new TItemList<T>);
		}
		catch (std::bad_alloc) {
			std::cerr << "Error: Memory limit!" << std::endl;
			return false;
		}
		item->value = t;
		iter->prev.lock()->next = item;
		item->prev = iter->prev;
		item->next = iter;
		iter->prev = item;
	}
	size++;
	return true;
}

template<class T>
bool TList<T>::InsertOrder(std::shared_ptr<T>& t){
	auto iter = head;
	int index = 1;
	for (; iter != last && iter->value->Square() < t->Square(); index++)
		iter = iter->next;
	if (iter == last) {
		iter->value = t;
		try {
			iter->next = std::shared_ptr<TItemList<T>>(new TItemList<T>);
		}
		catch (std::bad_alloc) {
			std::cerr << "Error: Memory limit!" << std::endl;
			return false;
		}
		iter->next->prev = iter;
		iter->next->next = nullptr;
		last = iter->next;
	}
	else if (index == 1) {
		std::shared_ptr<TItemList<T>> item;
		try {
			item = std::shared_ptr<TItemList<T>>(new TItemList<T>);
		}
		catch (std::bad_alloc) {
			std::cerr << "Error: Memory limit!" << std::endl;
			return false;
		}
		item->value = t;
		item->next = head;
		head->prev = item;
		head = item;
	}
	else {
		std::shared_ptr<TItemList<T>> item;
		try {
			item = std::shared_ptr<TItemList<T>>(new TItemList<T>);
		}
		catch (std::bad_alloc) {
			std::cerr << "Error: Memory limit!" << std::endl;
			return false;
		}
		item->value = t;
		iter->prev.lock()->next = item;
		item->prev = iter->prev;
		item->next = iter;
		iter->prev = item;
	}
	size++;
	return true;
}

template <class T>
bool TList<T>::Delete(int num){
	if (num > size || num < 1)
		return false;
	if (Empty())
		return false;
	auto iter = head;
	for (int index = 1; index < num; index++)
		iter = iter->next;
	if (num != 1)
		iter->prev.lock()->next = iter->next;
	else
		head = head->next;
	iter->next->prev = iter->prev;
	//delete iter;
	iter = 0;
	size--;
	return true;
}

template <class T>
bool TList<T>::Delete(TIterator<TItemList<T>, T> it) {
	auto iter = it.GetNode();
	if (iter != head)
		iter->prev.lock()->next = iter->next;
	else
		head = head->next;
	iter->next->prev = iter->prev;
	//delete iter;
	iter = 0;
	size--;
	return true;
}

template <class T>
TList <T>::~TList(){
	head = 0;
	size = 0;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const TList<T>& list) {
	if (!list.size) {
		os << "List empty" << std::endl;
		return os;
	}
	auto iter = list.head;
	for (int i = 0; i < list.size; i++) {
		os << "[" << *iter->GetValue() << "]  ";
		iter = iter->Next();
	}
	return os;
}




template<class T>
TIterator<TItemList<T>, T> TList<T>::begin() {
	return TIterator<TItemList<T>, T>(head);
}

template<class T>
TIterator<TItemList<T>, T> TList<T>::end() {
	return TIterator<TItemList<T>, T>(last);
}

#include "Figure.h"

template class TList<Figure>;
template std::ostream& operator <<(std::ostream& os,const TList<Figure>& list);