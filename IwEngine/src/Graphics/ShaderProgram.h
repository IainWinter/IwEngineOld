#pragma once

#include <string>

struct ShaderProgramSource;

class ShaderProgram {
private:
	unsigned int _renderId;

	ShaderProgramSource ReadShader(const char* fileName);
	unsigned int CompileShader(unsigned int type, std::string source);
public:
	ShaderProgram(const char* fileName);
	~ShaderProgram();

	void Use();
	void Delete();
};

struct ShaderProgramSource {
	std::string vertex;
	std::string fragment;
};
