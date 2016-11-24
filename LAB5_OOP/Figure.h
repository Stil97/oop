#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>

class Figure {
public:
	virtual double Square() = 0;
	virtual void Print() = 0;
	virtual ~Figure() {};
	friend std::ostream& operator <<(std::ostream& os, Figure& fig) {
		fig.Print();
		return os;
	}
};

#endif