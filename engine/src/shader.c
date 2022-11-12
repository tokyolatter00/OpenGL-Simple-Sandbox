
#include <stdio.h>
#include <GLEW/glew.h>
#include "../shader.h"
#include "../io.h"

static uint32 CompileShader(char* path, uint32 type) {

	// Load Shader from Disk

	File file = FileRead(path);

	// Create & Compile Shader

	uint32 shader = glCreateShader(type);
	glShaderSource(shader, 1, &file.Data, NULL);
	glCompileShader(shader);

	// Error Checking

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (!result) {
		char log[512];
		glGetShaderInfoLog(shader, 512, NULL, log);

		printf("Error: %s\n", log);
	}

	// Cleanup

	FileFree(&file);

	return shader;

}

ShaderProgram ShaderProgramInit(char* vertex_path, char* fragment_path) {

	// Compile Shaders

	uint32 vertex_shader = CompileShader(vertex_path, GL_VERTEX_SHADER);
	uint32 fragment_shader = CompileShader(fragment_path, GL_FRAGMENT_SHADER);

	// Create Shader Program

	uint32 program = glCreateProgram();

	// Attach Shaders

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	// Link Shader Program

	glLinkProgram(program);

	// Delete Shaders

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return (ShaderProgram) { .ID = program };

}
