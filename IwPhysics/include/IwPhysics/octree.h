#pragma once

#include <vector>
#include "iwphysics.h"
#include "Collisions\AABB.h"
#include "Collisions\collider.h"

namespace iwphysics {
	class IWPHYSICS_API octree {
	private:
		static constexpr unsigned int m_capacity = 8;
		unsigned int m_level;
		std::vector<collider*> m_items;
		octree* m_children;
		AABB m_bounds;
	public:
		octree(const AABB& m_bounds, unsigned int m_level = 0);
		~octree();

		bool insert(collider* collider);
		void split();
		octree& getChild(unsigned int x, unsigned int y, unsigned int z);
		inline std::vector<collider*> items() const {
			return m_items;
		}
	};
}