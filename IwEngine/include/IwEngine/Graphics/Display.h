#pragma once

#ifdef IWENGINE_EXPORTS
#define IWENGINE_API __declspec(dllexport)
#else
#define IWENGINE_API __declspec(dllimport)
#endif

class Display {
public: 
	IWENGINE_API Display();
	IWENGINE_API int Start();
};