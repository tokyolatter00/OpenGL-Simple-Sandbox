
#include <GLEW/glew.h>
#include "../renderer.h"

void RendererClear() {
	glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void RendererDraw(uint32 vao, uint32 vbo, uint32 ibo, uint32 count) {

	// Bind

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	// Draw

	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);

}
