#include "IwEngine\Memory\LinearAllocator.h"
#include "IwEngine\Memory\PointerMath.h"

using namespace Memory;

LinearAllocator::LinearAllocator(size_t size, void* start) 
	: Allocator(size, start), _currentPos(start) 
{
	ASSERT(size != 0);
}

LinearAllocator::~LinearAllocator() {
	_currentPos = nullptr;
}

void* LinearAllocator::Allocate(size_t size, size_t alignment) {
	ASSERT(size != 0);
	size_t adjustment = AlignForwardAdjustment(_currentPos, alignment);
	if (_usedMemory + adjustment + size > _size) {
		return nullptr;
	}

	void* alignedAddress = (void*)((size_t)_currentPos + adjustment);
	_currentPos = (void*)((size_t)alignedAddress + size);
	_usedMemory += size + adjustment;
	_numAllocations++;

	return alignedAddress;
}

void LinearAllocator::Deallocate(void* pointer) {
	Utility::Error("LinearAllocator::Deallocate - Use Clear() instead");
	ASSERT(false && "Use Clear() instead");
}

void LinearAllocator::Clear() {
	_numAllocations = 0;
	_usedMemory = 0;
	_currentPos = _start;
}
