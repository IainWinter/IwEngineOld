#pragma once

#include "Common.h"
#include <atomic>
#include <string>

class Object {
private:
	static std::atomic<int> static_id_;
	int instance_id_ = ++static_id_;
	std::string name_;
public:
	IWENGINE_API inline int GetInstanceID() const;
	IWENGINE_API inline const std::string& GetName() const;
	IWENGINE_API inline Object& SetName(const std::string& name);
	IWENGINE_API inline Object& SetName(const char* name);

	//static void Destroy(Object& object);
	//static Object* Instantiate(Object& object);
	//template<typename T> static Object* FindObjectsOfType();
	//template<typename T> static Object&??? FindObjectOfType();
};

std::atomic<int> Object::static_id_;