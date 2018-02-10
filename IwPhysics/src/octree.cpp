#include "IwPhysics\octree.h"

iwphysics::octree::octree(const AABB& bounds, unsigned int level) : m_bounds(AABB(bounds)), m_level(level) {
	m_items = std::vector<collider*>();
	m_items.reserve(m_capacity + 1);
	m_children = nullptr;
}

iwphysics::octree::~octree() {
	if (m_children != nullptr) {
		delete[] m_children;
	}

	for (size_t i = 0; i < m_items.size(); i++) {
		delete m_items[i];
	}
}

unsigned int iwphysics::octree::childToInsert(const AABB& aabb) {
	iwmath::vector3 aabbMid = aabb.mid();
	iwmath::vector3 mid = m_bounds.mid();

	bool x, y, z;

	if (abs(aabbMid.x - mid.x) > abs(aabbMid.x - aabb.min.x)) {
		x = aabbMid.x > mid.x;
	} else {
		return -1; //Crosses y-axis
	}

	if (abs(aabbMid.y - mid.y) > abs(aabbMid.y - aabb.min.y)) {
		y = aabbMid.y > mid.y;
	} else {
		return -1; //Crosses x-axis
	}

	if (abs(aabbMid.z - mid.z) > abs(aabbMid.z - aabb.min.z)) {
		z = aabbMid.z > mid.z;
	} else {
		return -1; //Crosses z-axis
	}

	if (x) {
		if (y) {
			if (z) {
				return 7;
			} else {
				return 6;
			}
		} else {
			if (z) {
				return 5;
			} else {
				return 4;
			}
		}
	} else {
		if (y) {
			if (z) {
				return 3;
			} else {
				return 2;
			}
		} else {
			if (z) {
				return 1;
			} else {
				return 0;
			}
		}
	}
}

void iwphysics::octree::insertIntoNode(collider* collider) {
	if (m_children != nullptr) {
		unsigned int childIndex = childToInsert(collider->bounds());
		if (childIndex != -1) {
			m_children[childIndex].insertIntoNode(collider);
		}
	} else {
		m_items.push_back(collider);
		if (m_items.size() > m_capacity) {
			split();
		}
	}
}

void iwphysics::octree::clear() {
	m_items.clear();
}

size_t iwphysics::octree::size() const {
	return m_items.size();
}

bool iwphysics::octree::insert(collider* collider) {
	if (m_bounds.fits(collider->bounds())) {
		insertIntoNode(collider);
		return true;
	}

	return false;
}

void iwphysics::octree::split() {
	/*
	x: ----++++
	y: --++--++
	z: -+-+-+-+
	*/
	iwmath::vector3& min = m_bounds.min;
	iwmath::vector3& mid = m_bounds.mid();
	iwmath::vector3& max = m_bounds.max;

	iwmath::vector3 scale = (max - min) / 2;

	iwmath::vector3 nnn = (min + mid) / 2;
	iwmath::vector3 nnp = iwmath::vector3(nnn.x, nnn.y, nnn.z + scale.z);
	iwmath::vector3 npn = iwmath::vector3(nnn.x, nnn.y + scale.y, nnn.z);
	iwmath::vector3 npp = iwmath::vector3(nnn.x, nnn.y + scale.y, nnn.z + scale.z);
	iwmath::vector3 pnn = iwmath::vector3(nnn.x + scale.x, nnn.y, nnn.z);
	iwmath::vector3 pnp = iwmath::vector3(nnn.x + scale.x, nnn.y, nnn.z + scale.z);
	iwmath::vector3 ppn = iwmath::vector3(nnn.x + scale.x, nnn.y + scale.y, nnn.z);
	iwmath::vector3 ppp = nnn + scale;

	m_children = new octree[8]{
		octree(AABB(nnn, scale), m_level + 1),
		octree(AABB(nnp, scale), m_level + 1),
		octree(AABB(npn, scale), m_level + 1),
		octree(AABB(npp, scale), m_level + 1),
		octree(AABB(pnn, scale), m_level + 1),
		octree(AABB(pnp, scale), m_level + 1),
		octree(AABB(ppn, scale), m_level + 1),
		octree(AABB(ppp, scale), m_level + 1),
	};

	std::vector<collider*> items = m_items;
	clear();
	for (size_t i = 0; i < items.size(); i++) {
		insert(items[i]);
	}
}