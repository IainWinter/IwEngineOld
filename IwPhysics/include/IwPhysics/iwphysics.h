#pragma once

#ifdef IWPHYSICS_EXPORTS
#define IWPHYSICS_API __declspec(dllexport)
#else
#define IWPHYSICS_API __declspec(dllimport)
#endif