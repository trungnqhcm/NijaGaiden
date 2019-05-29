#ifndef _MovingObject_H_
#define _MovingObject_H_


#include "GameObject.h"
#include "Camera.h"
#include <math.h>
#include <map>

using namespace std;

class MovingObject : public GameObject
{
public:
	//DWORD _localHurtTime;
	//DWORD _deltaHurtTime;
	//bool bActiveHurt;
	//bool IsHurt();
	//bool _bHurt;
	void Initialize();
	MovingObject(void);
	MovingObject(float posX, float posY, float vX, float vY, EnumID id);
	virtual void Update(int dt);
	virtual void Draw(CCamera*);
	//virtual Box GetBox();
	virtual void Collision(list<GameObject*>obj, int dt);
	virtual void SetActive(float x, float y);
	//virtual void ReceiveDamage(int damagePoint);
	~MovingObject(void);
};

#endif