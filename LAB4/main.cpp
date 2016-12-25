#include <iostream>
#include <memory>

#include "Figure.h"
#include "Trapezer.h"
#include "Pentagon.h"
#include "Rhombus.h"
#include "TNtree.h"

//int TNtreeItem::currentN ;

int main(int argc, char** argv) {
	char otvet;
	char idItem[15];
	char idDad[15];
	int n;
	Trapezer* trapezer = new Trapezer;
	Pentagon* pentagon = new Pentagon;
	Rhombus* rhombus = new Rhombus;
	std::shared_ptr<Figure> fig;


	TNtree<Figure> tree;
	do {
		std::cout << "Menu:" << std::endl << " c - create \n 1 - set Trapezer\n" <<
			 " 2 - set Pentagon\n 3 - set Rhombus \n p - print\n g - get item\n d - delet item\n q - quit\n" << std::endl;
		std::cin >> otvet;
		switch (otvet) {
			case 'c':
				std::cout << "Enter N" << std::endl;
				std::cin >> n;
				tree.TNtreeCreate(n);
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
		}
	} while (otvet != 'q');
}