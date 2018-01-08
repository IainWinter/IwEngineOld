#pragma once

namespace Memory {
	void* AlignForward(void* address, size_t alignment) {
		return (void*)((reinterpret_cast<size_t>(address) + (alignment - 1)) & (~(alignment - 1)));
	}

	size_t AlignForwardAdjustment(const void* address, size_t alignment) {
		size_t adjustment = alignment - (reinterpret_cast<size_t>(address) & (alignment - 1));
		if (adjustment == alignment) {
			return 0;
		}

		return adjustment;
	}

	size_t AlignForwardAdjustmentWithHeader(const void* address, size_t alignment, size_t headerSize) {
		size_t adjustment = AlignForwardAdjustment(address, alignment);
		size_t neededSpace = headerSize;
		if (adjustment < neededSpace) {
			neededSpace -= adjustment;
			//Fit adjustment to header
			adjustment += alignment * (neededSpace / alignment);
			if (neededSpace % alignment > 0) {
				adjustment += alignment;
			}
		}

		return adjustment;
	}
}