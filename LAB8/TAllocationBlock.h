#include <cstdlib>
#include "TList.h"

typedef unsigned char byte;

class TAllocationBlock {
public:
	TAllocationBlock(size_t size, size_t count);
	void* Allocate();
	void Deallocate(void* ptr);
	~TAllocationBlock();
private:
	byte* usedBlocks;
	TList<void*> freeBlocks;
};