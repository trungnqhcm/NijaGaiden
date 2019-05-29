#include "ListGameObject.h"

ListGameObject::ListGameObject(void)
{
}



ListGameObject::ListGameObject(string fileName)
{
	ifstream map(fileName);

	_staticObject = new list<GameObject*>();
	_MovingObject = new list<GameObject*>();

	if (map.is_open())
	{
		float posX, posY; int width, height, value;
		int count;
		map >> count;
		int id;
		for (int i = 0; i < count; i++)
		{
			//so thu tu dong - idObj -...
			map >> id >> value >> posX >> posY >> width >> height;

			switch (value)
			{
			case 700:
				_staticObject->push_back(new Ground(posX, posY, width, height, EnumID::Ground1_ID));
				break;
			case 702:
				_staticObject->push_back(new Ground(posX, posY, width, height, EnumID::Ground2_ID));
				break;
			case 612:
				_staticObject->push_back(new Ground(posX, posY, width, height, EnumID::Stair_ID));
				break;
			case 211:
				_MovingObject->push_back(new SwordMan(posX, posY));
				break;
			case 212:
				_MovingObject->push_back(new Leopard(posX, posY));
				break;
			case 213:
				_MovingObject->push_back(new MaceMan(posX, posY));
				break;
			case 214:
				_MovingObject->push_back(new GunMan(posX, posY));
				break;
			case 26:
				G_MinSize = posX;
				break;
			case 27:
				G_MaxSize = posX;
				break;
			default:
				break;
			}
		}
	}
	Initialize();
}


void ListGameObject::Draw(CCamera *camera)
{
	for (list<GameObject*>::iterator i = _staticObject->begin(); i != _staticObject->end(); i++)
	{
		GameObject* obj = (*i);
		if (obj->active)
		{
			obj->Draw(camera);
		}
	}
	for (list<GameObject*>::iterator i = _MovingObject->begin(); i != _MovingObject->end(); i++)
	{
		GameObject* obj = (*i);
		if (obj->active)
		{
			obj->Draw(camera);
		}
	}
}

void ListGameObject::Update(int deltaTime)
{
	list<GameObject*>::iterator it = _staticObject->begin();
	while (it != _staticObject->end())
	{
		(*it)->Update(deltaTime);
		++it;
	}
	it = _MovingObject->begin();

}

void ListGameObject::Update(int deltaTime, D3DXVECTOR2* ryuPos)
{
	list<GameObject*>::iterator it = _MovingObject->begin();

}

void ListGameObject::Collision(int dt)
{
	for (list<GameObject*>::reverse_iterator i = _staticObject->rbegin(); i != _staticObject->rend(); i++)
	{
		if ((*i)->canMove)
		{
			(*i)->Collision((*_staticObject), dt);
		}
	}
	for (list<GameObject*>::iterator i = _MovingObject->begin(); i != _MovingObject->end(); i++)
	{
		if ((*i)->active)
		{
			(*i)->Collision((*_staticObject), dt);
		}
	}
}

void ListGameObject::Initialize()
{
}

void ListGameObject::RemoveAllObject()
{
	_MovingObject->clear();
}

ListGameObject::~ListGameObject(void)
{
}
