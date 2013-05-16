
#include "GPShip.h"

GPShip::GPShip(){}

GPShip::~GPShip(){}

void GPShip::spawn()
{
	create(50, 384, 89, 86, 0, 0, "spaceship.bmp");
}

void GPShip::moveUp()
{
	GPShip temp = *this;

	temp.getInfo().setY(m_comps.getY() - 1);

	if(temp.inBound())
	{
		m_comps.setY(m_comps.getY() - 1);
	}
}

void GPShip::moveDown()
{
	GPShip temp = *this;

	temp.getInfo().setY(m_comps.getY() + 1);

	if(temp.inBound())
	{
		m_comps.setY(m_comps.getY() + 1);
	}
}

void GPShip::moveLeft()
{
	GPShip temp = *this;

	temp.getInfo().setX(m_comps.getX() - 1);

	if(temp.inBound())
	{
		m_comps.setX(m_comps.getX() - 1);
	}
}

void GPShip::moveRight()
{
	GPShip temp = *this;

	temp.getInfo().setX(m_comps.getX() + 1);

	if(temp.inBound())
	{
		m_comps.setX(m_comps.getX() + 1);
	}
}