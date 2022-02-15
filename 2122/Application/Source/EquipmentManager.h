#ifndef EQUIPMENTMANAGER_H
#define EQUIPMENTMANAGER_H
#include "Equipment.h"	
#include <string>

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
	std::string ConvertMoneyToSuitableAmounts(void);
	int UnlockPhone(bool unlock, float money);
	int UnlockComputer(bool unlock, float money);
	int UpgradePhone(bool upgrade, float money);   //return cost for upgrading phone
	int UpgradeComputer(bool upgrade, float money); //return cost for upgrading computer
	void DeleteEquipArray(void);
	void InitEquipArray(void);
};


#endif
