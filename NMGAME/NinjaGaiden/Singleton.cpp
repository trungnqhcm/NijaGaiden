#include "Singleton.h"
#include <string>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <malloc.h>

using namespace std;

Singleton* Singleton::single = NULL;

Singleton* Singleton::getInstance()
{
	if (single == NULL)
		single = new Singleton();
	return single;
}

Singleton::Singleton()
{
	ryu = new CTexture("Resources/ryuIdle.png", 1, 1, 1);
	ryuRun = new CTexture("Resources/ryuRun.png", 3, 1, 3);
	ryuJump1 = new CTexture("Resources/ryuJump.png", 4, 1, 4);
	ryuClimb = new CTexture("Resources/ryuClimb.png", 2, 1, 2);
	ryuAttack = new CTexture("Resources/ryuAttack.png", 3, 1, 3);
	ryuSit = new CTexture("Resources/ryuSit.png", 1, 1, 1);
	ryuSitAttack = new CTexture("Resources/ryuSitAttack.png", 3, 1, 3);

	swordMan = new CTexture("Resources/Enemy/Sword_Man.png", 3, 1, 3);
	gunMan = new CTexture("Resources/Enemy/Gun_Man.png", 2, 1, 2);
	maceMan = new CTexture("Resources/Enemy/Mace_Man.png", 3, 1, 3);
	leopard = new CTexture("Resources/Enemy/Leopard.png", 2, 1, 2);
	eagle = new CTexture("Resources/Enemy/Eagle.png", 2, 1, 2);
	butterfly = new CTexture("Resources/Enemy/Butterfly.png", 2, 1, 2);

	boss = new CTexture("Resources/Enemy/Final_Boss.png", 2, 1, 2);
}

CTexture* Singleton::getTexture(EnumID id)
{
	switch (id)
	{
		case EnumID::Ryu_ID:
			return ryu;
		case EnumID::RyuRun_ID:
			return ryuRun;
		case EnumID::RyuJump1_ID:
			return ryuJump1;
		case EnumID::RyuClimb_ID:
			return ryuClimb;
		case EnumID::RyuAttack_ID:
			return ryuAttack;
		case EnumID::RyuSit_ID:
			return ryuSit;
		case EnumID::RyuSitAttack_ID:
			return ryuSitAttack;

		case EnumID::GameScore_ID:
			return gameScore;
		case EnumID::swordMan_ID:
			return swordMan;
		case EnumID::gunMan_ID:
			return gunMan;
		case EnumID::maceMan_ID:
			return maceMan;
		case EnumID::leopard_ID:
			return leopard;
		case EnumID::eagle_ID:
			return eagle;
		case EnumID::butterfly_ID:
			return butterfly;
		case EnumID::Boss_ID:
			return boss;
	}
}