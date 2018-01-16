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
#include <iostream>
#include <string>

void Demo1();
void Demo2();

int main() {
	int i;
	do {
		std::cout << "Demo: ";
		std::cin >> i;
		if (i == 1) {
			Demo1();
		} else if (i == 2) {
			Demo2();
		}
	} while (i != 0);
}

float getInput(std::string prompt) {
	std::cout << prompt;
	float i;
	std::cin >> i;
	return i;
}

void Demo1() {
	float mass1 = getInput("Please enter a Mass for Object 1 (left): ");
	float mass2 = getInput("Please enter a Mass for Object 2 (right): ");
	float vel1X = getInput("Please enter an x component of velocity for Object 1 (left): ");
	float vel1y = getInput("Please enter a y component of velocity for Object 1 (left): ");
	float vel2X = getInput("Please enter an x component of velocity for Object 2 (right): ");
	float vel2y = getInput("Please enter a y component of velocity for Object 2 (right): ");
	float elast = getInput("Please enter the elasticity of the collision: ");

	Engine* engine = new Engine();
	engine->Init();

	Scene& scene = engine->GetScene();

	GameObject& gameObject = scene.MakeGameObject();
	GameObject& gameObject2 = scene.MakeGameObject();

	Graphics::Mesh* mesh = Graphics::Mesh::MakeBox(Math::Vector3(-0.75f), 1.5f);
	Graphics::Mesh* mesh2 = Graphics::Mesh::MakeBox(Math::Vector3(-0.75f), 1.5f);

	Physics::BoundingBox* bounds = new Physics::BoundingBox(Math::Vector3(-0.75f), 1.5f);
	Physics::BoundingBox* bounds2 = new Physics::BoundingBox(Math::Vector3(-0.75f), 1.5f);

	RenderMesh* renderMesh = new RenderMesh(gameObject, mesh);
	RenderMesh* renderMesh2 = new RenderMesh(gameObject, mesh2);

	Collider* collider = new Collider(gameObject, bounds, Physics::PhysicsMaterial(0, 0, elast, Physics::FrictionCombine::ADD, Physics::BounceCombine::ADD));
	Collider* collider2 = new Collider(gameObject, bounds2, Physics::PhysicsMaterial(0, 0, elast, Physics::FrictionCombine::ADD, Physics::BounceCombine::ADD));

	gameObject.AddComponent<RenderMesh>(renderMesh);
	gameObject.AddComponent<Transform>(new Transform(gameObject, Math::Vector3(-5, -0.5f, -5)));
	gameObject.AddComponent<RigidBody>(new RigidBody(gameObject, mass1, 1, 1, false, Math::Vector3(vel1X, vel1y, 0), Math::Vector3(0, 0, 0)));
	gameObject.AddComponent<Collider>(collider);

	gameObject2.AddComponent<RenderMesh>(renderMesh2);
	gameObject2.AddComponent<Transform>(new Transform(gameObject2, Math::Vector3(5, -0.5f, -5)));
	gameObject2.AddComponent<RigidBody>(new RigidBody(gameObject2, mass2, 1, 0, false, Math::Vector3(vel2X, vel2y, 0), Math::Vector3(0, 0, 0)));
	gameObject2.AddComponent<Collider>(collider2);

	scene.MakeSystem<RenderMesh, Transform>();
	scene.MakeSystem<Collider, Transform>();
	scene.MakeSystem<RigidBody, Transform>();

	engine->Run();

	delete engine;
}

void Demo2() {
	float mass1 = getInput("Please enter a Mass for Object 1 (left): ");
	float mass2 = getInput("Please enter a Mass for Object 2 (right): ");
	float vel1X = getInput("Please enter an x component of velocity for Object 1 (left): ");
	float vel1y = getInput("Please enter a y component of velocity for Object 1 (left): ");
	float vel2X = getInput("Please enter an x component of velocity for Object 2 (right): ");
	float vel2y = getInput("Please enter a y component of velocity for Object 2 (right): ");
	float elast = getInput("Please enter the elasticity of the collision: ");

	Engine* engine = new Engine();
	engine->Init();

	Scene& scene = engine->GetScene();

	GameObject& gameObject = scene.MakeGameObject();
	GameObject& gameObject2 = scene.MakeGameObject();

	Graphics::Mesh* mesh = Graphics::Mesh::MakeBox(Math::Vector3(-0.75f), 1.5f);
	Graphics::Mesh* mesh2 = Graphics::Mesh::MakeBox(Math::Vector3(-0.75f), 1.5f);

	Physics::BoundingBox* bounds = new Physics::BoundingBox(Math::Vector3(-0.75f), 1.5f);
	Physics::BoundingBox* bounds2 = new Physics::BoundingBox(Math::Vector3(-0.75f), 1.5f);

	RenderMesh* renderMesh = new RenderMesh(gameObject, mesh);
	RenderMesh* renderMesh2 = new RenderMesh(gameObject, mesh2);

	Collider* collider = new Collider(gameObject, bounds, Physics::PhysicsMaterial(0, 0, elast, Physics::FrictionCombine::ADD, Physics::BounceCombine::ADD));
	Collider* collider2 = new Collider(gameObject, bounds2, Physics::PhysicsMaterial(0, 0, elast, Physics::FrictionCombine::ADD, Physics::BounceCombine::ADD));

	gameObject.AddComponent<RenderMesh>(renderMesh);
	gameObject.AddComponent<Transform>(new Transform(gameObject, Math::Vector3(-5, -0.5f, -5)));
	gameObject.AddComponent<RigidBody>(new RigidBody(gameObject, mass1, 1, 1, false, Math::Vector3(vel1X, vel1y, 0), Math::Vector3(0, 0, 0)));
	gameObject.AddComponent<Collider>(collider);

	gameObject2.AddComponent<RenderMesh>(renderMesh2);
	gameObject2.AddComponent<Transform>(new Transform(gameObject2, Math::Vector3(0, -0.5f, -5)));
	gameObject2.AddComponent<RigidBody>(new RigidBody(gameObject2, mass2, 1, 0, false, Math::Vector3(vel2X, vel2y, 0), Math::Vector3(0, 0, 0)));
	gameObject2.AddComponent<Collider>(collider2);

	scene.MakeSystem<RenderMesh, Transform>();
	scene.MakeSystem<Collider, Transform>();
	scene.MakeSystem<RigidBody, Transform>();

	engine->Run();

	delete engine;
}