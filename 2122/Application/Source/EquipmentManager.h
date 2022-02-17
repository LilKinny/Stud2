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
	float TotalIncomePerSecond;
	float Money;
	float BasePrice;
	Equipment* EquipArray[18];
	EquipmentManager();
	~EquipmentManager();
	int UpgradePrestige(bool Upgrade);
	void CalculateTotalIncome(void);
	float CalculateIncome(int WorkStation, int CompOrPhone);
	void UpdateMoney(float dt);
	std::string ConvertMoneyToSuitableAmounts(float Amount);
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
