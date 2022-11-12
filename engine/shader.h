
#pragma once

#include "types.h"

typedef struct _Shader {
	uint32 ID;
} ShaderProgram;

ShaderProgram ShaderProgramInit(char* vertex_path, char* fragment_path);
