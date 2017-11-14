#pragma once

#include <memory>
#include "ResourceLoaderBase.h"

template<typename T>
class ResourceLoader : public ResourceLoaderBase {
public:
	virtual ~ResourceLoader() {}

	virtual void Load(std::string fileName, std::shared_ptr<T> ptr) const = 0;
};