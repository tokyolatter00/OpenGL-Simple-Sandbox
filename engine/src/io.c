
#include <stdio.h>
#include <stdlib.h>
#include "../io.h"

void FileFree(File* file) {
	free(file->Data);
}

File FileRead(char* path) {

	FILE* fptr = fopen(path, "rb");
	fseek(fptr, 0, SEEK_END);
	long size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	char* data = malloc(size + 1);
	fread(data, size, 1, fptr);
	fclose(fptr);

	data[size] = '\0';

	return (File) { .Data = data, .Size = size };
}
