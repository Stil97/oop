#include "Rhombus.h"
#include <iostream>

Rhombus::Rhombus() : Rhombus(0, 0) {}

Rhombus::Rhombus(size_t i, size_t j) : side_a(i), side_h(j) {
	std::cout << "Rhombus created : " << "a=" << side_a << ",h=" << side_h << std::endl;
}

Rhombus::Rhombus(std::istream &is) {
	std::cout << "Enter side a,h Rhombus :" << std::endl;
	is >> side_a;
	is >> side_h;
}

Rhombus::Rhombus(const Rhombus &orig) {
	std::cout << "Rhombus cope created" << std::endl;
	side_a = orig.side_a;
	side_h = orig.side_h;
}

double Rhombus::Square() {
	return side_a*side_h;
}

void Rhombus::Print(){
	std::cout << "Rhombus parameters side : a=" << side_a << ",h=" << side_h << std::endl;
}

Rhombus::~Rhombus() {
	std::cout << "Rhombus deleted" << std::endl;
}