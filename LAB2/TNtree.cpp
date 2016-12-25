#include <iostream>
#include <cstdlib>
//#include <cstring>
#include <string.h>
#include "TNtree.h"

TNtree::TNtree() : root(0) ,N(0) ,currentN(0) {};

void TNtree::TNtreeCreate(const Trapezer& trapezer,int n,char *idRoot)  {
	N = n;
	currentN = 1;
	root = NewTNtreeItem(idRoot, trapezer);
};

TNtreeItem* TNtree::NewTNtreeItem(const char *idNew, const Trapezer& trapezer) {
	TNtreeItem *newItem = new TNtreeItem;
	newItem->data = trapezer;
	newItem->numChilds = 0;
	newItem->childs = (TNtreeItem**)malloc(sizeof(TNtreeItem*));
	newItem->childs[0] = 0;
	size_t size = strlen(idNew) + 1;
	newItem->id = new char[size];
	strcpy_s(newItem->id, size, idNew);
	return newItem;
}

TNtreeItem *item = 0;

void TNtree::DepthFirstSearch(TNtreeItem* root,const char *idSearch) {
	if (!root)
		return;
	else if (!(strcmp(root->id, idSearch)))
		item = root;
	else
		for (int i = 0; i < root->numChilds; ++i)
			DepthFirstSearch(root->childs[i], idSearch);
}

void TNtree::SetNewItem(const char *idDad, const char *idNew, Trapezer& trapezer) {
	if (N == 0)
	{
		std::cout << "Not created Ntree" << std::endl;
		return;
	}
	if (!root)
	{
		currentN = 1;
		root = NewTNtreeItem(idNew, trapezer);
		return;
	}
	item = 0;
	DepthFirstSearch(root, idDad);
	if (!item)
		std::cout << "Item with this id is not found" << std::endl;
	else if (N == currentN)
		std::cout << "Limit elements exhausted" << std::endl;
	else
	{
		currentN++;
		item->numChilds++;
		item->childs = (TNtreeItem**)realloc(item->childs, sizeof(TNtreeItem*)*(item->numChilds + 1));
		item->childs[item->numChilds-1] = NewTNtreeItem(idNew, trapezer);
	}
	
}


std::ostream& operator <<(std::ostream &os,TNtree& tree) {
	if (tree.N == 0)
	{
		os << "\nTNtree not ctreated\n" << std::endl;
		return os;
	}
	os << std::endl << "currentN=" << tree.currentN << "\n\n";
	tree.PrintNtree(tree.root,os, 0);
	os << std::endl;
	return os;
}

void TNtree::PrintNtree(TNtreeItem *root,std::ostream& os, int indent) {
	if (!root)
		return;
	for (int i = 0; i < indent; i++)
		os << "   ";
	os << "id:" << root->id << " " << root->data;
	for (int i = 0; i < root->numChilds; i++)
		PrintNtree(root->childs[i],os, indent + 3);
}

Trapezer TNtree::GetItem(const char *idItem) {
	if (N == 0)
	{
		std::cout << "\nTNtree not ctreated\n" << std::endl;
		return Trapezer(0, 0, 0);
	}
	item = 0;
	DepthFirstSearch(root, idItem);
	if (!item)	
		return Trapezer(0, 0, 0);
	else
		return item->data;
}

int indexDeletedItem;

void TNtree::DeleteItem(const char *idItem) {
	if (N == 0)
	{
		std::cout << "\nTNtree not ctreated\n" << std::endl;
		return;
	}
	item = 0;
	indexDeletedItem = -1;
	SearchDeletedItem(root, idItem);
	if (!item)
		std::cout << "Item with this id is not found" << std::endl;
	else if (item == root && indexDeletedItem == -1)
		root = DeleteUnderTree(root);
	else
	{
		item->childs[indexDeletedItem] = DeleteUnderTree(item->childs[indexDeletedItem]);
		for (int i = indexDeletedItem + 1; i < item->numChilds; i++)
			item->childs[i - 1] = item->childs[i];
		item->numChilds--;
		item->childs = (TNtreeItem**) realloc(item->childs, sizeof(TNtreeItem*) * (item->numChilds + 1));
	}
}


void TNtree::SearchDeletedItem(TNtreeItem* root, const char *idItem) {
	if (!root)
		return;
	else if (!strcmp(root->id, idItem))
		item = root;
	else
	{
		for (int i = 0; i < root->numChilds; i++)
			if (!strcmp(root->childs[i]->id, idItem))
			{
				item = root;
				indexDeletedItem = i;
				return;
			}
		for (int i = 0; i < root->numChilds; i++)
			SearchDeletedItem(root->childs[i], idItem);
	}
}

TNtreeItem* TNtree::DeleteUnderTree(TNtreeItem* root) {
	if (!root)
		return root;
	for (int i = 0; i < root->numChilds; i++)
		root->childs[i] = DeleteUnderTree(root->childs[i]);
	delete[] root->childs;
	delete[] root->id;
	delete root;
	this->currentN--;
	return 0;
}

TNtree::~TNtree()  {
	root = DeleteUnderTree(root);
	N = 0;
	currentN = 0;
}