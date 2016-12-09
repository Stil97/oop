#ifndef IREMOVECRITERIABYVALUE_H
#define IREMOVECRITERIABYVALUE_H

#include "TRemoveCriteria.h"

template <class T> class TRemoveCriteriaByValue : public TRemoveCriteria<T>{
public:
	TRemoveCriteriaByValue(T&& value) : _value(value) {};
	bool isIt(T* value) override{
		return _value > *value;
	}
private:
	T _value;
};
#endif