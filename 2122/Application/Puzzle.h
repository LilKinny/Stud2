#ifndef Puzzle_H
#define Puzzle_H

#include "PuzzleEntity.h"

class Puzzle : public PuzzleEntity
{
public:
	void Render();
	void Update();
	void Init();

	bool pickupstatus;

	PuzzleEntity* Paper[10]{};

	PuzzleEntity* Player;
private:
	
};

#endif