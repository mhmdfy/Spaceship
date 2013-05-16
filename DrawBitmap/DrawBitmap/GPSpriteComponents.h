#pragma once


#include <math.h>
#include <d3d9.h>
#include <d3dx9.h>

class GPSpriteComponents
{
public:
	GPSpriteComponents();
	virtual ~GPSpriteComponents();

	// set methods for the components.
	void setX(float x);
	void setY(float y);
	void setXVelocity(float xVelocity);
	void setYVelocity(float yVelocity);
	void setWidth(int width);
	void setHeight(int height);

	// get methods for the components.
	float getX();
	float getY();
	float getXVelocity();
	float getYVelocity();
	int getWidth();
	int getHeight();

	// some physics
	void move();
	float getDistance(GPSpriteComponents other);

private:
	// x, y: represent the location.
	float m_x, m_y; 

	// width, height: represent the image boundery.
	int m_width, m_height; 

	// xVelocity, yVelocity: represent the directional velocity.
	float m_xVelocity, m_yVelocity;
};