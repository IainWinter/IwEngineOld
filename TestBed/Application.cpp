#include "IwEngine\Engine.h"
#include "IwEngine\Scene.h"
#include "IwEngine\RenderMesh.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\Common.h"

#include "IwEngine\Graphics\VertexArray.h"
#include "IwEngine\Graphics\IndexBuffer.h"
#include "IwEngine\Graphics\VertexBuffer.h"
#include "IwEngine\Graphics\Mesh.h"

int main() {
	Engine* engine = new Engine();
	engine->Init();

	Scene& scene = engine->GetScene();

	GameObject& gameObject = scene.MakeGameObject();


	float pos[] = {
		//left
		-0.5f, -0.5f, -0.5f,
		-0.5f, +0.5f, -0.5f,
		-0.5f, +0.5f, +0.5f,
		-0.5f, -0.5f, +0.5f,
		//right
		+0.5f, -0.5f, -0.5f,
		+0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, +0.5f,
		+0.5f, -0.5f, +0.5f,
		//bottom
		-0.5f, -0.5f, -0.5f,
		+0.5f, -0.5f, -0.5f,
		+0.5f, -0.5f, +0.5f,
		-0.5f, -0.5f, +0.5f,
		//top
		-0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, +0.5f,
		-0.5f, +0.5f, +0.5f,
		//back
		-0.5f, -0.5f, -0.5f,
		+0.5f, -0.5f, -0.5f,
		+0.5f, +0.5f, -0.5f,
		-0.5f, +0.5f, -0.5f,
		//front
		-0.5f, -0.5f, +0.5f,
		+0.5f, -0.5f, +0.5f,
		+0.5f, +0.5f, +0.5f,
		-0.5f, +0.5f, +0.5f
	};



	uint indices[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};

	Graphics::VertexBufferLayout layout;
	layout.Push<float>(3);

	Graphics::VertexArray* va = new Graphics::VertexArray();

	Graphics::IndexBuffer* ib = new Graphics::IndexBuffer(indices, 36);

	Graphics::VertexBuffer vb(pos, 72 * sizeof(float));

	va->AddBuffer(vb, layout);

	Graphics::Mesh* mesh = new Graphics::Mesh(va, ib);
	
	RenderMesh* renderMesh = new RenderMesh(gameObject, mesh);

	gameObject.AddComponent<RenderMesh>(renderMesh);

	scene.MakeSystem<RenderMesh>();

	engine->Run();

	delete engine;
}