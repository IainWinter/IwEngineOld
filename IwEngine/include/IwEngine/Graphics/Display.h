#pragma once

#include "IwEngine\Common.h"

//Temp
#include "IwEngine\Events\EventBus.h"

namespace Graphics {
	class IWENGINE_API Display {
	private:
		Events::EventBus* eventBus;
		void Init();
	public:
		int Start();
	};
}