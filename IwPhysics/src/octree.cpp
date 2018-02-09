#include "IwPhysics\octree.h"

iwphysics::octree::octree(const AABB& bounds, unsigned int level) : m_bounds(bounds), m_level(level) {
	m_items = std::vector<collider*>(m_capacity + 1);
}

iwphysics::octree::~octree() {
	delete[] m_children;
	//TODO: Check if this works
	for (size_t i = 0; i < m_items.size(); i++) {
		delete &m_items[i];
	}
}

bool iwphysics::octree::insert(collider* collider) {
	if (m_bounds.fits(collider->bounds())) {
		m_items.push_back(collider);
		if (m_items.size() > m_capacity) {
			split();
		}

		return true;
	}

	return false;
}

void iwphysics::octree::split() {
	/*
	x: ----++++
	y: --++--++
	z: -+-+-+-+

	(min), (mid)
	iwmath::vector3(min.x, min.y, mid.z), iwmath::vector3(mid.x, mid.y, max.z)
	iwmath::vector3(min.x, mid.y, min.z), iwmath::vector3(mid.x, max.y, mid.z)
	iwmath::vector3(min.x, mid.y, mid.z), iwmath::vector3(mid.x, max.y, max.z)
	iwmath::vector3(mid.x, min.y, min.z), iwmath::vector3(max.x, mid.y, mid.z)
	iwmath::vector3(mid.x, min.y, mid.z), iwmath::vector3(max.x, mid.y, max.z)
	iwmath::vector3(mid.x, mid.y, min.z), iwmath::vector3(max.x, max.y, mid.z)
	(mid), (max)
	*/
	iwmath::vector3& min = m_bounds.min;
	iwmath::vector3& mid = m_bounds.mid();
	iwmath::vector3& max = m_bounds.max;
	m_children = new octree[8]{
		octree(AABB(min, mid),																	 m_level + 1),
		octree(AABB(iwmath::vector3(min.x, min.y, mid.z), iwmath::vector3(mid.x, mid.y, max.z)), m_level + 1),
		octree(AABB(iwmath::vector3(min.x, mid.y, min.z), iwmath::vector3(mid.x, max.y, mid.z)), m_level + 1),
		octree(AABB(iwmath::vector3(min.x, mid.y, mid.z), iwmath::vector3(mid.x, max.y, max.z)), m_level + 1),
		octree(AABB(iwmath::vector3(mid.x, min.y, min.z), iwmath::vector3(max.x, mid.y, mid.z)), m_level + 1),
		octree(AABB(iwmath::vector3(mid.x, min.y, mid.z), iwmath::vector3(max.x, mid.y, max.z)), m_level + 1),
		octree(AABB(iwmath::vector3(mid.x, mid.y, min.z), iwmath::vector3(max.x, max.y, mid.z)), m_level + 1),
		octree(AABB(mid, max),																	 m_level + 1),
	};
}

iwphysics::octree& iwphysics::octree::getChild(unsigned int x, unsigned int y, unsigned int z) {
	return m_children[x + 2 * (y + 2 * z)];
}
