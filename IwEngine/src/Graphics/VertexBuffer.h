#pragma once

namespace Graphics {
	class VertexBuffer {
	private:
		unsigned int _renderId;
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
	};
}