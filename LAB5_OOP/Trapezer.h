#ifndef TRAPEZER_H
#define TRAPEZER_H
#include <cstdlib>
#include <iostream>

#include "Figure.h"

class Trapezer : public Figure{
public:
	Trapezer();
	Trapezer(size_t i, size_t j, size_t k);
	Trapezer(const Trapezer &orig);

	double Square() override;
	void Print() override;
	
	friend std::ostream& operator << (std::ostream& os, const Trapezer& obj);
	friend std::istream& operator >> (std::istream& is, Trapezer& obj);

	Trapezer& operator =(const Trapezer& right);
	friend bool operator == (const Trapezer& left, const Trapezer& right);

	virtual ~Trapezer();
private:
	size_t side_a;
	size_t side_b;
	size_t side_h;
};

#endif