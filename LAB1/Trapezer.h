#ifndef TRAPEZER_H
#define TRAPEZER_H
#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Trapezer : public Figure{
public:
	Trapezer();
	Trapezer(std::istream &is);
	Trapezer(size_t i, size_t j, size_t k);
	Trapezer(const Trapezer &orig);

	double Square() override;
	void Print() override;

	virtual ~Trapezer();
private:
	size_t side_a;
	size_t side_b;
	size_t side_h;
};

#endif