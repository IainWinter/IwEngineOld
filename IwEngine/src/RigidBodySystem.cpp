#include "IwEngine\RigidBodySystem.h"
#include "IwEngine\Physics\PhysicsHelper.h"
#include "IwEngine\Collider.h"

void System<RigidBody, Transform>::Update(ComponentLookUp& componentLookUp, float deltaTime) {
	std::vector<int> transformGOIDs = componentLookUp.GetComponentTable<Transform>()->GetGameObjectIDs();
	std::vector<int> rigidBodyGOIDs = componentLookUp.GetComponentTable<RigidBody>()->GetGameObjectIDs();

	std::vector<int> gameObjectIDs = std::vector<int>();

	uint tCount = transformGOIDs.size();
	uint rCount = rigidBodyGOIDs.size();
	for (uint i = 0; i < tCount; i++) {
		for (uint j = 0; j < rCount; j++) {
			if (transformGOIDs[i] == rigidBodyGOIDs[j]) {
				gameObjectIDs.push_back(i);
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

		if (rigidBody->use_gravity) {
			Math::Vector3 gravity(0, -9.81f, 0);
			rigidBody->force = gravity.operator*(rigidBody->mass);
		}

		//rigidBody->force.operator+=(applied force vector);
		//float frictionForce = rigidBody->material.coef_kinetic_friction*rigidBody->mass*rigidBody->velocity.y;
		//Math::Vector3 forceFriction(frictionForce, 0, 0);
		//rigidBody->force += forceFriction;

		//Kinematics and drag
		float volume = collider->GetVolume();

		Math::Vector3 normV = -rigidBody->velocity.NormalizedFast();
		Math::Vector3 dragForce (rigidBody->drag * rigidBody->mass / volume * rigidBody->velocity * rigidBody->velocity / 2);

		rigidBody->force += dragForce * normV;

		Math::Vector3 acceleration = rigidBody->force / rigidBody->mass;

		position += rigidBody->velocity*deltaTime + acceleration / 2 * deltaTime * deltaTime;
		rigidBody->velocity += acceleration * deltaTime;
		transform->SetPosition(position);

		//Rotation
		Math::Vector3 angularAcc = rigidBody->torque / rigidBody->momentOfInertia;
		Math::Vector3 rotationChange = rigidBody->rotationalVelocity * deltaTime + angularAcc / 2 * deltaTime * deltaTime;

		transform->SetRotation(transform->GetRotation() * Math::Quaternion::FromEulerAngles(rotationChange));
		rigidBody->rotationalVelocity += (angularAcc * deltaTime);

		//Debugging
		std::cout << rigidBody->velocity << std::endl;
		std::cout << deltaTime << std::endl;
		std::cout << rigidBody->torque << std::endl;
	}
}
