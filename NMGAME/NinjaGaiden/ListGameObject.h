#include <list>
#include <map>
#include "Ryu.h"
#include "SwordMan.h"
#include "Leopard.h"
#include "MaceMan.h"
#include "GunMan.h"

#include "Ground.h"
#include "Singleton.h"
#include "Camera.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include <time.h>
#include <random>

//using namespace std;

class ListGameObject
{
protected:
	D3DXVECTOR2 posDoor;
public:
	void Initialize();

	list<GameObject*> *_staticObject;
	list<GameObject*> *_MovingObject;

	ListGameObject(void);
	~ListGameObject(void);

	ListGameObject(string);
	void Draw(CCamera *camera);
	void Update(int deltaTime);
	void Update(int deltaTime, D3DXVECTOR2* ryuPos);
	void Collision(int dt);
	void RemoveAllObject();
};