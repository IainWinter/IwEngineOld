#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "IwEngine\Graphics\Display.h"
#include "IwEngine\Utility\Logger.h"
#include "IwEngine\Utility\IO\File.h"

Display::Display() {

}

struct ShaderProgramSource {
	std::string vertex;
	std::string fragment;
};

static ShaderProgramSource ParseShader(std::string* code) {
	for (size_t i = 0; i < 17; i++) {
		Utility::Info(code[i]);
	}
	return ShaderProgramSource();
}

static unsigned int CompileShader(unsigned int type, const std::string src) {
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

	float pos[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	ShaderProgramSource source = ParseShader(Utility::IO::ReadFileLines("C:/dev/code/c++/IwEngine/TestBed/res/shaders/default.shader"));

	unsigned int shader = CreateShader("", "");

	glUseProgram(shader);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}