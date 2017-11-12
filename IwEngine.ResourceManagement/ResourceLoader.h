#pragma once

#include <memory>

template<class T>
class ResourceLoader {
public:
	ResourceLoader();
	~ResourceLoader();
	virtual void Load(std::shared_ptr<T> ptr) const = 0;
};

template<class T>
inline ResourceLoader<T>::ResourceLoader() {
}

template<class T>
inline ResourceLoader<T>::~ResourceLoader() {
}
