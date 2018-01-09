#pragma once

#include "IwEngine\Common.h"

//Temp
#include "IwEngine\Engine.h"

namespace Graphics {
	class IWENGINE_API Display {
	private:
		Engine* engine;
		void Init();
	public:
		int Start();
	};
}