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
	Equipment* EquipArray[18];
	EquipmentManager();
	~EquipmentManager();
	int UpgradePrestige(void);
	int CalculateTotalIncome(void);
};


#endif
