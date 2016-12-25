#ifndef _TLISTFORALLOCATOR_H_
#define _TLISTFORALLOCATOR_H_

#include <cstdlib>
#include "TListForAllocator.h"

typedef unsigned char byte;

class TAllocationBlock {
public:
	TAllocationBlock(size_t size, size_t count);
	void* Allocate();
	void Deallocate(void* ptr);
	~TAllocationBlock();
private:
	byte* usedBlocks;
	TListForAllocator<void*> freeBlocks;
};

#endif