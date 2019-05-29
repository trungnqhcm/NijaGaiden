#include "MovingObject.h"

MovingObject::MovingObject(void) : GameObject()
{

}

MovingObject::MovingObject(float _posX, float _posY, float _vX, float _vY, EnumID id) : GameObject(_posX, _posY, id)
{
	vX = _vX;
	vY = _vY;
	canMove = true;
	active = true;
	Initialize();
}

void MovingObject::Update(int dt) {
	if (sprite == NULL || !active)
		return;
	posX = vX * dt;
	if (posX <= width / 2 + 2 || posX >= G_MapWidth - (width / 2 - 2))
		vX = -vX;
	posY = vY * dt;
	sprite->Update(dt);
}

void MovingObject::Draw(CCamera* camera)
{
	if (sprite == NULL || !active) {
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX < 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}

void MovingObject::SetActive(float x, float y)
{
	
}

MovingObject::~MovingObject(void)
{
}

void MovingObject::Collision(list<GameObject*> obj, int dt)
{

}

void MovingObject::Initialize()
{

}

