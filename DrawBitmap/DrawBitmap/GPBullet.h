#pragma once

#include <stdlib.h>
#include "GPSprites.h"

class GPBullet: public GPSprites
{
public:
	GPBullet();
	virtual ~GPBullet();

	// spawn from the given location
	void spawn(float x, float y);
};