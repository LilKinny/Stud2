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
	int UnlockPhone(bool unlock);
	int UnlockComputer(bool unlock);
	int UnlockLuckyCat(bool unlock);
	int UnlockMoneyPlant(bool unlock);
	int UpgradePhone(bool upgrade, int WorkStation);   
	int UpgradeComputer(bool upgrade, int WorkStation);
	void DeleteEquipArray(void);
	void InitEquipArray(void);
};


#endif
