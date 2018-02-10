#pragma once

#include <vector>
#include <ostream>
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

		unsigned int childToInsert(const AABB& aabb);
		void insertIntoNode(collider* collider);
	public:
		octree(const AABB& m_bounds, unsigned int m_level = 0);
		~octree();

		void clear();
		size_t size() const;
		bool insert(collider* collider);
		void split();

		inline std::vector<collider*> items() const {
			return m_items;
		}
	};
}