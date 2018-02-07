#pragma once

#include <vector>
#include "iwphysics.h"
#include "Collisions\AABB.h"
#include "Collisions\collider.h"

namespace iwphysics {
	class IWPHYSICS_API octree {
	private:
		const unsigned int m_maxItemCount = 8; // Hardcoded item count before spliting
		unsigned int m_level;
		AABB m_bounds;
		octree* m_children;
		std::vector<collider*> m_items;
	public:
		octree(const AABB& m_bounds, unsigned int m_level = 0);
		~octree();

		void add(collider* item);
		void remove(const collider& item);
		void split();
		collider* items();
		const AABB& bounds();
	};
}