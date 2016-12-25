#include <cstdlib>
#include "Trapezer.h"
#include "Rhombus.h"
#include "Pentagon.h"

int main(){

	Figure *ptr1 = new Trapezer(std::cin);
	ptr1->Print();
	std::cout << "Square Trapezer :" << ptr1->Square() << std::endl;
	delete ptr1;

	Figure *ptr2 = new Rhombus(std::cin);
	ptr2->Print();
	std::cout << "Square Rhombus :" << ptr2->Square() << std::endl;
	delete ptr2;

	Figure *ptr3 = new Pentagon(std::cin);
	ptr3->Print();
	std::cout << "Squre =" << ptr3->Square() << std::endl;
	delete ptr3;

	return 0;
}