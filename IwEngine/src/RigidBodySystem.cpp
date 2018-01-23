#include "IwEngine\RigidBodySystem.h"
#include "IwEngine\Physics\PhysicsHelper.h"
#include "IwEngine\Collider.h"
#include "IwEngine\Physics\CollisionData.h"

void System<RigidBody, Transform>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	std::vector<int> transformGOIDs = componentLookUp.GetComponentTable<Transform>()->GetGameObjectIDs();
	std::vector<int> rigidBodyGOIDs = componentLookUp.GetComponentTable<RigidBody>()->GetGameObjectIDs();

	std::vector<int> gameObjectIDs = std::vector<int>();

	uint tCount = transformGOIDs.size();
	uint rCount = rigidBodyGOIDs.size();
	for (uint i = 0; i < tCount; i++) {
		for (uint j = 0; j < rCount; j++) {
			if (transformGOIDs[i] == rigidBodyGOIDs[j]) {
				gameObjectIDs.push_back(transformGOIDs[i]);
				i++;
			}
		}
	}

	uint gCount = gameObjectIDs.size();
	for (size_t i = 0; i < gCount; i++) {
		Transform* transform = componentLookUp.GetComponentTable<Transform>()->GetComponent(gameObjectIDs[i]);
		RigidBody* rigidBody = componentLookUp.GetComponentTable<RigidBody>()->GetComponent(gameObjectIDs[i]);
		Collider* collider = componentLookUp.GetComponentTable<Collider>()->GetComponent(gameObjectIDs[i]);

		Math::Vector3 position = transform->GetPosition();
		Math::Quaternion rotation = transform->GetRotation();

		checkGravity(rigidBody);

		//rigidBody->force.operator+=(applied force vector);
		//float frictionForce = rigidBody->material.coef_kinetic_friction*rigidBody->mass*rigidBody->velocity.y;
		//Math::Vector3 forceFriction(frictionForce, 0, 0);
		//rigidBody->force += forceFriction;

		//Kinematics and drag
		drag(rigidBody, collider);

		motion(rigidBody, transform, position, deltaTime);

		//Rotation

		rotate(rigidBody, transform, deltaTime);
	}
}

void System<RigidBody, Transform>::checkGravity(RigidBody* rigidbody) {
	if (rigidbody->use_gravity) {
		Math::Vector3 gravity(0, -9.81f, 0);
		rigidbody->force = gravity * rigidbody->mass;
	}
}

void System<RigidBody, Transform>::drag(RigidBody * rigidbody, Collider * collider) {
	float volume = collider->GetVolume();

	Math::Vector3 normV = -rigidbody->velocity.NormalizedFast();
	Math::Vector3 dragForce(rigidbody->drag * rigidbody->mass / volume * rigidbody->velocity * rigidbody->velocity / 2);
	if (dragForce.LengthFast() >= rigidbody->force.LengthFast()) {
		dragForce = -rigidbody->force;
	}

	rigidbody->force += dragForce * normV;
}

void System<RigidBody, Transform>::motion(RigidBody* rigidbody, Transform* transform, Math::Vector3 position, float deltaTime) {
	Math::Vector3 acceleration = rigidbody->force / rigidbody->mass;

	position += rigidbody->velocity*deltaTime + acceleration / 2 * deltaTime * deltaTime;
	rigidbody->velocity += acceleration * deltaTime;
	transform->SetPosition(position);
}

void System<RigidBody, Transform>::rotate(RigidBody * rigidbody, Transform * transform, float deltaTime) {
	Math::Vector3 angularAcc = rigidbody->torque / rigidbody->momentOfInertia;
	Math::Vector3 rotationChange = rigidbody->rotationalVelocity * deltaTime + angularAcc / 2 * deltaTime * deltaTime;

	transform->SetRotation(transform->GetRotation() * Math::Quaternion::FromEulerAngles(rotationChange));
	rigidbody->rotationalVelocity += (angularAcc * deltaTime);
}
