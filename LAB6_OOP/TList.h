#ifndef _tlist_h_
#define _tlist_h_

#include <iostream>

template <class T>
struct TItemList{
	TItemList *prev;
	TItemList *next;
	T value;
};

template<class T>
class TList {
public:
	TList();
	bool Empty();
	size_t Size();
	bool Insert(int num, const T &item);
	bool Delete(int num);
	T Get(int num);
	template<class T> friend std::ostream& operator<<(std::ostream& os, const TList<T>& list);
	~TList();

private:
	TItemList<T>* head;
	TItemList<T>* last;//терминальный эл-т
	size_t size;

};

template <class T> 
T TList<T>::Get(int num) {
	if (num < 1 || num > size)
		return 0;
	TItemList<T>* iter = head;
	for (int index = 1; index < num; index++)
		iter = iter->next;
	return iter->value;
}

template <class T>
TList<T>::TList() {
	head = last = new TItemList<T>;
	head->next = head->prev = 0;
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
bool TList<T>::Insert(int num, const T& t){
	if (num < 1)
		return false;
	TItemList<T>* iter = head;
	for (int index = 1; iter != last && index < num; index++) 
		iter = iter->next;
	if (iter == last) {
		iter->value = t;
		iter->next = new TItemList<T>;
		iter->next->prev = iter;
		iter->next->next = 0;
		last = iter->next;
	}
	else if (num == 1) {
		TItemList<T>* item = new TItemList<T>;
		item->value = t;
		item->prev = 0;
		item->next = head;
		head->prev = item;
		head = item;
	}
	else {
		TItemList<T>* item = new TItemList<T>;
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
bool TList<T>::Delete(int num){
	if (num > size || num < 1)
		return false;
	TItemList<T>* iter = head;
	for (int index = 1;index < num; index++)
		iter = iter->next;
	if (num != 1)
		iter->prev->next = iter->next;
	else
		head = head->next;
	iter->next->prev = iter->prev;
	delete iter;
	size--;
}

template <class T>
TList <T>::~TList(){
	TItemList<T> *i = head;
	while (i) {
		TItemList<T> *pi = i;
		i = i->next;
		delete pi;
	}
	head = 0;
	size = 0;
}

template<class T> 
std::ostream& operator<<(std::ostream& os, const TList<T>& list) {
	if (!list.size) {
		os << "List empty" << std::endl;
		return os;
	}
	TItemList<T>* iter = list.head;
	for (int i = 0; i < list.size; i++) {
		os << "[" << iter->value << "]" << std::endl;
		iter = iter->next;
	}
	return os;
}


#endif