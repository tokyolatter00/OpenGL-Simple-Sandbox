
#include "../physics.h"
#include "../globals.h"

void PhysicsUpdateQuad(Quad* quad, float32 time_delta) {

	/*
	Gravity

	- Decrease quad's Y velocity overtime until it hits the ground
	- Reset the quad's Y velocity once it has hit the ground
	*/

	quad->velocity.y -= 0.1f;

	QuadUpdateData(quad);

	/*
		Friction

		- Decrease the quad's X velocity overtime until it hits 0
		- Ensures the quad does infinitely move in a direction when the user presses a key
	*/

	if (quad->velocity.x > 0.0f) {

		if (quad->velocity.x < 1.0f) {
			quad->velocity.x = 0.0f;
		}
		else {
			quad->velocity.x -= 0.1f;
		}

	}
	else if (quad->velocity.x < 0.0f) {

		if (quad->velocity.x > -1.0f) {
			quad->velocity.x = 0.0f;
		}
		else {
			quad->velocity.x += 0.1f;
		}

	}

	QuadUpdateData(quad);

	/*
		Velocity
		
		- Change the quad's X position based on its X velocity
		- Change the quad's Y position based on its Y velocity
	*/
	
	quad->location.x += (quad->velocity.x * quad->velocity.xspeed) * time_delta;
	quad->location.y += (quad->velocity.y * quad->velocity.yspeed) * time_delta;

	QuadUpdateData(quad);

	/*
		Wall Collision

		- Ensure the quad does not go through the left wall
		- Ensure the quad does not go through the right wall
		- Ensure the quad does not fall through the floor
		- Ensure the quad does not go about the window
	*/

	if (quad->location.left <= 0.0f) {
		quad->location.x = (quad->size.width / 2);
		quad->velocity.x = 0.0f;
	}

	if (quad->location.right > WINDOW_WIDTH) {
		quad->location.x = WINDOW_WIDTH - (quad->size.width / 2);
		quad->velocity.x = 0.0f;
	}

	if (quad->location.bottom <= 0.0f) {
		quad->location.y = (quad->size.height / 2);
		quad->velocity.y = 0.0f;
	}

	if (quad->location.top > WINDOW_HEIGHT) {
		quad->location.y = WINDOW_HEIGHT - (quad->size.height / 2);
		quad->velocity.y = 0.0f;
	}

	QuadUpdateData(quad);

}
