
#include <stdio.h>
#include <GLEW/glew.h>
#include <STB/stb-image.h>
#include "../texture.h"

TextureList TextureListInit() {
	return (TextureList)
	{
		.count = 0,
		.textures = ListInit(sizeof(uint32), 1)
	};
}

void TextureListDelete(TextureList* tex_listay) {
	glDeleteTextures(tex_listay->count, tex_listay->textures->buffer);
}

uint32 TextureListAdd(TextureList* tex_list, char* path, bool8 flip_image) {

	// Load Image from Disk

	int32 width;
	int32 height;
	int32 bits_per_pixel;

	stbi_set_flip_vertically_on_load(flip_image);

	uint8* pixels = stbi_load(
		path,
		&width,
		&height,
		&bits_per_pixel,
		STBI_rgb_alpha
	);

	if (!pixels) {
		printf("ERROR: Failed to load texture: %s\n", path);
	}

	// Create OpenGL Texture

	uint32 texture;
	uint32 count = tex_list->count++;

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + count);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	ListAppend(tex_list->textures, &texture);

	// Cleanup

	stbi_image_free(pixels);

	return count;

}
