#include "MovingObject.h"
#include "CEnum.h"

class Leopard : public MovingObject
{
public:
	bool hasAttack;
	bool active;

	Leopard(void);
	Leopard(float x, float y);
	void Update(int dt);

	void SetActive(float x, float y);

	~Leopard(void);
};

