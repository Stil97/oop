#include "TAllocationBlock.h"

TAllocationBlock::TAllocationBlock(size_t size, size_t count) {
	usedBlocks = (byte*)malloc(size * count);
	for (size_t i = 0; i < count; i++) {
		void* ptrFree = (void*)malloc(sizeof(void*));
		ptrFree = usedBlocks + i * size;
		freeBlocks.Insert(i + 1, ptrFree);
	}
}

void* TAllocationBlock::Allocate() {
	if (!freeBlocks.Empty()){
		void* result = freeBlocks.Get(1);
		freeBlocks.Delete(1);
		return result;
	}
	else
		throw std::bad_alloc();
}

void TAllocationBlock::Deallocate(void* ptr) {
	freeBlocks.Insert(1, ptr);
}

TAllocationBlock::~TAllocationBlock() {
	free(usedBlocks);
}