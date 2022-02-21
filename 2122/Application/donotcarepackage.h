#pragma once
#include <Vector3.h>
#include <ctime>
#include <cstdlib>


class donotcarepackage
{
public:
	donotcarepackage();
	~donotcarepackage();

	void reset(int xstart, int xend, int zstart, int zend);

	bool active;
	bool notitext;
	bool pickuptext;
	Vector3 position;
private:
	
};

