#pragma once

#include "Common.h"
#include <atomic>
#include <string>

class Object {
private:
	static std::atomic<int> _staticId;
	int _instanceId = ++_staticId;
	std::string _name;
public:
	IWENGINE_API inline int GetInstanceID() const {
		return _instanceId;
	}

	IWENGINE_API inline const std::string& GetName() const {
		return _name;
	}

	IWENGINE_API inline Object& SetName(const std::string& name) {
		_name = name;
		return *this;
	}

	//static void Destroy(Object& object);
	//static Object* Instantiate(Object& object);
	//template<typename T> static Object* FindObjectsOfType();
	//template<typename T> static Object&?? FindObjectOfType();
};

std::atomic<int> Object::_staticId;