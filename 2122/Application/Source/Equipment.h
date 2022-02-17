#ifndef EQUIPMENT_H
#define EQUIPMENT_H


class Equipment 
{
public:
	int IncomePerSecond;
	int PhoneLvl;
	int ComputerLvl;
	Equipment();
	~Equipment();
	void CalculateIncomePerSecond(void);
	int CalculateIncomePerSecond(int CompOrPhone);
};

#endif