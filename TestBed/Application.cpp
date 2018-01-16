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

int main() {
	Engine* engine = new Engine();
	engine->Init();

	Scene& scene = engine->GetScene();

	GameObject& gameObject = scene.MakeGameObject();
	GameObject& gameObject2 = scene.MakeGameObject();

	Graphics::Mesh* mesh = Graphics::Mesh::MakeBox(Math::Vector3(-0.5f), 1);
	Graphics::Mesh* mesh2 = Graphics::Mesh::MakeBox(Math::Vector3(-0.5f), 1);
	
	Physics::BoundingBox* bounds = new Physics::BoundingBox(Math::Vector3(-0.5f), 1);
	Physics::BoundingBox* bounds2 = new Physics::BoundingBox(Math::Vector3(-0.5f), 1);

	RenderMesh* renderMesh = new RenderMesh(gameObject, mesh);
	RenderMesh* renderMesh2 = new RenderMesh(gameObject, mesh2);

	Collider* collider = new Collider(gameObject, bounds, Physics::PhysicsMaterial(0, 0, .5, Physics::FrictionCombine::ADD, Physics::BounceCombine::ADD));
	Collider* collider2 = new Collider(gameObject, bounds2, Physics::PhysicsMaterial(0, 0, 1, Physics::FrictionCombine::ADD, Physics::BounceCombine::ADD));

	gameObject.AddComponent<RenderMesh>(renderMesh);
	gameObject.AddComponent<Transform>(new Transform(gameObject, Math::Vector3(-0.5f, 0.0f, -5)));
	gameObject.AddComponent<RigidBody>(new RigidBody(gameObject, 1000000, 1, 1, false, Math::Vector3(0, 0, 0), Math::Vector3(0, 0, 0)));
	gameObject.AddComponent<Collider>(collider);

	gameObject2.AddComponent<RenderMesh>(renderMesh2);
	gameObject2.AddComponent<Transform>(new Transform(gameObject2, Math::Vector3(-0.5f, 5.0f, -5)));
	gameObject2.AddComponent<RigidBody>(new RigidBody(gameObject2, 1, 1, 0, true, Math::Vector3(0, 0, 0), Math::Vector3(0, 0, 0)));
	gameObject2.AddComponent<Collider>(collider2);

	scene.MakeSystem<RenderMesh, Transform>();
	scene.MakeSystem<Collider, Transform>();
	scene.MakeSystem<RigidBody, Transform>();

	engine->Run();
}