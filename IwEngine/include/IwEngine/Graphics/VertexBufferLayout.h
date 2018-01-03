#pragma once

#include <vector>
#include "IwEngine\Common.h"
#include "IwEngine\Utility\Debug.h"

namespace Graphics {
	struct IWENGINE_API VertexBufferLayoutElement {
		uint type;
		uint count;
		unsigned char normalized;

		static uint GetSizeOfType(uint glType);
	};

	class IWENGINE_API VertexBufferLayout {
	private:
		struct VectorVertexBufferLayoutElement { std::vector<VertexBufferLayoutElement> vector; };

		VectorVertexBufferLayoutElement _elements;
		uint _stride;
	public:
		VertexBufferLayout() : _stride(0) {}

		template<typename T>
		void Push(uint count);

		template<>
		void Push<float>(uint count);

		template<>
		void Push<uint>(uint count);

		template<>
		void Push<unsigned char>(uint count);
		inline const std::vector<VertexBufferLayoutElement>& GetElements() const {
			return _elements.vector;
		}

		inline uint GetStride() const {
			return _stride;
		}
	};
}