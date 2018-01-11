#pragma once

#include <atomic>
#include <string>
#include <memory>
#include "IwEngine\Common.h"

class IWENGINE_API Object {
private:
	//Wrappers for __dllspec C4251
	struct String { std::string string; };
	struct AtomicInt { std::atomic<int> atomic; };

	static AtomicInt _staticId;
	int _instanceId = ++_staticId.atomic;
	String _name;
public:
	virtual ~Object() = default;

	inline int GetInstanceID() const {
		return _instanceId;
	}

	inline const std::string& GetName() const {
		return _name.string;
	}

	inline Object& SetName(const std::string& name) {
		_name.string = name;
		return *this;
	}

	//static void Destroy(Object& object);
	//static Object* Instantiate(Object& object);
	//template<typename T> static Object* FindObjectsOfType();
	//template<typename T> static Object&?? FindObjectOfType();
};