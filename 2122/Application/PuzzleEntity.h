#pragma once
#include <Vector3.h>

// created by luke
class PuzzleEntity
{
public:
	PuzzleEntity();
	~PuzzleEntity();


	Vector3 position;
	Vector3 actlposition;
	Vector3 prevposition;
	bool pickupstatus;
};

