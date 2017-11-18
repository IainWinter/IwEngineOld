#pragma once

#include "ResourceInfo.cpp"

struct Resource {
public:
	const ResourceInfo* const info;
	//const RsrouceData* data;

	Resource() : info() {

	}

	~Resource() {
		//delete &data;
	}
};

