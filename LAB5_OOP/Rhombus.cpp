#include "Rhombus.h"

Rhombus::Rhombus() :Rhombus(0,0) {}

Rhombus::Rhombus(size_t i,size_t j) : side_a(i), side_h(j)  {}

Rhombus::Rhombus(const Rhombus &orig) {
	side_a = orig.side_a;
}

void Rhombus::Print() {
	std::cout << "Rhombus : a=" << side_a << " h=" << side_h << std::endl;
}

double Rhombus::Square() {
	return side_a*side_h;
}

std::ostream& operator << (std::ostream& os, const Rhombus &obj) {

	os << "Rhombus : a=" << obj.side_a <<" h=" << obj.side_h << std::endl;
	return os;
}

std::istream& operator >> (std::istream& is, Rhombus& obj) {
	is >> obj.side_a;
	is >> obj.side_h;
	return is;
}

Rhombus& Rhombus::operator = (const Rhombus& right) {
	if (this == &right)
		return *this;
	side_a = right.side_a;
	side_h = right.side_h;
	return *this;
}

bool operator == (const Rhombus& left, const Rhombus& right) {
	return (right.side_a == left.side_a && right.side_h == left.side_h);
}

Rhombus::~Rhombus() {
	//	std::cout << "Rhombus deleted" << std::endl;
}