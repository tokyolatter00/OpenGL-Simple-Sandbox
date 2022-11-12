
#pragma once

#include "types.h"
#include "list.h"

#define TEXTURE_NONE					-1

typedef struct _TextureList {
	uint32 count;
	List* textures;
} TextureList;

TextureList TextureListInit();
void TextureListDelete(TextureList* tex_list);
uint32 TextureListAdd(TextureList* tex_list, char* path, bool8 flip_image);
