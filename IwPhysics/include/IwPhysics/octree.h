#pragma once

#include <vector>
#include "iwphysics.h"
#include "Collisions\AABB.h"
#include "Collisions\collider.h"

namespace iwphysics {
	class IWPHYSICS_API octree {
	private:
		unsigned int m_level;
		AABB m_bounds;
		octree* m_children[8];
		std::vector<collider>* m_items;
	public:
		octree(const AABB& m_bounds, unsigned int m_level = 0);
		~octree();

		//add
		//remove
		//get
		//

	};
}