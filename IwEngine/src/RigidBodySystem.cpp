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
		if (dragForce.LengthFast() >= rigidBody->force.LengthFast()) {
			dragForce = -rigidBody->force;
		}
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

		//Collisions
		if (collider->GetCollisionData()->intersects) {
			//Math::Vector3 otherVelocity = collisiondata.getOtherVelocity;
			//float otherMass = collisiondata.getOtherMass;
			//Math::Vector3 momentum = rigidBody->velocity * rigidBody->mass;
			//Math::Vector3 otherMomentum = otherVelocity * otherMass;
			//float elasicity = rigidBody->GetGameObject
			//float otherelasticity = collisiondata.otherelasticity
			//float combine = rigidBody->material.elasticity;//*collisiondata.elasticity
			//Math::Vector3 totalMomentum = momentum; //-othermomentum
			//float KineticE1 = 1 / 2 * rigidBody->mass * rigidBody->velocity * rigidBody->velocity;
			//float KineticE2 = 1 / 2 * other.getmass * other.velocity ^2;
			//float postKE1 = KineticE1 * combine;
			//float postKE2 = KineticE2 * combine;
			if (/*combine < .5*/false) {
				if(false/*momentum1 > momentum2*/){}
			}
		}

		//Debugging
		std::cout << rigidBody->velocity << std::endl;
		std::cout << deltaTime << std::endl;
		std::cout << rigidBody->torque << std::endl;
	}
}
