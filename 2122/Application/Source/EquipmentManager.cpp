#include "EquipmentManager.h"

EquipmentManager::EquipmentManager()
{
	MinigameBuffs = 0;
	LuckyCatUpgrade = 0;
	MoneyPlantUpgrade = 0;
	PrestigeLvl = 0;
	Money = 5000;
	InitEquipArray();
}

EquipmentManager::~EquipmentManager()
{
	DeleteEquipArray();
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
				DeleteEquipArray();
				InitEquipArray();
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
				DeleteEquipArray();
				InitEquipArray();
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
				DeleteEquipArray();
				InitEquipArray();
			}
			return 1;
		}
	}
	return 0;
}

int EquipmentManager::CalculateTotalIncome(void)
{
	int TotalIncome = 0;
	for (int i = 0; i < PrestigeLvl * 6; ++i)
	{
		EquipArray[i]->CalculateIncomePerSecondCalculateIncomePerSecond();
		TotalIncome += EquipArray[i]->IncomePerSecond;
	}
	return TotalIncome
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

int EquipmentManager::UnlockPhone(bool unlock)
{
	//Checks if got space for Phone
	for(int i = 0; i < PrestigeLvl*6;++i)
	{
		//Check if Equip Array got empty "Work station"
		if (EquipArray[i] == nullptr)
		{
			EquipArray[i] = new Equipment;
			i = PrestigeLvl * 6;
		}
		//if Phonelvl is 0 which means not unlocked
		if(EquipArray[i]->PhoneLvl == 0)
		{
			//If got money show can unlock
			if (Money >= 50)
			{
				//if unlock is true , unlock the phone
				if (unlock == true)
				{
					Money -= 50;
					EquipArray[i]->PhoneLvl = 1;
				}
				return 1;
			}
			i = PrestigeLvl * 6;
		}
	}
	return 0;
}

int EquipmentManager::UnlockComputer(bool unlock)
{
	//Checks if got space for Computer
	for (int i = 0; i < PrestigeLvl * 6; ++i)
	{
		//Check if Equip Array got empty "Work station"
		if (EquipArray[i] == nullptr)
		{
			EquipArray[i] = new Equipment;
			i = PrestigeLvl * 6;
		}
		//if Computerlvl is 0 which means not unlocked
		if (EquipArray[i]->ComputerLvl == 0)
		{
			//If got money show can unlock
			if (Money >= 50)
			{
				//if unlock is true , unlock the Computer
				if (unlock == true)
				{
					Money -= 50;
					EquipArray[i]->ComputerLvl = 1;
				}
				return 1;
			}
			i = PrestigeLvl * 6;
		}
	}
	return 0;
}

int EquipmentManager::UnlockLuckyCat(bool unlock)
{
	//Checks if Lucky Cat Unlocked
	if (LuckyCatUpgrade == 0)
	{
		if (Money >= 10000 && PrestigeLvl >= 2)
		{
			if (unlock == true)
			{
				Money -= 10000;
				LuckyCatUpgrade = 1;
			}
			return 1;
		}
	}
	return 0;
}

int EquipmentManager::UnlockMoneyPlant(bool unlock)
{
	//Checks if Money Plant Unlocked
	if (MoneyPlantUpgrade == 0)
	{
		if (Money >= 5000 && PrestigeLvl >= 1)
		{
			if (unlock == true)
			{
				Money -= 5000;
				MoneyPlantUpgrade = 1;
			}
			return 1;
		}
	}
	return 0;
}

int EquipmentManager::UpgradePhone(bool upgrade, int WorkStation)
{
	if (EquipArray[WorkStation]->PhoneLvl == 1) //Can Upgrade to 1
	{
		if (Money >= 250)
		{
			if (upgrade == true)
			{
				Money -= 250;
				EquipArray[WorkStation]->PhoneLvl = 2;
			}
			return 1;
		}
	}
	if (EquipArray[WorkStation]->PhoneLvl == 2) //Can Upgrade to 2
	{
		if (Money >= 1250)
		{
			if (upgrade == true)
			{
				Money -= 1250;
				EquipArray[WorkStation]->PhoneLvl = 3;
			}
			return 1;
		}
	}
	if (EquipArray[WorkStation]->PhoneLvl == 3) //Maxed Cannot upgrade
	{
		return 2;
	}
	return 0;
}

int EquipmentManager::UpgradeComputer(bool upgrade, int WorkStation)
{
	if (EquipArray[WorkStation]->ComputerLvl == 1) //Can Upgrade to 1
	{
		if (Money >= 500)
		{
			if (upgrade == true)
			{
				Money -= 500;
				EquipArray[WorkStation]->ComputerLvl = 2;
			}
			return 1;
		}
	}
	if (EquipArray[WorkStation]->ComputerLvl == 2) //Can Upgrade to 2
	{
		if (Money >= 5000)
		{
			if (upgrade == true)
			{
				Money -= 5000;
				EquipArray[WorkStation]->ComputerLvl = 3;
			}
			return 1;
		}
	}
	if (EquipArray[WorkStation]->ComputerLvl == 3) //Maxed Cannot upgrade
	{
		return 2;
	}
	return 0;
}

void EquipmentManager::DeleteEquipArray(void)
{
	for (int i = 0; i < 18; ++i)
	{
		Equipment* Temp = EquipArray[i];
		delete Temp;
	}
}

void EquipmentManager::InitEquipArray(void)
{
	for (int i = 0; i < 18; ++i)
	{
		EquipArray[i] = nullptr;
	}
}

