#include "MaceMan.h"

#define SPEED_X 0.1f
#define SPEED_Y 0.1f
#define MAX_HEIGHT 150.0f

MaceMan::MaceMan(void) : MovingObject()
{
}

MaceMan::MaceMan(float x, float y) : MovingObject(x, y, 0, 0, EnumID::maceMan_ID)
{
	type = ObjectType::Enemy_Type;
	active = false;
}

void MaceMan::Update(int dt)
{
	sprite->Update(dt);
	if (sprite == NULL || !active)
		return;

	posX += vX * dt;
	posY += vY * dt;
}

void MaceMan::SetActive(float x, float y)
{

	if (abs(posX - x) <= 300 && !active)
	{
		active = true;
		vX = -SPEED_X;
	}
}

MaceMan::~MaceMan(void)
{
}
