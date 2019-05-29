#include "Leopard.h"

#define SPEED_X 0.3f
#define SPEED_Y 0.3f
#define MAX_HEIGHT 150.0f

Leopard::Leopard(void) : MovingObject()
{
}

Leopard::Leopard(float x, float y) : MovingObject(x, y, 0, 0, EnumID::leopard_ID)
{
	type = ObjectType::Enemy_Type;
	active = false;
}

void Leopard::Update(int dt)
{
	sprite->Update(dt);
	if (sprite == NULL || !active)
		return;

	posX += vX * dt;
	posY += vY * dt;
}

void Leopard::SetActive(float x, float y)
{

	if (abs(posX - x) <= 300 && !active)
	{
		active = true;
		vX = -SPEED_X;
	}
}

Leopard::~Leopard(void)
{
}
