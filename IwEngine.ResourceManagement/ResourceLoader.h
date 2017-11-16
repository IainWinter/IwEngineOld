#pragma once

#include <memory>
#include "ResourceLoaderBase.h"
#include <string>

template<typename TResource>
class ResourceLoader : public ResourceLoaderBase {
public:
	virtual ~ResourceLoader() {}

	virtual TResource Load(const std::string& fileName) const = 0;
};