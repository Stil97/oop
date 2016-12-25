#include "Trapezer.h"

Trapezer::Trapezer() : Trapezer(0, 0, 0) {}

Trapezer::Trapezer(size_t i, size_t j, size_t k) : side_a(i), side_b(j), side_h(k) {}

Trapezer::Trapezer(const Trapezer &orig) {
	//std::cout << "Trapezer copy cteated" << std::endl;
	side_a = orig.side_a;
	side_b = orig.side_b;
	side_h = orig.side_h;
}

double Trapezer::Square() {
	return (side_a + side_b)*side_h / 2;
}

Trapezer& Trapezer::operator = (const Trapezer& right) {
	if (this == &right)
		return *this;
	//std::cout << "Trapezer copied" << std::endl;
	side_a = right.side_a;
	side_b = right.side_b;
	side_h = right.side_h;

	return *this;
}

void Trapezer::Print() {
	std::cout << "Trapezer: a=" << side_a << ", b=" << side_b << ", h=" << side_h << std::endl;
}


std::ostream& operator << (std::ostream& os, const Trapezer& obj) {
	
	os << "Trapezer a=" << obj.side_a << ", b=" << obj.side_b << ", h=" << obj.side_h << std::endl;
	return os;
}

std::istream& operator >> (std::istream& is, Trapezer& obj) {
	
	is >> obj.side_a;
	is >> obj.side_b;
	is >> obj.side_h;

	return is;
}

bool operator == (const Trapezer& left, const Trapezer& right) {

	return (left.side_a == right.side_a && left.side_b == right.side_b && left.side_h == right.side_h);
}
Trapezer::~Trapezer() {
	//std::cout << "Trapezer delete" << std::endl;
}