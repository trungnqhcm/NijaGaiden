#include "SwordMan.h"

#define SPEED_X 0.1f
#define SPEED_Y 0.1f
#define MAX_HEIGHT 250.0f

SwordMan::SwordMan(void) : MovingObject()
{
}

SwordMan::SwordMan(float x, float y) : MovingObject(x, y, 0, 0, EnumID::SwordMan_ID)
{
	type = ObjectType::Enemy_Type;
	active = false;
}

void SwordMan::Update(int dt)
{
	sprite->Update(dt);
	if (sprite == NULL || !active)
		return;

	posX += vX * dt;
	posY += vY * dt;
}

void SwordMan::SetActive(float x, float y)
{

	if (abs(posX - x) <= 300 && !active)
	{
		active = true;
		vX = -SPEED_X;
	}
}

SwordMan::~SwordMan(void)
{
}
