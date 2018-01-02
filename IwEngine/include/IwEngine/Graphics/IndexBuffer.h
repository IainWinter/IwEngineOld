#pragma once

#include "IwEngine\Common.h"

namespace Graphics {
	class IndexBuffer {
	private:
		uint _renderId;
		uint _count;
	public:
		IndexBuffer(const void* data, uint count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline uint GetCount() const {
			return _count;
		}
	};
}