#include "TNtree.h"

int TNtreeItem::currentN;

TNtree::TNtree() : root(0) ,N(0) {};

void TNtree::TNtreeCreate(int n)  {
	N = n;
	root = 0;
	TNtreeItem::currentN = 0;
};

std::shared_ptr<TNtreeItem> TNtree::NewTNtreeItem(const char *idNew, std::shared_ptr<Figure>& fig) {
	auto newItem = std::shared_ptr<TNtreeItem>(new TNtreeItem);
	newItem->data = fig;
	newItem->child = 0;
	newItem->brother = 0;
	size_t size = strlen(idNew) + 1;
	newItem->id = new char[size];
	strcpy_s(newItem->id, size, idNew);
	newItem->currentN++;
	return newItem;
}

std::shared_ptr<TNtreeItem> item = 0;

void TNtree::DepthFirstSearch(std::shared_ptr<TNtreeItem> root, const char *idSearch) {
	auto son = root->child;
	if (!root)
		return;
	else if (!(strcmp(root->id, idSearch)))
		item = root;
	else
		while (son) {
			DepthFirstSearch(son, idSearch);
			son = son->brother;
		}
}

void TNtree::SetNewItem(const char *idDad, const char *idNew, std::shared_ptr<Figure>& fig) {
	if (N == 0)
	{
		std::cout << "Not created Ntree" << std::endl;
		return;
	}
	if (!root)
	{
		root = NewTNtreeItem(idNew, fig);
		return;
	}
	item = 0;
	DepthFirstSearch(root, idDad);
	if (!item)
		std::cout << "Item with this id is not found" << std::endl;
	else if (N == root->currentN)
		std::cout << "Limit elements exhausted" << std::endl;
	else
	{
		auto son = item->child;
		while (son && son->brother)
			son = son->brother;
		if (!son)
			item->child = NewTNtreeItem(idNew, fig);
		else
			son->brother = NewTNtreeItem(idNew, fig);
	}
	
}


std::ostream& operator <<(std::ostream &os,TNtree& tree) {
	if (tree.N == 0)
	{
		os << "\nTNtree not ctreated\n" << std::endl;
		return os;
	}
	os << std::endl << "currentN=" << tree.root->GetCurrentN() << "\n\n";
	tree.PrintNtree(tree.root,os, 0);
	os << std::endl;
	return os;
}

void TNtree::PrintNtree(std::shared_ptr<TNtreeItem> root, std::ostream& os, int indent) {
	if (!root)
		return;
	for (int i = 0; i < indent; i++)
		os << "   ";
	os << "id:" << root->id << " " << *root->data;
	auto son = root->child;
	while (son) {
		PrintNtree(son, os, indent + 3);
		son = son->brother;
	}
}

std::shared_ptr<Figure> TNtree::GetItem(const char *idItem) {
	if (N == 0)
	{
		std::cout << "\nTNtree not ctreated\n" << std::endl;
		return 0;
	}
	item = 0;
	DepthFirstSearch(root, idItem);
	if (!item)	
		return 0;
	else
		return item->data;
}

std::shared_ptr<TNtreeItem> deletedItem;

void TNtree::DeleteItem(const char *idItem) {
	if (N == 0)
	{
		std::cout << "\nTNtree not ctreated\n" << std::endl;
		return;
	}
	item = 0;
	deletedItem = 0;
	SearchDeletedItem(root, idItem);
	if (!item)
		std::cout << "Item with this id is not found" << std::endl;
	else if (item == root && deletedItem == 0) {
		root = 0;
		item = 0;
	}
	else
	{
		auto son = item->child;
		while (son != deletedItem && son->brother != deletedItem)
			son = son->brother;
		if (son == deletedItem) {
			item->child = son->brother;
			deletedItem = 0;
		}				
		else {
			son->brother = deletedItem->brother;
			deletedItem = 0;
		}
	}
}


void TNtree::SearchDeletedItem(std::shared_ptr<TNtreeItem> root, const char *idItem) {
	auto son = root->child;
	if (!root)
		return;
	else if (!strcmp(root->id, idItem))
		item = root;
	else
	{
		while (son) {
			if (!strcmp(son->id, idItem))
			{
				item = root;
				deletedItem = son;
				return;
			}
			son = son->brother;
		}
		son = root->child;
		while (son) {
			SearchDeletedItem(son, idItem);
			son = son->brother;
		}
	}
}

TNtree::~TNtree()  {
	root = 0;
	N = 0;

}