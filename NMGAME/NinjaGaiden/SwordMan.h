#ifndef _SWORDMAN_H_
#define _SWORDMAN_H_

#include "MovingObject.h"
#include "CEnum.h"

class SwordMan : public MovingObject
{
public:
	bool hasAttack;
	bool active;

	SwordMan(void);
	SwordMan(float x, float y);
	void Update(int dt);

	void SetActive(float x, float y);

	~SwordMan(void);
};
#endif
