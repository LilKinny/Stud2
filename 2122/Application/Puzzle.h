#ifndef Puzzle_H
#define Puzzle_H

#include "PuzzleEntity.h"

class Puzzle : public PuzzleEntity
{
public:
	void Render();
	void Update();
	void Init();
	bool Wincheck();
	void Resetgame();

	bool ispickupsomthing;

	PuzzleEntity* Paper[10]{};

	PuzzleEntity* Player;



	float playeractualpox;
	float playeractualpoy;
private:
	
};

#endif