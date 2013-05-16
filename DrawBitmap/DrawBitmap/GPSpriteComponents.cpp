
#include "GPSpriteComponents.h"

GPSpriteComponents::GPSpriteComponents()
{
	m_x = NULL;
	m_y = NULL;
	m_xVelocity = NULL;
	m_yVelocity = NULL;
	m_width = NULL;
	m_height = NULL;
}

GPSpriteComponents::~GPSpriteComponents(){}
void GPSpriteComponents::setX(float x)
{
	m_x = x;
}
void GPSpriteComponents::setY(float y)
{
	m_y = y;
}
void GPSpriteComponents::setXVelocity(float xVelocity)
{
	m_xVelocity = xVelocity;
}
void GPSpriteComponents::setYVelocity(float yVelocity)
{
	m_yVelocity = yVelocity;
}
void GPSpriteComponents::setWidth(int width)
{
	m_width = width;
}
void GPSpriteComponents::setHeight(int height)
{
	m_height = height;
}

float GPSpriteComponents::getX()
{
	return m_x;
}
float GPSpriteComponents::getY()
{
	return m_y;
}
float GPSpriteComponents::getXVelocity()
{
	return m_xVelocity;
}
float GPSpriteComponents::getYVelocity()
{
	return m_yVelocity;
}
int GPSpriteComponents::getWidth()
{
	return m_width;
}
int GPSpriteComponents::getHeight()
{
	return m_height;
}

void GPSpriteComponents::move()
{
	m_x = m_x + m_xVelocity;
	m_y = m_y + m_yVelocity;
}

float GPSpriteComponents::getDistance(GPSpriteComponents other)
{
	float x1 = getX() + (getWidth()/2);
	float y1 = getY() + (getHeight()/2);
	float x2 = other.getX() + (other.getWidth()/2);
	float y2 = other.getY() + (other.getHeight()/2);

	return sqrt( pow(x1 - x2, 2) + pow(y1 - y2, 2) );
}