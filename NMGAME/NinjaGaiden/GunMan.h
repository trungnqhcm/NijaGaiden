
#include "MovingObject.h"
#include "CEnum.h"

class GunMan : public MovingObject
{
public:
	bool hasAttack;
	bool active;

	GunMan(void);
	GunMan(float x, float y);
	void Update(int dt);

	void SetActive(float x, float y);

	~GunMan(void);
};

