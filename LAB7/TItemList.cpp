#include "TItemList.h"

template <class T> TAllocationBlock
TItemList<T>::tlistitem_allocator(sizeof(TItemList<T>), 100);

template <class T>
std::shared_ptr<T> TItemList<T>::GetValue() const {
	return this->value;
}

template <class T>
std::shared_ptr<TItemList<T>> TItemList<T>::Next() {
	return this->next;
}

template<class T>
void* TItemList<T>::operator new(size_t size){
	return tlistitem_allocator.Allocate();
}

template<class T>
void TItemList<T>::operator delete(void* ptr) {
	tlistitem_allocator.Deallocate(ptr);
}

#include "Figure.h"

template class TItemList<Figure>;