#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Graphics\VertexArray.h" //TODO: Put in /src and acces through thread safe system (same goes for all \graphics\... .h)
#include "IwEngine\Graphics\IndexBuffer.h"
#include "IwEngine\Graphics\VertexBufferLayout.h" //TODO: Not this one though because it is thread safe

#include "IwEngine\Math\Vector3.h"
#include "IwEngine\Math\Quaternion.h"

namespace Graphics {
	class IWENGINE_API Mesh {
	private:
		Graphics::VertexArray* _vertexArray;
		Graphics::IndexBuffer* _indexBuffer;
	public:
		Mesh(Graphics::VertexArray* va, Graphics::IndexBuffer* ib);
		~Mesh();

		void Draw(const Math::Vector3& position, const Math::Quaternion& rotation) const;

		static Mesh* MakeBox(const Math::Vector3& bottomCorner, const Math::Vector3& scale);
		static Mesh* MakeSphere(const Math::Vector3& center, float radius, uint detail);
	};
}