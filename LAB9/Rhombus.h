#ifndef RHOMBUS_H
#define RHOMBUS_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Rhombus : public Figure {
public:
	Rhombus();
	Rhombus(size_t i,size_t j);
	Rhombus(const Rhombus &orig);

	double Square() override;
	void Print() override;

	friend std::ostream& operator << (std::ostream& os, const Rhombus &obj);
	friend std::istream& operator >> (std::istream& is, Rhombus& obj);

	Rhombus& operator =(const Rhombus& right);
	friend bool operator == (const Rhombus& left, const Rhombus& right);

	virtual ~Rhombus();

private:
	size_t side_a;
	size_t side_h;
};

#endif
