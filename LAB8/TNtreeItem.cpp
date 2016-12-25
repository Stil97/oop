#include "TNtreeItem.h"

template <class T> TAllocationBlock
TNtreeItem <T>::ntreeitem_allocator(sizeof(TNtreeItem<T>), 100);


template<class T> 
std::shared_ptr<TNtreeItem<T>> TNtreeItem<T>::GetFather() const {
	return father.lock();
}

template<class T> 
std::shared_ptr<T> TNtreeItem<T>::GetValue() const {
	return  this->data;
}

template<class T> 
std::shared_ptr<TNtreeItem<T>> TNtreeItem<T>::GetChild() const {
	return this->child;
}

template<class T>
std::shared_ptr<TNtreeItem<T>> TNtreeItem<T>::GetBrother() const {
	return this->brother;
}

template<class T>
std::shared_ptr<TNtreeItem<T>> TNtreeItem<T>::Getptr() {
	return this->shared_from_this();
}

template<class T>
std::shared_ptr<TNtreeItem<T>> TNtreeItem<T>::Begin() {
	if (!this->child)
		return Getptr();
	else {
		auto iter = this->child;
		while (iter->child)
			iter = iter->child;
		return iter;
	}
}

template<class T>
std::shared_ptr<TNtreeItem<T>> TNtreeItem<T>::Next() {
	if (this->brother)
		return this->brother->Begin();
	else
		if (this->father.expired())
			return nullptr;
		else
			return this->father.lock();
}

template <class T> 
void* TNtreeItem<T>:: operator new (size_t size){
	return ntreeitem_allocator.Allocate();
}

template <class T> 
void TNtreeItem<T>:: operator delete (void *p) {
	ntreeitem_allocator.Deallocate(p);
}



#include "Figure.h"
template class TNtreeItem<Figure>;