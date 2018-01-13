#pragma once

#include "IwEngine\Common.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

namespace Graphics {
	class VertexArray {
	private:
		uint _renderId;
		std::vector<VertexBuffer*> _buffers;
		std::vector<VertexBufferLayout*> _layouts;
	public:
		IWENGINE_API VertexArray();
		IWENGINE_API ~VertexArray();

		IWENGINE_API void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		IWENGINE_API void Bind() const;
		IWENGINE_API void Unbind() const;
	};
}