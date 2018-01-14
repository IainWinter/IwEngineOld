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

#include "IwEngine\Collider.h"
#include "IwEngine\Transform.h"
#include "IwEngine\Physics\BoundingBox.h"
#include "IwEngine\Physics\BoundingSphere.h"

int main() {
	Engine* engine = new Engine();
	engine->Init();

	Scene& scene = engine->GetScene();

	GameObject& gameObject = scene.MakeGameObject();

	Graphics::Mesh* mesh = Graphics::Mesh::MakeBox(Math::Vector3(-0.5f), 1);
	
	Physics::BoundingBox* bounds = new Physics::BoundingBox(Math::Vector3(-0.5f), 1);

	RenderMesh* renderMesh = new RenderMesh(gameObject, mesh);

	Collider* collider = new Collider(gameObject, bounds);

	gameObject.AddComponent<RenderMesh>(renderMesh);
	gameObject.AddComponent<Transform>(new Transform(gameObject, Math::Vector3(-0.5f, -0.5f, -5)));
	gameObject.AddComponent<RigidBody>(new RigidBody(gameObject, 50, 50, Math::Vector3(0, 0, 0), Math::Vector3(0, 10, 10)));
	gameObject.AddComponent<Collider>(collider);

	scene.MakeSystem<RenderMesh, Transform>();
	scene.MakeSystem<Collider, Transform>();
	scene.MakeSystem<RigidBody, Transform>();

	engine->Run();
}