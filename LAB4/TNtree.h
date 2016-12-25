#include <iostream>
#include <memory>
#include <cstdlib>
#include <string.h>

template <class T> class TNtree;

template <class T> class TNtreeItem{
public:
	friend class TNtree<T>;
	int GetCurrentN() {
		return currentN;
	}
	~TNtreeItem() {
		delete[] id;
		currentN--;
	}
private:
	static int currentN;
	std::shared_ptr<T> data;
	std::shared_ptr<TNtreeItem> child;
	std::shared_ptr<TNtreeItem> brother;
	char *id;
};

template <class T> class TNtree {
public:
	TNtree();
	void TNtreeCreate(int n);
	void SetNewItem(const char *idDad, const char *idNew, std::shared_ptr<T>& trapezer);
	template <class T> friend std::ostream& operator << (std::ostream& os,TNtree<T>& tree);
	std::shared_ptr<T> GetItem(const char *idItem);
	void DeleteItem(const char *idItem);
	
	virtual ~TNtree();
private:
	std::shared_ptr<TNtreeItem<T>> NewTNtreeItem(const char *idNew, std::shared_ptr<T>& fig);
	std::shared_ptr<TNtreeItem<T>> DepthFirstSearch(std::shared_ptr<TNtreeItem<T>> root,const char *idSearch);
	void PrintNtree(std::shared_ptr<TNtreeItem<T>> root, std::ostream& os, int indent);
	
	std::shared_ptr<TNtreeItem<T>> SearchDeletedItem(std::shared_ptr<TNtreeItem<T>>, const char*);
	
	std::shared_ptr<TNtreeItem<T>> root;
	int N;
};
