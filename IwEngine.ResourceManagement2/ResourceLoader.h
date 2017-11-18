#pragma once

#include <memory>
#include "ResourceLoaderBase.h"
#include <string>

template<typename TResource>
class ResourceLoader : public ResourceLoaderBase {
public:
	virtual ~ResourceLoader() {}

	virtual TResource Load(const char* fileName) const = 0;
};