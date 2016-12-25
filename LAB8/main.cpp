#include <iostream>
#include <memory>

#include "Figure.h"
#include "Trapezer.h"
#include "Pentagon.h"
#include "Rhombus.h"
#include "TNtree.h"

#include "TIterator.h"

using namespace std;

void printmenu() {
	cout << "Menu:" << endl;
	cout << "0 - print Menu" << endl;
	cout << "1 - set Trapezer" << endl;
	cout << "2 - set Pentagon" << endl;
	cout << "3 - set Rhombus" << endl;
	cout << "p - print" << endl;
	cout << "g - get item" << endl;
	cout << "d - delete item" << endl;
	cout << "4 - sort tree" << endl;
	cout << "5 - parallel sort tree" << endl;
	cout << "f - cycle \"for\"" << endl;
	cout << "q - quit" << endl;

}

int main(int argc, char** argv) {
	char otvet;
	char idItem[15];
	char idDad[15];

	Trapezer* trapezer = new Trapezer;
	Pentagon* pentagon = new Pentagon;
	Rhombus* rhombus = new Rhombus;
	std::shared_ptr<Figure> fig;

	printmenu();
	TNtree<Figure> tree;
	do {
		
		std::cin >> otvet;
		switch (otvet) {
			case '0':
				printmenu();
				break;
			case '1':
				std::cout << "Enter id Dad node" << std::endl;
				std::cin >> idDad;
				std::cout << "Enter node tree(trapezer:a,b,h and id node)" << std::endl;
				std::cin >> *trapezer >> idItem;
				fig = std::shared_ptr<Figure>(trapezer);
				tree.SetNewItem(idDad, idItem, fig);
				trapezer = new Trapezer;
				break;
			case '2':
				std::cout << "Enter id Dad node" << std::endl;
				std::cin >> idDad;
				std::cout << "Enter node tree(side pentagon and id node)" << std::endl;
				std::cin >> *pentagon >> idItem;
				fig = std::shared_ptr<Figure>(pentagon);
				tree.SetNewItem(idDad, idItem, fig);
				pentagon = new Pentagon;
				break;
			case '3':
				std::cout << "Enter id Dad node" << std::endl;
				std::cin >> idDad;
				std::cout << "Enter node tree(rhombus:a,h and id node)" << std::endl;
				std::cin >> *rhombus >> idItem;
				fig = std::shared_ptr<Figure>(rhombus);
				tree.SetNewItem(idDad, idItem, fig);
				rhombus = new Rhombus;
				break;
			case 'p':
				std::cout << tree;
				break;
			case 'g':
				std::cout << "Enter id item" << std::endl;
				std::cin >> idItem;
				fig = tree.GetItem(idItem);
				if (!fig)
					std::cout << "Item with this id is not found" << std::endl;
				else
					std::cout << *fig;
				break;
			case 'd':
				std::cout << "Enter id deleted item" << std::endl;
				std::cin >> idItem;
				tree.DeleteItem(idItem);
				break;
			case '4':
				tree.Sort();
				break;
			case '5':
				tree.ParallelSort();
				break;
			case 'f':
				if (tree.Empty())
					std::cout << "Tree empty" << std::endl;
				else 
				for (auto i = tree.begin(); i != tree.end(); ++i)
					std::cout << "{ " << **i << "} ";
				cout << endl;
				break;
		}
	} while (otvet != 'q');
}