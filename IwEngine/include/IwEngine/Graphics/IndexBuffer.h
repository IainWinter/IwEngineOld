#pragma once

#include "IwEngine\Common.h"

namespace Graphics {
	class IWENGINE_API IndexBuffer {
	private:
		uint _renderId;
		const void* _data;
		uint _count;
	public:
		IndexBuffer(const void* data, uint count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;
		void Draw() const;

		inline uint GetCount() const {
			return _count;
		}
	};
}