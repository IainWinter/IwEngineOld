#include "IwEngine\Engine.h"
#include "IwEngine\Scene.h"
#include "IwEngine\RenderMesh.h"
#include "IwEngine\RigidBody.h"
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

	Graphics::Mesh* mesh = Graphics::Mesh::MakeBox(Math::Vector3(-0.5f), 1);
	
	RenderMesh* renderMesh = new RenderMesh(gameObject, mesh);

	gameObject.AddComponent<RenderMesh>(renderMesh);
	gameObject.AddComponent<Transform>(new Transform(gameObject, Math::Vector3(0, 0, -2), Math::Quaternion::FromEulerAngles(0, 0.7853982f, 0)));

	gameObject.AddComponent<RigidBody>(new RigidBody(gameObject));

	scene.MakeSystem<RenderMesh, Transform>();
	scene.MakeSystem<RigidBody, Transform>();

	engine->Run();
}