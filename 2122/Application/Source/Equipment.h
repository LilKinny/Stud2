#ifndef EQUIPMENT_H
#define EQUIPMENT_H


class Equipment 
{
public:
	int IncomePerSecond;
	int UnlockPrice;
	int PhoneLvl;
	int ComputerLvl;
	Equipment();
	~Equipment();
	void CalculateIncomePerSecond(void);
	int UpgradePhone(void);   //return cost for upgrading phone
	int UpgradeComputer(void); //return cost for upgrading computer
};

#endif