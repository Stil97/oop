#ifndef PENTAGON_H
#define PENTAGON_H

#include <cstdlib>
#include "Figure.h"
#include <cmath>
#include <iostream>

class Pentagon : public Figure {
public:
	Pentagon();
	Pentagon(size_t i);
	Pentagon(std::istream &is);

	double Square() override;
	void Print() override;

	virtual ~Pentagon();

private:
	size_t side_a;
};

#endif