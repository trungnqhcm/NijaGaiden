﻿#include "Ryu.h"

#define SPEED_X 0.5f
#define SPEED_Y 0.8f
#define MAX_HEIGHT 120.0f
bool isCol = false;
bool isAtk = false;

Ryu::Ryu(void) : MovingObject() {

}

Ryu::Ryu(int _posX, int _posY) : MovingObject(_posX, _posY, 0, -SPEED_Y, EnumID::Ryu_ID) 
{
	_action = Action::Idle;
	_vLast = 0.2f;
	_allowPress = true;
	_lastCollidedGround = nullptr;
	_hasJump = false;
	_hasAttack = false;
	_hasClimb = false;
	_hasSit = false;
	_isFall = false;
	_heightJump = 0.0f;
	ryuLife = 10;
	
	onLand = false;
	ryuRun = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuRun_ID), 0, 2, 18);
	ryuJump = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuJump1_ID), 0, 3, 18);
	ryuClimb = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuClimb_ID), 0, 1, 50);
	ryuAttack = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuAttack_ID), 0, 2, 40);
	ryuSit = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuSit_ID), 1);
	ryuSitAttack = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuSitAttack_ID), 0, 2, 40);
	Initialize();
}

void Ryu::Update(int dt) {
	switch (_action)
	{
		case Action::Run_Left:
		case Action::Run_Right:
			ryuRun->Update(dt);
			break;
		case Action::Jump1:
			ryuJump->Update(dt);
			break;
		case Action::Attack:
			ryuAttack->Update(dt);
			break;
	}
	if (!_hasClimb)
	{
		posX += vX * dt;
	}
	if (!onLand || _hasJump || _hasClimb)
	{
		posY += vY * dt;
	}
	if (_hasJump) {
		ryuJump->Update(dt);
		_heightJump += vY * dt;
		if (_heightJump >= MAX_HEIGHT)
		{
			vY = -SPEED_Y;
		}
	}
	if (_hasClimb && vY != 0)
	{
		ryuClimb->Update(dt);
	}
	if (_hasAttack)
	{	
		if (!_hasSit)
		{
			ryuAttack->Update(dt);
			if (ryuAttack->GetIndex() == 0 && isAtk) {
				_hasAttack = false;
				isAtk = false;
				return;
			}
			if (ryuAttack->GetIndex() == 1) {
				isAtk = true;
			}
			_heightJump += vY * dt;
			int maxHeight;
			if (!_isFall)
				maxHeight = MAX_HEIGHT;
			else
				maxHeight = 300.0f;
			if (_heightJump >= maxHeight)
			{
				vY = -SPEED_Y;
			}
		}
		else
		{
			ryuSitAttack->Update(dt);
			if (ryuSitAttack->GetIndex() == 0 && isAtk) {
				_hasAttack = false;
				isAtk = false;
				return;
			}
			if (ryuSitAttack->GetIndex() == 1) {
				isAtk = true;
			}
			vX = 0;
			vY = -SPEED_Y;
		}
	}
	if (_hasSit && !_hasAttack)
	{
		ryuSit->Update(dt);
		vX = 0;
		vY = -SPEED_Y;
	}

	if (posY < -80)
	{
		if (ryuLife > 0)
		{
			ryuLife--;
			posY = 300;
			_isFall = true;
			onLand = false;
			posX = posX - 100;
			vX = _vLast;
		}
	}
}

Box Ryu::GetBox()
{
	if (_hasSit)
		return Box(posX - ryuSit->_texture->FrameWidth / 2, (posY + ryuSit->_texture->FrameHeight / 2), ryuSit->_texture->FrameWidth, ryuSit->_texture->FrameHeight);
	else if (_hasClimb)
		return Box(posX - ryuClimb->_texture->FrameWidth / 2, (posY + ryuClimb->_texture->FrameHeight / 2), ryuClimb->_texture->FrameWidth, ryuClimb->_texture->FrameHeight);
	if ((vX != 0 || (vY != 0 && _hasJump)) && !_hasClimb)
	{
		if (_hasJump)
			return Box(posX - ryuJump->_texture->FrameWidth / 2, (posY + ryuJump->_texture->FrameHeight / 2), ryuJump->_texture->FrameWidth, ryuJump->_texture->FrameHeight);
		return Box(posX - ryuRun->_texture->FrameWidth / 2, (posY + ryuRun->_texture->FrameHeight / 2), ryuRun->_texture->FrameWidth, ryuRun->_texture->FrameHeight);
	}
	return Box(posX - sprite->_texture->FrameWidth / 2 , (posY + sprite->_texture->FrameHeight / 2), sprite->_texture->FrameWidth, sprite->_texture->FrameHeight);
}

void Ryu::Collision(list<GameObject*> &obj, float dt, bool isDynamic)
{
	int countCollis = 0;
	for (list<GameObject*>::iterator _itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		
		if (other->id == EnumID::swordMan_ID || other->id == EnumID::leopard_ID || other->id == EnumID::maceMan_ID || other->id == EnumID::gunMan_ID)
		{
			other->SetActive(this->posX, this->posY);
		}
		if (!other->active)
		{

		}
		else 
		{
			float moveX;
			float moveY;
			float normalx;
			float normaly;

			Box boxRyu = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(boxRyu, boxOther, moveX, moveY) == true)
			{
				float collisiontime = SweptAABB(boxRyu, boxOther, normalx, normaly, dt);
				ECollisionDirect dir = this->GetCollisionDirect(other);
				switch (other->id)
				{
				case EnumID::Ground1_ID:
				{
					countCollis++;
					if (!_isFall)
					{
						//va cham canh
						if (dir == ECollisionDirect::Colls_Left || dir == ECollisionDirect::Colls_Right)
						{
							vX = 0;
							if (dir == ECollisionDirect::Colls_Right && _action == Action::Run_Right)
							{
								vX = SPEED_X;
							}
							else if (dir == ECollisionDirect::Colls_Left && _action == Action::Run_Left)
							{
								vX = -SPEED_X;
							}
						}
						//va cham tren
					
					}

					//xet cham dat
					if (vY < 0  && dir == ECollisionDirect::Colls_Bot)
					{
						//posY += moveY;
						onLand = true;
						_hasJump = false;
						_isFall = false;
					}
			
					/*if (vX != 0 && moveX != 0)
					{
						posX += moveX;
					}*/
					break;
				}
				case EnumID::Ground2_ID:
				{
					countCollis++;
					if (dir == ECollisionDirect::Colls_Bot && vY < 0 && !_hasClimb)
					{
						onLand = true;
						_hasJump = false;
						_hasClimb = false;
					}
					break;
				}
			
				
				default:
					break;
				}
			}
			else
			{
			}
		}
	}
	if (countCollis == 0 && onLand == true && !isDynamic)
	{
		onLand = false;
	}
}

void Ryu::Draw(CCamera* camera) {
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if ((vX != 0 || (vY != 0 && _hasJump)) && !_hasClimb)
	{
		if (_vLast > 0)
		{
			if (_hasJump)
			{
				ryuJump->Draw(center.x, center.y);
				return;
			}
			ryuRun->Draw(center.x, center.y);
		}
		else {
			if (_hasJump)
			{
				ryuJump->DrawFlipX(center.x, center.y);
				return;
			}
			ryuRun->DrawFlipX(center.x, center.y);
		}
	}
	else if (_hasSit)
	{
		if (_hasAttack)
		{
			if (_vLast > 0)
			{
				ryuSitAttack->Draw(center.x + 23, center.y);
				return;
			}
			else {
				ryuSitAttack->DrawFlipX(center.x - 23, center.y);
				return;
			}
		}
		if (_vLast > 0)
		{
			ryuSit->Draw(center.x, center.y);
		}
		else {
			ryuSit->DrawFlipX(center.x, center.y);
		}
	}
	else
	{
		if (_vLast > 0)
		{
			if (_hasAttack)
			{
				ryuAttack->Draw(center.x + 23, center.y);

				return;
			}
			sprite->Draw(center.x, center.y);
		}
		else {
			if (_hasAttack)
			{
				ryuAttack->DrawFlipX(center.x - 23, center.y);
				return;
			}
			sprite->DrawFlipX(center.x, center.y);
		}
	}
}

void Ryu::TurnLeft()
{
	if (_allowPress)
	{
		vX = -SPEED_X;
		_vLast = vX;
		_action = Action::Run_Left;
		_hasClimb = false;
		_hasSit = false;
		onLand = false;
	}
}

void Ryu::TurnRight() 
{
	if (_allowPress)
	{
		vX = SPEED_X;
		_vLast = vX;
		_action = Action::Run_Right;
		_hasClimb = false;
		_hasSit = false;
		onLand = false;
	}
}

void Ryu::Sit()
{
	if (_allowPress)
	{
		if (!_hasSit)
		{
			_hasSit = true;
			if (!_hasAttack)
				_action = Action::Sit;
			else
				_action = Action::SitAttack;
			onLand = false;
		}
	}
}

void Ryu::Jump()
{
	if (_allowPress)
	{
		if (!_hasJump)
		{
			vX = 0;
			vY = SPEED_Y;
			_heightJump = 0;
			ryuJump->SelectIndex(0);
			_action = Action::Jump1;
			_hasJump = true;
			_hasClimb = false;
			_hasSit = false;
			onLand = false;
		}
	}
}
void Ryu::Attack(bool isUseWeapon)
{
	if (_allowPress)
	{
		if (!_hasAttack)
		{
			if (isUseWeapon)
			{
				useWeapon = true;
			}
			else
			{
				_hasJump = false;
				ryuAttack->SelectIndex(0);
			}
			_action = Action::Attack;
			_hasAttack = true;
		}
	}
}
void Ryu::Initialize()
{
	sprite->SelectIndex(0);
}

void Ryu::Stop()
{
	if (!_hasClimb)
	{
		if (!_hasJump) vX = 0;
		_action = Action::Idle;
	}
	else
	{
		ryuClimb->SelectIndex(0);
		vY = 0;
	}
}

ECollisionDirect Ryu::GetCollisionDirect(GameObject* other)
{
	float x = (this->posX-(this->getWidth()/2)) - (other->posX-(other->getWidth()/2));
	float y = (this->posY+ (this->getHeight() / 2)) - (other->posY+(other->getHeight() / 2));
	if (abs(x) > abs(y)) {
		if (x < 0)
			return ECollisionDirect::Colls_Left;
		else if (x > 0)
			return ECollisionDirect::Colls_Right;
	}
	else
	{
		if (y < 0)
			return ECollisionDirect::Colls_Top;
		else if (y > 0)
			return ECollisionDirect::Colls_Bot;
	}

	return ECollisionDirect::Colls_None;
}

D3DXVECTOR2* Ryu::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}

int Ryu::getWidth()
{
	if (_hasJump)
		return ryuJump->_texture->FrameWidth;
	return sprite->_texture->FrameWidth;
}

int Ryu::getHeight()
{
	if (_hasJump)
		return ryuJump->_texture->FrameWidth;
	return sprite->_texture->FrameHeight;
}

Ryu::~Ryu(void)
{

}