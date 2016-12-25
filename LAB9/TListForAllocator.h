#ifndef _TLISTFORALLOCATION_H_
#define _TLISTFORALLOCATION_H_

#include <iostream>

template <class T>
struct TItList{
	TItList *prev;
	TItList *next;
	T value;
};

template<class T>
class TListForAllocator {
public:
	TListForAllocator();
	bool Empty();
	size_t Size();
	bool Insert(int num, const T &item);
	bool Delete(int num);
	T Get(int num);
	template<class T> friend std::ostream& operator<<(std::ostream& os, const TListForAllocator<T>& list);
	~TListForAllocator();

private:
	TItList<T>* head;
	TItList<T>* last;//терминальный эл-т
	size_t size;

};

template <class T> 
T TListForAllocator<T>::Get(int num) {
	if (num < 1 || num > size)
		return 0;
	TItList<T>* iter = head;
	for (int index = 1; index < num; index++)
		iter = iter->next;
	return iter->value;
}

template <class T>
TListForAllocator<T>::TListForAllocator() {
	head = last = new TItList<T>;
	head->next = head->prev = 0;
	size = 0;
}

template <class T>
bool TListForAllocator<T>::Empty(){
	return size == 0;
}

template <class T>
size_t TListForAllocator<T>::Size(){
	return size;
}

template <class T>
bool TListForAllocator<T>::Insert(int num, const T& t){
	if (num < 1)
		return false;
	TItList<T>* iter = head;
	for (int index = 1; iter != last && index < num; index++) 
		iter = iter->next;
	if (iter == last) {
		iter->value = t;
		iter->next = new TItList<T>;
		iter->next->prev = iter;
		iter->next->next = 0;
		last = iter->next;
	}
	else if (num == 1) {
		TItList<T>* item = new TItList<T>;
		item->value = t;
		item->prev = 0;
		item->next = head;
		head->prev = item;
		head = item;
	}
	else {
		TItList<T>* item = new TItList<T>;
		item->value = t;
		iter->prev->next = item;
		item->prev = iter->prev;
		item->next = iter;
		iter->prev = item;
	}
	size++;
	return true;
}

template <class T>
bool TListForAllocator<T>::Delete(int num){
	if (num > size || num < 1)
		return false;
	TItList<T>* iter = head;
	for (int index = 1;index < num; index++)
		iter = iter->next;
	if (num != 1)
		iter->prev->next = iter->next;
	else
		head = head->next;
	iter->next->prev = iter->prev;
	delete iter;
	size--;
	return true;
}

template <class T>
TListForAllocator<T>::~TListForAllocator(){
	TItList<T> *i = head;
	while (i) {
		TItList<T> *pi = i;
		i = i->next;
		delete pi;
	}
	head = 0;
	size = 0;
}

template<class T> 
std::ostream& operator<<(std::ostream& os, const TListForAllocator<T>& list) {
	if (!list.size) {
		os << "List empty" << std::endl;
		return os;
	}
	TItList<T>* iter = list.head;
	for (int i = 0; i < list.size; i++) {
		os << "[" << iter->value << "]" << std::endl;
		iter = iter->next;
	}
	return os;
}


#endif