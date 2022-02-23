#pragma once
#include <Vector3.h>
#include <ctime>
#include <cstdlib>

// created by luke
class donotcarepackage
{
public:
	donotcarepackage();
	~donotcarepackage();

	void reset(int xstart, int xend, int zstart, int zend);

	bool active;
	bool notitext;
	bool pickuptext;
	bool wintext;
	Vector3 position;

	float wintexttimer;
private:
	
};

