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

std::string EquipmentManager::ConvertMoneyToSuitableAmounts(void) //Return Edited String
{
	float Temp = Money;
	if (Money >= 1000000)
	{
		Temp = Temp * 0.000001;
	}
	else if (Money >= 1000)
	{
		Temp = Temp * 0.001;
	}
	std::string Temporary = std::to_string(Temp);
	int Stoppos = -1;
	for (unsigned int i = 0; i < Temporary.length(); ++i)
	{
		if (Temporary[i] == '.')
		{
			Stoppos = i;
		}
	}
	Temporary += "0000";
	if (Stoppos > 0)
	{
		Temporary = Temporary.substr(0, Stoppos + 3);
	}
	if (Money >= 1000000)
	{
		Temporary += 'mil';
	}
	else if (Money >= 1000)
	{
		Temporary += 'k';
	}
	return Temporary;
}
