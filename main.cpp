#include <iostream>

#include "Trapezer.h"
#include "TNtree.h"

int main(int argc, char** argv) {
	char otvet;
	char idItem[15];
	char idDad[15];
	int n;
	Trapezer trapezer;
	TNtree tree;
	do {
		std::cout << "Menu:" << std::endl << " c - create \n s - set item\n p - print\n g - get item\n d - delet item\n q - quit\n" << std::endl;
		std::cin >> otvet;
		switch (otvet) {
		case 'c':
			std::cout << "Enter N" << std::endl;
			std::cin >> n;
			std::cout << "Enter root tree(trapezer:a,b,h and id node)" << std::endl;
			std::cin >> trapezer >> idItem;
			tree.TNtreeCreate(trapezer, n, idItem);
			break;
		case 's':
			std::cout << "Enter id Dad node" << std::endl;
			std::cin >> idDad;
			std::cout << "Enter node tree(trapezer:a,b,h and id node)" << std::endl;
			std::cin >> trapezer >> idItem;
			tree.SetNewItem(idDad, idItem, trapezer);
			break;
		case 'p':
			std::cout << tree;
			break;
		case 'g':
			std::cout << "Enter id item" << std::endl;
			std::cin >> idItem;
			trapezer = tree.GetItem(idItem);
			if (!(Trapezer(0, 0, 0) == trapezer))
				std::cout << trapezer;
			else
				std::cout << "Item with this id is not found" << std::endl;
			break;
		case 'd':
			std::cout << "Enter id deleted item" << std::endl;
			std::cin >> idItem;
			tree.DeleteItem(idItem);
			break;
		}
	} while (otvet != 'q');
}