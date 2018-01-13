#pragma once

#include "IwEngine\Common.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

namespace Graphics {
	class IWENGINE_API VertexArray {
	private:
		uint _renderId;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;
	};
}