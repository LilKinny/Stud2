#ifndef EQUIPMENTMANAGER_H
#define EQUIPMENTMANAGER_H
#include "Equipment.h"	

class EquipmentManager
{
public:
	int MinigameBuffs;
	int LuckyCatUpgrade;
	int MoneyPlantUpgrade;
	int PrestigeLvl;
	float Money;
	Equipment* EquipArray[18];
	EquipmentManager();
	~EquipmentManager();
	int UpgradePrestige(bool Upgrade);
	int CalculateTotalIncome(void);
};


#endif
