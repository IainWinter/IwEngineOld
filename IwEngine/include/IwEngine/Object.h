#pragma once

#include "Common.h"
#include <atomic>
#include <string>
#include <memory>

class IWENGINE_API Object {
private:
	//Wrappers for __dllspec C4251
	struct String { std::string string; };
	struct AtomicInt { std::atomic<int> atomic; };

	static AtomicInt _staticId;
	int _instanceId = ++_staticId.atomic;
	String _name;
public:
	inline int GetInstanceID() const {
		return _instanceId;
	}

	const std::string& GetName() const {
		return _name.string;
	}

	Object& SetName(const std::string& name) {
		_name.string = name;
		return *this;
	}

	//static void Destroy(Object& object);
	//static Object* Instantiate(Object& object);
	//template<typename T> static Object* FindObjectsOfType();
	//template<typename T> static Object&?? FindObjectOfType();
};