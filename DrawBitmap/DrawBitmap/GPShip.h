#pragma once

#include <stdlib.h>
#include "GPSprites.h"

class GPShip: public GPSprites
{
public:
	GPShip();
	virtual ~GPShip();

	// spawn a spaceship on the left side in the middle of the y-axis
	void spawn();

	// move up.
	void moveUp();

	// move down.
	void moveDown();

	// move left.
	void moveLeft();

	// move right.
	void moveRight();

private:
};