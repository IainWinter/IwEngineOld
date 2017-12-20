#pragma once

#include "Common.h"
#include <atomic>
#include <string>

class Object {
private:
	static std::atomic<int> m_staticId;
	int m_instanceId = ++m_staticId;
	std::string m_name;
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

std::atomic<int> Object::m_staticId;