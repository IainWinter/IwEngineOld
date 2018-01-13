#pragma once

#include "IwEngine\Common.h"

namespace Graphics {
	class IWENGINE_API VertexBuffer {
	private:
		uint _renderId;
		const void* _data;
	public:
		VertexBuffer(const void* data, uint size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
	};
}