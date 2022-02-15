#include "Equipment.h"

Equipment::Equipment()
{
	PhoneLvl = 0;
	ComputerLvl = 0;
	IncomePerSecond = 0;
}

Equipment::~Equipment()
{
}

void Equipment::CalculateIncomePerSecond(void)
{
	IncomePerSecond = 0;
	if (ComputerLvl == 1)
	{
		IncomePerSecond += 1;
	}
	else if (ComputerLvl == 2)
	{
		IncomePerSecond += 5;
	}
	else if (ComputerLvl == 3)
	{
		IncomePerSecond += 10;
	}
	if (PhoneLvl == 1)
	{
		IncomePerSecond += 1;
	}
	else if (PhoneLvl == 2)
	{
		IncomePerSecond += 3;
	}
	else if (PhoneLvl == 3)
	{
		IncomePerSecond += 8;
	}
}

