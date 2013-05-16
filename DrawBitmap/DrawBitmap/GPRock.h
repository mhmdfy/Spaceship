#pragma once

#include <stdlib.h>
#include "GPSprites.h"

class GPRock: public GPSprites
{
public:
	GPRock();
	virtual ~GPRock();

	// spawn a rock from the right corner with random speed and random location (on the y axis)
	void spawn();

	// update the sprite every frame.
	void Update();

private:
	// a counter to determine when to rotate
	int m_rotateCount;
};