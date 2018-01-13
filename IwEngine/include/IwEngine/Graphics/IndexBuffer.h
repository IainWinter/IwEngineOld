#pragma once

#include "IwEngine\Common.h"

namespace Graphics {
	class IWENGINE_API IndexBuffer {
	private:
		uint _renderId;
		uint _count;
		const void* _data;
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