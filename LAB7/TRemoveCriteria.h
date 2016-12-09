#ifndef IREMOVECRITERIA_H
#define IREMOVECRITERIA_H

template <class T> class TRemoveCriteria {
public:
	virtual bool isIt(T* value) = 0;
private:
};

#endif