#include "ResourceInfo.h"

struct Resource {
public:
	const ResourceInfo* const info;
	//const RsrouceData* data;

	Resource() : info(nullptr) {

	}

	Resource(ResourceInfo* resourceInfo) : info(resourceInfo) {

	}

	~Resource() {
		//delete &data;
	}
};

