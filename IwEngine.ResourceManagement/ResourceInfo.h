#pragma once
#include <string>

struct ResourceInfo {
	const char* const name;
	const uintmax_t size;
	ResourceInfo(const char* name, uintmax_t size);
};