#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Utility\Debug.h"
#include "IwEngine\Utility\Logger.h"

namespace Memory {
	class IWENGINE_API Allocator {
	protected:
		size_t _size;
		size_t _usedMemory;
		size_t _numAllocations;
		void* _start;
	public:
		Allocator(size_t size, void* start) : _size(size), _start(start) {
			_usedMemory = 0;
			_numAllocations = 0;
		}

		virtual ~Allocator() {
			if (_usedMemory != 0 && _numAllocations != 0) {
				Utility::ThrowRunTimeError("Memory leak in linear allocator!!");
			}

			_size = 0;
			_start = nullptr;
		}

		virtual void* Allocate(size_t size, size_t alignment = 4) = 0;
		virtual void Deallocate(void* pointer) = 0;

		inline size_t GetSize() const {
			return _size;
		}

		inline size_t GetUsedMemory() const {
			return _usedMemory;
		}

		inline size_t GetNumberOfAllocations() const {
			return _numAllocations;
		}

		inline void* GetStart() const {
			return _start;
		}
	};

	template <typename T>
	T* AllocateNew(Allocator& allocator) {
		return new (allocator.Allocate(sizeof(T), __alignof(T))) T;
	}

	template <typename T>
	T* AllocateNew(Allocator& allocator, const T& t) {
		return new (allocator.Allocate(sizeof(T), __alignof(T))) T(t);
	}

	template <typename T>
	void DeallocateDelete(Allocator& allocator, T& object) {
		object.~T();
		allocator.Deallocate(&object);
	}

	template <typename T>
	T* AllocateArray(Allocator& allocator, size_t length) {
		ASSERT(length != 0);
		size_t headerSize = sizeof(size_t) / sizeof(T);
		if (sizeof(size_t) % sizeof(T) > 0) {
			headerSize += 1;
		}

		//Allocate size of array
		T* pointer = (T*)(allocator.Allocate(sizeof(T)*(length + headerSize), __alignof(T))) + headerSize;
		*(((size_t*)pointer) - 1) = length;
		for (size_t i = 0; i < length; i++) {
			new (&pointer) T;
		}

		return pointer;
	}

	template <typename T>
	void DeallocateArray(Allocator& allocator, T* array) {
		ASSERT(array != nullptr);
		size_t length = *(((size_t*)array) - 1);
		for (size_t i = 0; i < length; i++) {
			array.~T();
		}

		size_t headerSize = sizeof(size_t) / sizeof(T);
		if (sizeof(size_t) % sizeof(T) > 0) {
			headerSize += 1;
		}

		allocator.deallocate(array - headerSize);
	}
}