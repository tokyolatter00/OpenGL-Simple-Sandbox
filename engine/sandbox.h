
#pragma once

#include <LINMATH/linmath.h>
#include "physics.h"
#include "shader.h"
#include "texture.h"

typedef struct _Sandbox {
	mat4x4 projection;
	Quad quad;

	int32 vao;
	int32 vbo;
	int32 ibo;

	ShaderProgram default_shader;
	TextureList texure_list;
} Sandbox;

Sandbox SandboxInit();
void SandboxSubmitData(Sandbox* sandbox);

void SandboxUpdate(Sandbox* sandbox, float32 time_delta);
void SandboxDraw(Sandbox* sandbox);
void SandboxProcessInput(Sandbox* sandbox, uint32 input);
