#include "IwEngine\Object.h"

inline int Object::GetInstanceID() const {
	return m_instanceId;
}

inline const std::string& Object::GetName() const {
	return m_name;
}

inline Object& Object::SetName(const std::string& name) {
	m_name = name;
	return *this;
}

inline Object& Object::SetName(const char* name) {
	m_name = name;
	return *this;
}