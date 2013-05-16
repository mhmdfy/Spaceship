#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class GPSpritePhysics
{
public:
	GPSpritePhysics();
	virtual ~GPSpritePhysics();

	static bool Collide(Sprite, Sprite);

	static bool Move(Sprite);

	static bool inBound(Sprite, int width, int height);
}