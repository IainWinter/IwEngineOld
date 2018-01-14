#include "IwEngine\RigidBodySystem.h"
#include "IwEngine\Physics\PhysicsHelper.h"

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
		Math::Vector3 position = transform->GetPosition();
		Math::Quaternion rotation = transform->GetRotation();
		//if (rigidBody->use_gravity) {
			Math::Vector3 gravity(0, -9.81f, 0);
			rigidBody->force.operator+=(gravity);
		//}
		//rigidBody->force.operator+=(applied force vector);
		//float frictionForce = rigidBody->material.coef_kinetic_friction*rigidBody->mass*rigidBody->velocity.y;
		//rigidBody->force.x += frictionForce;
		Math::Vector3 acceleration = rigidBody->force.operator/=(rigidBody->mass);
		position.operator+=(rigidBody->velocity.operator*=(deltaTime)+acceleration.operator/=(2).operator*=(deltaTime*deltaTime));
		transform->SetPosition(position);
		rigidBody->velocity.operator+=(acceleration.operator*(deltaTime));
		//Math::Vector3 angularAcceleration = rigidBody->torque.operator/=(rigidBody->momentOfInertia);
	    //Math::Quaternion rotationalChange(rigidBody->rotationalVelocity.operator*=(deltaTime)+angularAcceleration.operator*=(2).operator*=(deltaTime*deltaTime), 1);
		//transform->SetRotation(rotation.operator+=(rotationalChange));
		//rigidBody->rotationalVelocity.operator+=(angularAcceleration*deltaTime);

		//transform->SetPosition(transform->GetPosition() - Math::Vector3(deltaTime, deltaTime, deltaTime));
	}
}
