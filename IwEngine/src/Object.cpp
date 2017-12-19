#include "IwEngine\Object.h"

inline int Object::GetInstanceID() const {
	return instance_id_;
}

inline const std::string& Object::GetName() const {
	return name_;
}

inline Object& Object::SetName(const std::string& name) {
	name_ = name;
	return *this;
}

inline Object& Object::SetName(const char* name) {
	name_ = name;
	return *this;
}