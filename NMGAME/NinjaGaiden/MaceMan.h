#include "MovingObject.h"
#include "CEnum.h"

class MaceMan : public MovingObject
{
public:
	bool hasAttack;
	bool active;

	MaceMan(void);
	MaceMan(float x, float y);
	void Update(int dt);

	void SetActive(float x, float y);

	~MaceMan(void);
};

