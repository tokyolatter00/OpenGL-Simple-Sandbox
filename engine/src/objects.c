
#include <GLEW/glew.h>
#include "../objects.h"
#include "../globals.h"
#include "../texture.h"

Quad QuadInit(QuadType type, Colour colour, Location location, Size size, Velocity velocity) {

	// Create Quad

	Quad quad;
	
	quad.colour = colour;
	quad.location = location;
	quad.size = size;
	quad.velocity = velocity;
	quad.tex_id = TEXTURE_NONE;
	quad.type = type;

	quad.velocity.xspeed = 200.0f;
	quad.velocity.yspeed = 200.0f;

	// Update Data

	QuadUpdateData(&quad);

	return quad;
}

void QuadUpdateData(Quad* quad) {

	// Recalculate Bounds

	quad->location.top = quad->location.y + (quad->size.height / 2);
	quad->location.bottom = quad->location.y - (quad->size.height / 2);
	quad->location.left = quad->location.x - (quad->size.height / 2);
	quad->location.right = quad->location.x + (quad->size.height / 2);

	// Reset Vertices

	quad->vertices[0] = (Vertex)
	{
		.position = { quad->location.left, quad->location.top, 0.0f },
		.colour = quad->colour,
		.tex_coords = { 0.0f, 1.0f },
		.tex_id = quad->tex_id
	};

	quad->vertices[1] = (Vertex)
	{
		.position = { quad->location.right, quad->location.top, 0.0f },
		.colour = quad->colour,
		.tex_coords = { 1.0f, 1.0f },
		.tex_id = quad->tex_id
	};

	quad->vertices[2] = (Vertex)
	{
		.position = { quad->location.right, quad->location.bottom, 0.0f },
		.colour = quad->colour,
		.tex_coords = { 1.0f, 0.0f },
		.tex_id = quad->tex_id
	};

	quad->vertices[3] = (Vertex)
	{
		.position = { quad->location.left, quad->location.bottom, 0.0f },
		.colour = quad->colour,
		.tex_coords = { 0.0f, 0.0f },
		.tex_id = quad->tex_id
	};

}
