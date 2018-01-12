#include "IwEngine\Engine.h"
#include "IwEngine\Scene.h"
#include "IwEngine\RenderMesh.h"
#include "IwEngine\GameObject.h"
#include "IwEngine\Common.h"

int main() {
	Engine* engine = new Engine();
	engine->Init();

	Scene& scene = engine->GetScene();

	GameObject& gameObject = scene.MakeGameObject();

	float* data = new float[6]{
		-0.5f, -0.5f,
		 0.5f, -0.0f,
		 0.0f,  0.5f
	};

	uint* index = new uint[3]{
		1, 2, 3
	};

	Graphics::VertexBufferLayout layout = Graphics::VertexBufferLayout();
	layout.Push<float>(2);

	Graphics::Mesh* mesh = new Graphics::Mesh(data, 6, layout, index, 3);
	
	RenderMesh* renderMesh = new RenderMesh(gameObject, mesh);

	gameObject.AddComponent<RenderMesh>(renderMesh);

	scene.MakeSystem<RenderMesh>();

	engine->Run();

	delete engine;
}