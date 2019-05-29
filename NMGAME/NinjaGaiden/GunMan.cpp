#include "GunMan.h"

#define SPEED_X 0.07f
#define SPEED_Y 0.07f
#define MAX_HEIGHT 250.0f

GunMan::GunMan(void) : MovingObject()
{
}

GunMan::GunMan(float x, float y) : MovingObject(x, y, 0, 0, EnumID::gunMan_ID)
{
	type = ObjectType::Enemy_Type;
	active = false;
}

void GunMan::Update(int dt)
{
	sprite->Update(dt);
	if (sprite == NULL || !active)
		return;

	posX += vX * dt;
	posY += vY * dt;
}

void GunMan::SetActive(float x, float y)
{

	if (abs(posX - x) <= 300 && !active)
	{
		active = true;
		vX = -SPEED_X;
	}
}

GunMan::~GunMan(void)
{
}
