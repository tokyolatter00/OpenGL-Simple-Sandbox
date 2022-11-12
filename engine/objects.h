
#pragma once

#include "types.h"

// Location

typedef struct _Location {
	float32 x;
	float32 y;

	float32 top;
	float32 bottom;
	float32 left;
	float32 right;
} Location;

// Direction

typedef struct _Velocity {
	float32 x;
	float32 y;
	float32 xspeed;
	float32 yspeed;
} Velocity;

// Size

typedef struct _Size {
	float32 width;
	float32 height;
	float32 depth;
} Size;

// Colour

typedef struct _Colour {
	float32 R;
	float32 G;
	float32 B;
} Colour;

// Vertex

typedef struct _Vertex {
	float32 position[3];
	Colour colour;
	float32 tex_coords[2];
	float32 tex_id;
} Vertex;

// Quad

typedef enum _QuadType {
	QUAD_TYPE_PLAYER_CONTROLLED,
	QUAD_TYPE_INTERACTIVE,
	QUAD_TYPE_STATIC
} QuadType;

typedef struct _Quad {
	Vertex vertices[4];

	Colour colour;
	float32 tex_id;

	Location location;
	Size size;
	Velocity velocity;
	QuadType type;
} Quad;

Quad QuadInit(QuadType type, Colour colour, Location location, Size size, Velocity velocity);

void QuadUpdateData(Quad* quad);
