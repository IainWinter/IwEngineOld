#pragma once

#include "IwEngine\Common.h"
#include "IwEngine\Graphics\VertexArray.h" //TODO: Put in /src and acces through thread safe system (same goes for all \graphics\... .h)
#include "IwEngine\Graphics\IndexBuffer.h"
#include "IwEngine\Graphics\VertexBufferLayout.h" //TODO: Not this one though because it is thread safe

#include "IwMath\vector3.h"
#include "IwMath\quaternion.h"

namespace Graphics {
	class IWENGINE_API Mesh {
	private:
		Graphics::VertexArray* _vertexArray;
		Graphics::IndexBuffer* _indexBuffer;
	public:
		Mesh(Graphics::VertexArray* va, Graphics::IndexBuffer* ib);
		~Mesh();

		void Draw(const math::vector3& position, const math::quaternion& rotation) const;

		static Mesh* MakeBox(const math::vector3& bottomCorner, const math::vector3& scale);
		static Mesh* MakeSphere(const math::vector3& center, float radius, uint detail);
	};
}