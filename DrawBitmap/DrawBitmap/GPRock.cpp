
#include "GPRock.h"

GPRock::GPRock()
{
	m_rotateCount = 0;
}

GPRock::~GPRock(){}

void GPRock::spawn()
{
	float speed = -((rand() % 3) + 1);
	float location = (rand() % 768-m_comps.getHeight()) + 1;

	create(1024-m_comps.getWidth(), location, 89, 86, speed, 0, "rocks.bmp");
}

void GPRock::Update()
{
	if(inBound())
	{
		GPSprites::Update();

		if(m_rotateCount == 5)
		{
			m_display.left = (m_display.left + 90);
			m_display.right = (m_display.right + 90);

			if(m_display.right > 360){
				m_display.left = 0;
				m_display.right = 89;
			}

		}
		
		m_rotateCount = (m_rotateCount + 1) % 10;
	}

	else
		spawn();
}