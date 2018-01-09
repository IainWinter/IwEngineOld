#pragma once

#include "Allocator.h"

namespace Memory {
	class IWENGINE_API LinearAllocator : public Allocator {
	private:
		void* _currentPos;
	public:
		LinearAllocator(size_t size, void* start);
		~LinearAllocator();

		LinearAllocator(const LinearAllocator&) = delete;
		LinearAllocator& operator=(const LinearAllocator&) = delete;

		void* Allocate(size_t size, size_t alignment) override;
		void Deallocate(void* pointer) override;
		void Clear();
	};
}