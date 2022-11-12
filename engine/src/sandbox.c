
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "../sandbox.h"
#include "../renderer.h"
#include "../globals.h"
#include "../io.h"

Sandbox SandboxInit() {

	Sandbox sandbox;

	sandbox.quad = QuadInit(
		QUAD_TYPE_PLAYER_CONTROLLED,
		(Colour) { 1.0f, 0.0f, 0.0f },
		(Location) { 300.0f, 400.0f },
		(Size) { 75.0f, 75.0f },
		(Velocity) { 0.0f , 0.0f }
	);

	sandbox.default_shader = ShaderProgramInit("shaders/default-vert.txt", "shaders/default-frag.txt");
	sandbox.texure_list = TextureListInit();

	TextureListAdd(&sandbox.texure_list, "resources/pop-cat.png", TRUE);
	mat4x4_ortho(sandbox.projection, 0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -1.0f, 1.0f);

	// Create Buffers

	glGenVertexArrays(1, &sandbox.vao);
	glGenBuffers(1, &sandbox.vbo);
	glGenBuffers(1, &sandbox.ibo);

	// Bind

	glBindVertexArray(sandbox.vao);
	glBindBuffer(GL_ARRAY_BUFFER, sandbox.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sandbox.ibo);

	// Allocate Data

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, NULL, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float32) * 6, NULL, GL_STATIC_DRAW);

	// Define Layout

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, colour));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, tex_coords));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, tex_id));
	glEnableVertexAttribArray(3);

	return sandbox;

}

void SandboxSubmitData(Sandbox* sandbox) {
	
	// Fill Vertex Buffer

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4, sandbox->quad.vertices);

	// Fill Index Buffer

	uint32 indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(float32) * 6, indices);

}

void SandboxUpdate(Sandbox* sandbox, float32 time_delta) {

	PhysicsUpdateQuad(&sandbox->quad, time_delta);

	SandboxSubmitData(sandbox);

}

void SandboxDraw(Sandbox* sandbox) {

	// Clear

	RendererClear();

	// Uniforms

	glUseProgram(sandbox->default_shader.ID);

	int32 u_projection = glGetUniformLocation(sandbox->default_shader.ID, "u_Projection");
	int32 u_Texture = glGetUniformLocation(sandbox->default_shader.ID, "u_Texture");

	glUniformMatrix4fv(u_projection, 1, GL_FALSE, &sandbox->projection[0][0]);
	glUniform1i(u_Texture, 0);

	// Draw

	RendererDraw(sandbox->vao, sandbox->vbo, sandbox->ibo, 12);

}

void SandboxProcessInput(Sandbox* sandbox, uint32 input) {

	switch (input) {
		case GLFW_KEY_A:
			sandbox->quad.velocity.x = -2.0f;
			break;
		case GLFW_KEY_D:
			sandbox->quad.velocity.x = 2.0f;
			break;
		case GLFW_KEY_SPACE:
			sandbox->quad.velocity.y = 2.0f;
			break;
	}

}
