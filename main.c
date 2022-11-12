
#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "globals.h"
#include "engine/sandbox.h"

void ProcessInput(GLFWwindow* window, Sandbox* sandbox) {
	
	char title[64];

	// Process 'A'

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		SandboxProcessInput(sandbox, GLFW_KEY_A);

		snprintf(title, 64, "%s | LEFT", WINDOW_TITLE);
		glfwSetWindowTitle(window, title);
	}

	// Process 'D'

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		SandboxProcessInput(sandbox, GLFW_KEY_D);

		snprintf(title, 64, "%s | RIGHT", WINDOW_TITLE);
		glfwSetWindowTitle(window, title);
	}

	// Process Space Bar

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		SandboxProcessInput(sandbox, GLFW_KEY_SPACE);

		snprintf(title, 64, "%s | UP", WINDOW_TITLE);
		glfwSetWindowTitle(window, title);
	}

}

int main(void) {

	// Initialise GLFW

	if (!glfwInit()) {
		printf("Failed to initialise GLFW\n");
		exit(1);
	}

	// Create Window

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	if (!window) {
		printf("Failed to create window\n");
		exit(1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	printf("%s\n", glGetString(GL_VERSION));

	// Initialise GLEW

	if (glewInit() != GLEW_OK) {
		printf("Failed to initialise GLEW\n");
		exit(1);
	}
	
	// Create Sandbox
	
	Sandbox sandbox = SandboxInit();

	// Window Loop

	float32 time_delta = 0.0f;
	float32 last_frame = 0.0f;
	
	while (!glfwWindowShouldClose(window)) {
		
		glfwSetWindowTitle(window, WINDOW_TITLE);

		// Time

		float32 time = glfwGetTime();
		time_delta = time - last_frame;
		last_frame = time;

		// Process Input

		ProcessInput(window, &sandbox);

		// Update

		SandboxUpdate(&sandbox, time_delta);

		// Draw

		SandboxDraw(&sandbox);

		// Swap Buffers

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

}

