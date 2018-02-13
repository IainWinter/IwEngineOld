#pragma once

#include <vector>
#include <ostream>
#include "IwPhysics\iwphysics.h"
#include "AABB.h"
#include "collider.h"

#define OCTREE_MAX_LEVEL 8

namespace iwphysics {
	class IWPHYSICS_API octree {
	private:
		static constexpr unsigned int m_capacity = 8;
		unsigned int m_level;
		std::vector<collider*> m_items;
		octree* m_children;
		AABB m_bounds;

		unsigned int child_to_insert(const AABB& aabb);
		void insert_into_node(collider* collider);
	public:
		octree(const AABB& m_bounds, unsigned int m_level = 0);
		~octree();

		void clear();
		size_t size() const;
		bool insert(collider* collider);
		void split();
		bool isLeaf() const;

		inline std::vector<collider*> items() const {
			return m_items;
		}

		friend IWPHYSICS_API std::ostream& operator<<(std::ostream& stream, const octree& octree);
		friend IWPHYSICS_API std::stringstream& operator<<(std::stringstream& stream, const octree& octree);
	};
}