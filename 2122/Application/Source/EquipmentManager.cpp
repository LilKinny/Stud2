#include "EquipmentManager.h"

EquipmentManager::EquipmentManager()
{
	MinigameBuffs = 0;
	LuckyCatUpgrade = 0;
	MoneyPlantUpgrade = 0;
	PrestigeLvl = 0;
}

EquipmentManager::~EquipmentManager()
{
}

int EquipmentManager::UpgradePrestige(void)
{
	return PrestigeLvl;
}
