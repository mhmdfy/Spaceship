
#include "GPBullet.h"

GPBullet::GPBullet(){}

GPBullet::~GPBullet(){}

void GPBullet::spawn(float x, float y)
{
	create(x, y, 25, 6, 4, 0, "lazor.bmp");
}