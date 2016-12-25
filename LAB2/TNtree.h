#ifndef TNTREE_H
#define TNTREE_H

#include <iostream>

#include "Trapezer.h"

struct TNtreeItem{
	Trapezer data;
	int numChilds;
	TNtreeItem **childs;
	char *id;
};

class TNtree {
public:
	TNtree();
	void TNtreeCreate(const Trapezer& trapezer,int n,char *idRoot);
	void SetNewItem(const char *idDad, const char *idNew, Trapezer& trapezer);
	friend std::ostream& operator << (std::ostream& os,TNtree& tree);
	Trapezer GetItem(const char *idItem);
	void DeleteItem(const char *idItem);

	~TNtree();
private:
	TNtreeItem* NewTNtreeItem(const char *idNew,const Trapezer& trapezer);
	void DepthFirstSearch(TNtreeItem* root,const char *idSearch);
	void PrintNtree(TNtreeItem * root,std::ostream& os, int indent);
	
	void SearchDeletedItem(TNtreeItem*, const char*);
	TNtreeItem* DeleteUnderTree(TNtreeItem*);

	TNtreeItem *root;
	int N;
	int currentN;
};


#endif