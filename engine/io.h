
#pragma once

#include "types.h"

typedef struct _File {
	char* Data;
	uint64 Size;
} File;

void FileFree(File* file);
File FileRead(char* path);
