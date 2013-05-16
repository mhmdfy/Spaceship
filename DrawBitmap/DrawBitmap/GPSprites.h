#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "GPSpriteComponents.h"


class GPSprites
{
public:
	GPSprites();
	virtual ~GPSprites();

	// Initializes the game.  Returns false if initialization fails.
	virtual bool Init(HINSTANCE& hInstance, const char* cmdLine, int nCmdShow, LPDIRECT3DDEVICE9& d3ddev, int image_width, int image_height);

	// creat a new sprite with given information:
	virtual void create(float x, float y, int width, int height, float xVelocity, float yVelocity, char* image);

	// update the sprite every frame.
	virtual void Update();

	// draw the sprite into the given buffer (with the given device).
	virtual bool draw(LPDIRECT3DSURFACE9& Backbuffer, LPDIRECT3DDEVICE9& d3ddev);

	// check if this sprite collide with the given sprite.
	virtual bool collide(GPSprites other);

	// methods to return private data from this sprite
	virtual GPSpriteComponents& getInfo();

	// helper for collide:
	// returns the sign of the given velocity (1 or -1)
	virtual int getSign(float x);

	// check if the sprite is in bound of the frame.
	virtual bool inBound();
	

protected:
	// the components.
	GPSpriteComponents m_comps;

	// image: the name of the image.
	char* m_image;

	// rectangle for the display portion of the image
	RECT m_display;

	//Direct3D objects
	LPDIRECT3DSURFACE9		m_Surface;
};