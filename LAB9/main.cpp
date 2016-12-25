#include <iostream>
#include <memory>
#include <functional>
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
	cout << "4 - insert to list command: generate figure" << endl;
	cout << "5 - insert to list command: delete squere less that x" << endl;
	cout << "6 - insert to list command: print tree" << endl;
	cout << "7 - perform all the teams in the list" << endl;
	cout << "f - cycle \"for\"" << endl;
	cout << "q - quit" << endl;

}

int main(int argc, char** argv) {
	char otvet;

	srand(time(0));

	typedef function<void(void)> Tcom;
	Trapezer* trapezer = new Trapezer;
	Pentagon* pentagon = new Pentagon;
	Rhombus* rhombus = new Rhombus;
	std::shared_ptr<Figure> fig;
	int a;
	TNtree<Figure> tree;
	TList<Tcom> list;
	Tcom command;
	double square;
	int count;
	printmenu();
	
	do {
		
		std::cin >> otvet;
		switch (otvet) {
			case '0':
				printmenu();
				break;
			case '1':
				std::cout << "Enter node tree(trapezer:a,b,h)" << std::endl;
				std::cin >> *trapezer;
				fig = std::shared_ptr<Figure>(trapezer);
				tree.InsertItem( fig);
				trapezer = new Trapezer;
				break;
			case '2':
				std::cout << "Enter node tree(side pentagon)" << std::endl;
				std::cin >> *pentagon;
				fig = std::shared_ptr<Figure>(pentagon);
				tree.InsertItem(fig);
				pentagon = new Pentagon;
				break;
			case '3':
				std::cout << "Enter node tree(rhombus:a,h)" << std::endl;
				std::cin >> *rhombus;
				fig = std::shared_ptr<Figure>(rhombus);
				tree.InsertItem(fig);
				rhombus = new Rhombus;
				break;
			case 'p':
				std::cout << tree;
				break;
			case 'f':
				if (tree.Empty())
					std::cout << "Tree empty" << std::endl;
				else 
				for (auto i = tree.begin(); i != tree.end(); ++i)
					std::cout << "{ " << **i << "} ";
				cout << endl;
				break;
			case '4':
				cout << "enter the number of figures: ";
				cin >> count;
				command = [&, count]() {
					int i = count;
					cout << "Command generate " << i << " figure" << endl;
					for (; i > 0; --i) {
						switch (rand() % 3) {
						case 0:
							fig = shared_ptr<Figure>(new Trapezer(rand() % 100 + 1, rand() % 100 + 1 , rand() % 100 + 1));
							tree.InsertItem(fig);
							break;
						case 1:
							a = rand() % 100 + 1;
							fig = shared_ptr<Figure>(new Rhombus(a, rand() % a + 1));
							tree.InsertItem(fig);
							break;
						case 2:
							fig = shared_ptr<Figure>(new Pentagon(rand() % 100 + 1));
							tree.InsertItem(fig);
							break;
						}
					}

				};
				list.Insert(list.Size() + 1, make_shared<Tcom>(command));
				break;
			case '5':
				cout << "Enter square: ";
				cin >> square;
				command = [&, square]() {
					double sq = square;
					cout << "Command deleted figure, with square less then " << sq << endl;
					for (auto i = tree.begin(); i != tree.end();) {
						if ((*i)->Square() < sq) {
							auto j = i;
							i++;
							tree.DeleteItem(j);
						}
						else
							i++;
					}
				};
				list.Insert(list.Size() + 1, make_shared<Tcom>(command));
				break;
			case '6':
				command = [&]() {
					cout << "Command print" << endl;
					cout << tree;
				};
				list.Insert(list.Size() + 1, make_shared<Tcom>(command));
				break;
			case '7':
				for (auto i = list.begin(); i != list.end();) {
					(**i)();
					auto j = i;
					i++;
					list.Delete(j);
				}
				break;		
		}
	} while (otvet != 'q');
}