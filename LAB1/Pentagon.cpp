#define _USE_MATH_DEFINES
#include "Pentagon.h"
#include <iostream>
#include <cmath>

Pentagon::Pentagon() :Pentagon(0) {}

Pentagon::Pentagon(size_t i) : side_a(i) {
	std::cout << "Pentagon created : a=" << side_a << std::endl;
}

Pentagon::Pentagon(std::istream &is) {
	std::cout << "Enter Pentagon side:" << std::endl;
	is >> side_a;
}

void Pentagon::Print() {
	std::cout << "Sides Pentagon " << side_a << std::endl;
}

double Pentagon::Square() {
	return (5 / 4) * side_a * side_a * (1 / tan(M_PI / 5));
}

Pentagon::~Pentagon() {
	std::cout << "Pentagon deleted" << std::endl;
}