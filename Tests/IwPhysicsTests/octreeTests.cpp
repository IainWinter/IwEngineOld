#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IwPhysicsTests {
	TEST_CLASS(octreeTests) {
	public:
		TEST_METHOD(octreeInsertTest) {
			iwphysics::AABB aabb = iwphysics::AABB(iwmath::vector3::zero, iwmath::vector3(10000));

			iwphysics::octree octree = iwphysics::octree(aabb);

			srand(time(nullptr));
			for (size_t i = 0; i < 10000; i++) {
				float x = (rand() / (float)RAND_MAX - .5f) * 9999.0f;
				float y = (rand() / (float)RAND_MAX - .5f) * 9999.0f;
				float z = (rand() / (float)RAND_MAX - .5f) * 9999.0f;
				iwphysics::box_collider* box_collider = new iwphysics::box_collider(iwmath::vector3(x, y, z), iwmath::vector3::one);
				octree.insert(box_collider);
			}

			std::stringstream ss = std::stringstream();
			ss << octree;
			Logger::WriteMessage(ss.str().c_str());
		}
	};
}