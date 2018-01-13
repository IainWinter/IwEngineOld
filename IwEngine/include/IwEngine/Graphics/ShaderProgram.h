#pragma once

#include <string>
#include "IwEngine\Common.h"

namespace Graphics {
	struct IWENGINE_API ShaderProgramSource;
	class IWENGINE_API ShaderProgram {
	private:
		uint _renderId;

		ShaderProgramSource ReadShader(const char* fileName);
		uint CompileShader(uint type, std::string source);
	public:
		ShaderProgram(const char* fileName);
		~ShaderProgram();

		void Use();
		void Delete();
	};

	struct IWENGINE_API ShaderProgramSource {
		std::string vertex;
		std::string fragment;
	};
}