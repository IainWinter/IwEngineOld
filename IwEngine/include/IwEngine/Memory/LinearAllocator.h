#pragma once

#include "Allocator.h"

namespace Memory {
	class LinearAllocator : public Allocator {
	private:
		LinearAllocator(const LinearAllocator&);
		LinearAllocator& operator=(const LinearAllocator&) {}
		void* _currentPos;
	public:
		LinearAllocator(size_t size, void* start);
		~LinearAllocator();
		void* Allocate(size_t size, size_t alignment) override;
		void Deallocate(void* pointer) override;
		void Clear();
	};
}