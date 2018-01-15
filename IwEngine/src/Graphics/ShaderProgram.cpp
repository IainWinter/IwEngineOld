#include <sstream>
#include <vector>
#include "GL\glew.h"
#include "IwEngine\Graphics\ShaderProgram.h"
#include "IwEngine\Utility\IO\File.h"
#include "IwEngine\Utility\Logger.h"

using namespace Graphics;

ShaderProgram::ShaderProgram(const char* fileName) {
	ShaderProgramSource source = ReadShader(fileName);

	_renderId = glCreateProgram();
	uint vsid = CompileShader(GL_VERTEX_SHADER, source.vertex);
	uint fsid = CompileShader(GL_FRAGMENT_SHADER, source.fragment);

	glAttachShader(_renderId, vsid);
	glAttachShader(_renderId, fsid);
	glLinkProgram(_renderId);
	glValidateProgram(_renderId);

	glDeleteShader(vsid);
	glDeleteShader(fsid);
}

ShaderProgram::~ShaderProgram() {
	Delete();
}

ShaderProgramSource ShaderProgram::ReadShader(const char* fileName) {
	std::vector<std::string> code = Utility::IO::ReadFileLines(fileName);
	std::stringstream ss[2];
	enum ShaderMode {
		NONE = -1,
		VERTEX,
		FRAGMENT
	};

	ShaderMode mode;
	for (std::string& line : code) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)  mode = VERTEX;
			else if (line.find("fragment") != std::string::npos)  mode = FRAGMENT;
		} else {
			ss[mode] << line << std::endl;
		}
	}

	return ShaderProgramSource{ ss[VERTEX].str(), ss[FRAGMENT].str() };
}

uint ShaderProgram::CompileShader(uint type, std::string source) {
	uint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		glDeleteShader(id);

		Utility::Error(message);
		return 0;
	}

	return id;
}

void ShaderProgram::Use() {
	glUseProgram(_renderId);
}

void ShaderProgram::Delete() {
	glDeleteProgram(_renderId);
}
