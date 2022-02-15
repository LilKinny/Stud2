#include "EquipmentManager.h"

EquipmentManager::EquipmentManager()
{
	MinigameBuffs = 0;
	LuckyCatUpgrade = 0;
	MoneyPlantUpgrade = 0;
	PrestigeLvl = 0;
	Money = 5000;
}

EquipmentManager::~EquipmentManager()
{
}

int EquipmentManager::UpgradePrestige(bool Upgrade)
{
	if (PrestigeLvl == 0)
	{
		if (Money >= 500)
		{
			if (Upgrade == true)
			{
				Money = 0;
				++PrestigeLvl;
				LuckyCatUpgrade = MoneyPlantUpgrade = 0;
			}
			return 1;
		}
	}
	else if(PrestigeLvl == 1) 
	{
		if (Money >= 1500)
		{
			if (Upgrade == true)
			{
				Money = 0;
				++PrestigeLvl;
				LuckyCatUpgrade = MoneyPlantUpgrade = 0;
			}
			return 1;
		}
	}
	else if (PrestigeLvl == 2)
	{
		if (Money >= 4500)
		{
			if (Upgrade == true)
			{
				Money = 0;
				++PrestigeLvl;
				LuckyCatUpgrade = MoneyPlantUpgrade = 0;
			}
			return 1;
		}
	}
	return 0;
}
