#include "Trapezer.h"
#include <iostream>

Trapezer::Trapezer() : Trapezer(0, 0, 0) {}

Trapezer::Trapezer(size_t i, size_t j, size_t k) : side_a(i), side_b(j), side_h(k) {
	std::cout << "Trapezer created: " << side_a << side_b << side_h << std::endl;
}

Trapezer::Trapezer(std::istream &is) {
	std::cout << "Enter a,b and h Trapezer" << std::endl;
	is >> side_a;
	is >> side_b;
	is >> side_h;
}

Trapezer::Trapezer(const Trapezer &orig) {
	std::cout << "Trapezer copy cteated" << std::endl;
	side_a = orig.side_a;
	side_b = orig.side_b;
	side_h = orig.side_h;
}

double Trapezer::Square() {
	return (side_a + side_b)*side_h / 2;
}

void Trapezer::Print() {
	std::cout << "Trapezer parameters : a=" << side_a << ",b=" << side_b << ",h=" << side_h << std::endl;
}

Trapezer::~Trapezer() {
	std::cout << "Trapezer delete" << std::endl;
}