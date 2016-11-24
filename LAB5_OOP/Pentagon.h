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
	Pentagon(const Pentagon &orig);

	double Square() override;
	void Print() override;

	friend std::ostream& operator << (std::ostream& os, const Pentagon &obj);
	friend std::istream& operator >> (std::istream& is, Pentagon& obj);

	Pentagon& operator =(const Pentagon& right);
	friend bool operator == (const Pentagon& left, const Pentagon& right);

	virtual ~Pentagon();

private:
	size_t side_a;
};

#endif