#ifndef TNTREE_H
#define TNTREE_H

#include <iostream>
#include <memory>
#include <cstdlib>
#include <string.h>

#include "Figure.h"
//#include "Trapezer.h"

class TNtreeItem{
public:
	friend class TNtree;
	int GetCurrentN() {
		return currentN;
	}
	~TNtreeItem() {
		delete[] id;
		currentN--;
	}
private:
	static int currentN;
	std::shared_ptr<Figure> data;
	std::shared_ptr<TNtreeItem> child;
	std::shared_ptr<TNtreeItem> brother;
	char *id;
};

class TNtree {
public:
	TNtree();
	void TNtreeCreate(int n);
	void SetNewItem(const char *idDad, const char *idNew, std::shared_ptr<Figure>& trapezer);
	friend std::ostream& operator << (std::ostream& os,TNtree& tree);
	std::shared_ptr<Figure> GetItem(const char *idItem);
	void DeleteItem(const char *idItem);

	virtual ~TNtree();
private:
	std::shared_ptr<TNtreeItem> NewTNtreeItem(const char *idNew, std::shared_ptr<Figure>& trapezer);
	void DepthFirstSearch(std::shared_ptr<TNtreeItem> root,const char *idSearch);
	void PrintNtree(std::shared_ptr<TNtreeItem> root, std::ostream& os, int indent);
	
	void SearchDeletedItem(std::shared_ptr<TNtreeItem>, const char*);

	std::shared_ptr<TNtreeItem> root;
	int N;
	
};


#endif