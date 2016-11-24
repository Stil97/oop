#include <iostream>
#include <memory>
#include <cstdlib>
#include <string.h>

template <class T> class TNtree;

template <class T> class TNtreeItem : public std::enable_shared_from_this<TNtreeItem<T>>{
public:
	friend class TNtree<T>;

	int GetCurrentN();
	std::shared_ptr<TNtreeItem<T>> GetFather() const;
	std::shared_ptr<T> GetValue() const;
	std::shared_ptr<TNtreeItem<T>> GetChild() const;
	std::shared_ptr<TNtreeItem<T>> GetBrother() const;
	char* GetId() const;
	
	std::shared_ptr<TNtreeItem> Getptr();

	std::shared_ptr<TNtreeItem<T>> Begin();

	std::shared_ptr<TNtreeItem<T>> Next();

	~TNtreeItem();
private:
	int numItems;
	std::shared_ptr<T> data;
	std::shared_ptr<TNtreeItem> child;
	std::shared_ptr<TNtreeItem> brother;
	std::weak_ptr<TNtreeItem> father;
	char *id;
};

