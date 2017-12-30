#pragma once

namespace Graphics {
	class IndexBuffer {
	private:
		unsigned int _renderId;
		unsigned int _count;
	public:
		IndexBuffer(const void* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() const {
			return _count;
		}
	};
}