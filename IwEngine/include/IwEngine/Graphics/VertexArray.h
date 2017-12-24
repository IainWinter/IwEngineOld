#pragma once

#include "IwEngine\Graphics\VertexBufferLayout.h"
#include "IwEngine\Graphics\VertexBuffer.h"

class VertexArray {
private:
	unsigned int _renderId;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

