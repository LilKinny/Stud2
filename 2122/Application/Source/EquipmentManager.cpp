#include "EquipmentManager.h"
#include <iostream>

EquipmentManager::EquipmentManager()
{
	MinigameBuffs = 0;
	LuckyCatUpgrade = 0;
	MoneyPlantUpgrade = 0;
	PrestigeLvl = 0;
	Money = -12400;
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
				++PrestigeLvl;
				LuckyCatUpgrade = MoneyPlantUpgrade = 0;
				DeleteEquipArray();
				InitEquipArray();
				CalculateTotalIncome();
				//Money = 0;
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
				++PrestigeLvl;
				LuckyCatUpgrade = MoneyPlantUpgrade = 0;
				DeleteEquipArray();
				InitEquipArray();
				CalculateTotalIncome();
				//Money = 0;
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
				++PrestigeLvl;
				LuckyCatUpgrade = MoneyPlantUpgrade = 0;
				DeleteEquipArray();
				InitEquipArray(); 
				CalculateTotalIncome();
				//Money = 0;
			}
			return 1;
		}
	}
	return 0;
}

void EquipmentManager::CalculateTotalIncome(void)
{
	float TotalIncome = 0;
	float TempIncome;
	for (int i = 0; i < (PrestigeLvl + 1) * 6; ++i)
	{
		if (EquipArray[i] != nullptr)
		{
			TempIncome = 0;
			EquipArray[i]->CalculateIncomePerSecond();
			TempIncome += EquipArray[i]->IncomePerSecond;
			if (MoneyPlantUpgrade == 1)
			{
				TempIncome += 2;
			}
			if (LuckyCatUpgrade == 1)
			{
				TempIncome *= 2;
			}
			TotalIncome += TempIncome;
		}
	}
	if (MinigameBuffs > 0)
	{
		TotalIncome += TotalIncome * (MinigameBuffs * 0.01);
	}
	if (PrestigeLvl == 1)
	{
		TotalIncome *= 1.5;
	}
	else if (PrestigeLvl == 2)
	{
		TotalIncome *= 1.75;
	}
	else if (PrestigeLvl == 3)
	{
		TotalIncome *= 2;
	}
	TotalIncomePerSecond = TotalIncome;
}

float EquipmentManager::CalculateIncome(int WorkStation, int CompOrPhone)
{
	float TempIncome = 0;;
	if (EquipArray[WorkStation] != nullptr)
	{
		TempIncome = 0;
		TempIncome += EquipArray[WorkStation]->CalculateIncomePerSecond(CompOrPhone);
		if (MoneyPlantUpgrade == 1)
		{
			TempIncome += 2;
		}
		if (LuckyCatUpgrade == 1)
		{
			TempIncome *= 2;
		}
		if (MinigameBuffs > 0)
		{
			TempIncome += TempIncome * (MinigameBuffs * 0.01);
		}
		if (PrestigeLvl == 1)
		{
			TempIncome *= 1.5;
		}
		else if (PrestigeLvl == 2)
		{
			TempIncome *= 1.75;
		}
		else if (PrestigeLvl == 3)
		{
			TempIncome *= 2;
		}
	}
	
	return TempIncome;
}

void EquipmentManager::UpdateMoney(float dt)
{
	if (TotalIncomePerSecond != 0)
	{
		Money += TotalIncomePerSecond * dt;
	}
}

std::string EquipmentManager::ConvertMoneyToSuitableAmounts(float Amount) //Return Edited String
{
	float Temp = Amount;
	if (Amount >= 1000000)
	{
		Temp = Temp * 0.000001;
	}
	else if (Amount >= 1000)  
	{
		Temp = Temp * 0.001;
	}
	std::string Temporary = std::to_string(Temp);
	int Stoppos = 0;
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
	if (Amount >= 1000000)
	{
		Temporary += 'm';
	}
	else if (Amount >= 1000)
	{
		Temporary += 'k';
	}
	return Temporary;
}

int EquipmentManager::UnlockPhone(bool unlock)
{
	float IncrementPrice = 50;
	//Checks if got space for Phone
	int Temp = 1;
	if (PrestigeLvl == 3)
	{
		Temp = 0;
	}
	for(int i = 0; i < (PrestigeLvl+Temp)*6;++i)
	{
		//Check if Equip Array got empty "Work station"
		if (EquipArray[i] == nullptr && unlock == true)
		{
			EquipArray[i] = new Equipment;
		}
		//if Phonelvl is 0 which means not unlocked
		if(EquipArray[i] == nullptr || EquipArray[i]->PhoneLvl == 0)
		{
			//Calculate Increment 
			IncrementPrice = IncrementPrice + IncrementPrice * NumOfPhones() * 0.2;
			//If got money show can unlock
			if (Money >= IncrementPrice)
			{
				//if unlock is true , unlock the phone
				if (unlock == true)
				{
					Money -= IncrementPrice;
					EquipArray[i]->PhoneLvl = 1;
				}
				CalculateTotalIncome();
				return 1;
			}
			i = (PrestigeLvl+1) * 6;
		}
	}
	return 0;
}

int EquipmentManager::UnlockComputer(bool unlock)
{
	float IncrementPrice = 50;
	//Checks if got space for Phone
	int Temp = 1;
	if (PrestigeLvl == 3)
	{
		Temp = 0;
	}
	for (int i = 0; i < (PrestigeLvl + Temp) * 6; ++i)
	{
		//Check if Equip Array got empty "Work station"
		if (EquipArray[i] == nullptr && unlock == true)
		{
			EquipArray[i] = new Equipment;
		}
		//if Computerlvl is 0 which means not unlocked
		if (EquipArray[i] == nullptr || EquipArray[i]->ComputerLvl == 0)
		{
			//Calculate Increment 
			IncrementPrice = IncrementPrice + IncrementPrice * NumOfComputers() * 0.2;
			//If got money show can unlock
			if (Money >= IncrementPrice)
			{
				//if unlock is true , unlock the Computer
				if (unlock == true)
				{
					Money -= 50;
					EquipArray[i]->ComputerLvl = 1;
				}
				CalculateTotalIncome();
				return 1;
			}
			i = (PrestigeLvl + 1) * 6;
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
			CalculateTotalIncome();
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
			CalculateTotalIncome();
			return 1;
		}
	} 
	return 0;
}

int EquipmentManager::UpgradePhone(bool upgrade, int WorkStation)
{
	float IncrementPrice;
	if (EquipArray[WorkStation]->PhoneLvl == 1) //Can Upgrade to 1
	{
		IncrementPrice = 250;
		IncrementPrice = IncrementPrice + IncrementPrice * WorkStation * 0.2;
		if (Money >= IncrementPrice)
		{
			if (upgrade == true)
			{
				Money -= IncrementPrice;
				EquipArray[WorkStation]->PhoneLvl = 2;
			}
			CalculateTotalIncome();
			return 1;
		}
		return 3;
	}
	if (EquipArray[WorkStation]->PhoneLvl == 2) //Can Upgrade to 2
	{
		IncrementPrice = 1250;
		IncrementPrice = IncrementPrice + IncrementPrice * WorkStation * 0.2;
		if (Money >= IncrementPrice)
		{
			if (upgrade == true)
			{
				Money -= IncrementPrice;
				EquipArray[WorkStation]->PhoneLvl = 3;
			}
			CalculateTotalIncome();
			return 1;
		}
		return 3;
	}
	if (EquipArray[WorkStation]->PhoneLvl == 3) //Maxed Cannot upgrade
	{
		return 2;
	}
	if (EquipArray[WorkStation]->PhoneLvl == 0)
	{
		return 0;
	}
}

int EquipmentManager::UpgradeComputer(bool upgrade, int WorkStation)
{
	float IncrementPrice;
	if (EquipArray[WorkStation]->ComputerLvl == 1) //Can Upgrade to 1
	{
		IncrementPrice = 500;
		IncrementPrice = IncrementPrice + IncrementPrice * WorkStation * 0.2;
		if (Money >= IncrementPrice)
		{
			if (upgrade == true)
			{
				Money -= IncrementPrice;
				EquipArray[WorkStation]->ComputerLvl = 2;
			}
			CalculateTotalIncome();
			return 1;
		}
		return 3;
	}
	if (EquipArray[WorkStation]->ComputerLvl == 2) //Can Upgrade to 2
	{
		IncrementPrice = 5000;
		IncrementPrice = IncrementPrice + IncrementPrice * WorkStation * 0.2;
		if (Money >= IncrementPrice)
		{
			if (upgrade == true)
			{
				Money -= IncrementPrice;
				EquipArray[WorkStation]->ComputerLvl = 3;
			}
			CalculateTotalIncome();
			return 1;
		}
		return 3;
	}
	if (EquipArray[WorkStation]->ComputerLvl == 3) //Maxed Cannot upgrade
	{
		return 2;
	}
	if (EquipArray[WorkStation]->ComputerLvl == 0)
	{
		return 0;
	}
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

float EquipmentManager::NumOfPhones(void)
{
	int NumOfPhones = 0;
	for (int i = 0; i < (PrestigeLvl + 1) * 6; ++i)
	{
		if (EquipArray[i] != nullptr && EquipArray[i]->PhoneLvl >= 1)
		{
			++NumOfPhones;
		}
	}
	return NumOfPhones;
}

float EquipmentManager::NumOfComputers(void)
{
	int NumOfComputers = 0;
	for (int i = 0; i < (PrestigeLvl + 1) * 6; ++i)
	{
		if (EquipArray[i] != nullptr && EquipArray[i]->ComputerLvl >= 1)
		{
			++NumOfComputers;
		}
	}
	return NumOfComputers;
}

