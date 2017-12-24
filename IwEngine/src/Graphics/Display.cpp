#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "IwEngine\Graphics\Display.h"
#include "IwEngine\Utility\Logger.h"
#include "IwEngine\Utility\IO\File.h"
#include <sstream>

#include "IwEngine\Graphics\VertexBuffer.h"
#include "IwEngine\Graphics\VertexArray.h"
#include "IwEngine\Graphics\IndexBuffer.h"
#include "IwEngine\Math\Matrix4x4.h"

Display::Display() {

}

struct ShaderProgramSource {
	std::string vertex;
	std::string fragment;
};

static ShaderProgramSource ParseShader(std::vector<std::string> code) {
	Utility::Debug("Reading shaders...");
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

static unsigned int CompileShader(unsigned int type, const std::string src) {
	Utility::Debug("Compiling shader...");
	unsigned int id = glCreateShader(type);
	const char* source = src.c_str();
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		glDeleteShader(id);

		Utility::Error(message);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vs, const std::string& fs) {
	unsigned int program = glCreateProgram();
	unsigned int vsid = CompileShader(GL_VERTEX_SHADER, vs);
	unsigned int fsid = CompileShader(GL_FRAGMENT_SHADER, fs);

	glAttachShader(program, vsid);
	glAttachShader(program, fsid);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vsid);
	glDeleteShader(fsid);

	return program;
}

int Display::Start() {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		Utility::Error("GLEW init not ok");
	}

	float pos[] = {
		//left
		-0.5f, -0.5f, -0.5f,
		-0.5f, +0.5f, +0.5f,
		-0.5f, +0.5f, -0.5f,
		-0.5f, -0.5f, +0.5f,
		//right
		+0.5f, -0.5f, +0.5f,
		+0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, +0.5f,
		+0.5f, -0.5f, -0.5f,
		//bottom
		-0.5f, -0.5f, -0.5f,
		+0.5f, -0.5f, +0.5f,
		-0.5f, -0.5f, +0.5f,
		+0.5f, -0.5f, -0.5f,
		//top
		 -0.5f, +0.5f, +0.5f,
		+0.5f, +0.5f, -0.5f,
		-0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, +0.5f,
		//back
		 +0.5f, -0.5f, -0.5f,
		-0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		//front
		-0.5f, -0.5f, +0.5f,
		+0.5f, +0.5f, +0.5f,
		-0.5f, +0.5f, +0.5f,
		+0.5f, -0.5f, +0.5f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};

	VertexArray va;
	VertexBuffer vb(pos, 3 * 24 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 36);

	ShaderProgramSource source = ParseShader(Utility::IO::ReadFileLines("res/shaders/default.shader"));
	unsigned int shader = CreateShader(source.vertex, source.fragment);
	glUseProgram(shader);
	glUniform4f(1, .4f, 1.0f, .2f, 1.0f);

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Math::Vector3 position = Math::Vector3(0, 0, 0);
	Math::Matrix4x4 perp = Math::Matrix4x4::CreatePerspectiveFieldOfView(1.7f, 640.0f / 480, 0.01f, 100.0f);
		/*Math::Matrix4x4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 0, 
		0, 0, 0, 1
	);*/

	while (!glfwWindowShouldClose(window)) {
		position.z += 0.001f;

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);
		glUniform4f(1, .4f, 1.0f, .2f, 1.0f);

		Math::Matrix4x4 p = Math::Matrix4x4::CreateTranslation(position);

		std::cout << (perp * p) << std::endl;

		glUniformMatrix4fv(0, 1, GL_FALSE, (perp * p).elements);

		va.Bind();
		ib.Bind();

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}