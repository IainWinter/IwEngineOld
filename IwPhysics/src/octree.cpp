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
	m_items.push_back(collider);

	if (m_items.size() > m_capacity) {
		split();
		return true;
	}

	if (m_bounds.fits(collider->bounds())) {

	}

	return false;
}

void iwphysics::octree::split() {

}

iwphysics::octree& iwphysics::octree::getChild(unsigned int x, unsigned int y, unsigned int z) {
	return m_children[x + 2 * (y + 2 * z)];
}
