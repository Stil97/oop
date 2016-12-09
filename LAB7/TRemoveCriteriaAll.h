#ifndef IREMOVECRITERIAALL_H
#define IREMOVECRITERIAALL_H
#include "TRemoveCriteria.h"

template <class T> class TRemoveCriteriaAll : public TRemoveCriteria<T>{
public:
	TRemoveCriteriaAll() {};
	bool isIt(T* value) override{
		return true;
	}
private:

};
#endif