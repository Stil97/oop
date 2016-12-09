#include <iostream>
#include <memory>

#include "Figure.h"
#include "Trapezer.h"
#include "Pentagon.h"
#include "Rhombus.h"
#include "TNtree.h"
#include "TList.h"
#include "TIterator.h"

using namespace std;

void printmenu() {
	cout << "Menu:" << endl;
	cout << "0 - print Menu" << endl;
	cout << "1 - set Trapezer" << endl;
	cout << "2 - set Pentagon" << endl;
	cout << "3 - set Rhombus" << endl;
	cout << "p - print" << endl;
	cout << "4 - delet type" << endl;
	cout << "5 - delete squere less that x" << endl;
	cout << "f - cycle \"for\"" << endl;
	cout << "q - quit" << endl;
	
}

int main(int argc, char** argv) {
	char otvet,figur;
	double square;
	Trapezer* trapezer = new Trapezer;
	Pentagon* pentagon = new Pentagon;
	Rhombus* rhombus = new Rhombus;
	std::shared_ptr<Figure> fig;

	TNtree<TList<Figure>,Figure> tree;
	printmenu();
	do {
		std::cin >> otvet;
		switch (otvet) {

			case '0':
				printmenu();
				break;
			case '1':
				std::cout << "Enter container tree(trapezer:a,b,h)" << std::endl;
				std::cin >> *trapezer ;
				fig = std::shared_ptr<Figure>(trapezer);
				tree.InsertItem(fig);
				trapezer = new Trapezer;
				break;
			case '2':
				std::cout << "Enter container tree(side pentagon)" << std::endl;
				std::cin >> *pentagon;
				fig = std::shared_ptr<Figure>(pentagon);
				tree.InsertItem(fig);
				pentagon = new Pentagon;
				break;
			case '3':
				std::cout << "Enter container tree(rhombus:a,h)" << std::endl;
				std::cin >> *rhombus ;
				fig = std::shared_ptr<Figure>(rhombus);
				tree.InsertItem(fig);
				rhombus = new Rhombus;
				break;
			case 'p':
				std::cout << tree;
				break;
			case '4':
				cout << "Enter the tupe figure (P, R, T): ";
				std::cin >> figur;
				switch (figur) {
					case 'p':case 'P':
						tree.RemoveItemType(std::shared_ptr<Figure>(new Pentagon));
						break;
					case 'r':case'R':
						tree.RemoveItemType(std::shared_ptr<Figure>(new Rhombus));
						break;
					case 't':case 'T':
						tree.RemoveItemType(std::shared_ptr<Figure>(new Trapezer));
						break;
					default:
						cout << "Wrong!" << endl;
				}
				break;
			case'5':
				cout << "Enter square: ";
				cin >> square;
				tree.RemoveItemSquare(square);
				break;
			case'f':
				if (tree.Empty())
					std::cout << "Tree empty" << std::endl;
				else 
					for (auto i = tree.begin(); i != tree.end(); ++i)
						std::cout << **i << std::endl;
				break;
		}
	} while (otvet != 'q');
}