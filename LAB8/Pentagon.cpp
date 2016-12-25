#define _USE_MATH_DEFINES
#include "Pentagon.h"

Pentagon::Pentagon() :Pentagon(0) {}

Pentagon::Pentagon(size_t i) : side_a(i) {}

Pentagon::Pentagon(const Pentagon &orig) {
	side_a = orig.side_a;
}

void Pentagon::Print() {
	std::cout << "Sides Pentagon : " << side_a;
}

double Pentagon::Square() {
	return (5 / 4) * side_a * side_a * (1 / tan(M_PI / 5));
}

std::ostream& operator << (std::ostream& os, const Pentagon &obj) {
	
	os << "Sides Pentagon : " << obj.side_a << std::endl;
	return os;
}

std::istream& operator >> (std::istream& is, Pentagon& obj) {
	is >> obj.side_a;
	return is;
}

Pentagon& Pentagon::operator = (const Pentagon& right) {
	if (this == &right)
		return *this;
	side_a = right.side_a;
	return *this;
}

bool operator == (const Pentagon& left, const Pentagon& right) {
	return right.side_a == left.side_a;
}

Pentagon::~Pentagon() {
//	std::cout << "Pentagon deleted" << std::endl;
}