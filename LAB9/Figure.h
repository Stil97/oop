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
	friend bool operator <(Figure& fig1, Figure& fig2) {
		return fig1.Square() < fig2.Square();
	}

	friend bool operator >(Figure& fig1, Figure& fig2) {
		return fig1.Square() > fig2.Square();
	}
};

#endif
