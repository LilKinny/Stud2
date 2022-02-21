#include "donotcarepackage.h"

donotcarepackage::donotcarepackage()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	active = false;
	notitext = false;
	pickuptext = false;
}

donotcarepackage::~donotcarepackage()
{
}

void donotcarepackage::reset(int xstart, int xend, int zstart, int zend)
{
	int xrange, zrange;

	if (xstart > xend)
	{
		xrange = xstart - xend;
	}
	else
	{
		xrange = xend - xstart;
	}

	if (zstart > zend)
	{
		zrange = zstart - zend;
	}
	else
	{
		zrange = zend - zstart;
	}



	position.x = (rand() % xrange) + (xstart);
	position.z = (rand() % zrange) + (zstart);




}
