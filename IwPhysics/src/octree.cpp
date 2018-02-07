#include "IwPhysics\octree.h"

using namespace iwphysics;

octree::octree(const AABB& bounds, unsigned int level) : m_bounds(bounds), m_level(level) {
	m_items = std::vector<collider*>(1);
}

octree::~octree() {
	delete[] m_children;
	//Check for error
	for (size_t i = 0; i < m_items.size(); i++) {
		delete &m_items[i];
	}
}

void octree::add(collider* item) {
	//check if going to spit. Over max item count
	//if it is then add collider to items and split()
	//if it is not then just add item to items

	m_items.push_back(item);
	if (m_items.size() > m_maxItemCount) {
		split();
	}
}

void octree::remove(const collider& item) {
	m_items.erase(m_items.begin(), m_items.end(), item);
}
