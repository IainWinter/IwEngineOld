#pragma once

#ifdef IWENGINE_EXPORTS
#define IWENGINE_API __declspec(dllexport)
#else
#define IWENGINE_API __declspec(dllimport)
#endif

typedef unsigned int uint;