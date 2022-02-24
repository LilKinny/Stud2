#include "Puzzle.h"
#include <ctime>
#include <cstdlib>

//created by luke
using namespace std;

void Puzzle::Render()
{

}

void Puzzle::Update()
{
}

void Puzzle::Init()
{
	srand(time(0));  // Initialize random number generator.


	// Init paper
	for (int i = 0; i < 10; i++)
	{
		Paper[i] = new PuzzleEntity();
	}

	//Init player
	Player = new PuzzleEntity();
	// Init Player Border
	Border = new PuzzleEntity();
	

	//Randomize paper Positions and check for stacking 
	for (int i = 0; i < 10; i++)
	{
		/*Paper[i] = new Puzzle();*/
		Paper[i]->position.x = (rand() % 10) + 1;
		Paper[i]->position.y = (rand() % 10) + 1;

		for (int e = 0; e < 10; e++)
		{
			while (Paper[i]->position.x == Paper[e]->position.x && Paper[i]->position.y == Paper[e]->position.y)
			{
				if (Paper[i] == Paper[e])
				{
					break;
				}
				else
				{
					Paper[i]->position.x = (rand() % 10) + 1;
					Paper[i]->position.y = (rand() % 10) + 1;
				}
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		Paper[i]->actlposition.x = (18 + (Paper[i]->position.x * 4));
		Paper[i]->actlposition.y = (7 + (Paper[i]->position.y * 4));

		Paper[i]->prevposition.x = Paper[i]->actlposition.x;
		Paper[i]->prevposition.y = Paper[i]->actlposition.y;
	}

	//Randomize player position and check for stacking with papers
	Player->position.x = (rand() % 10) + 1;
	Player->position.y = (rand() % 10) + 1;

	for (int e = 0; e < 10; e++)
	{
		while (Player->position.x == Paper[e]->position.x && Player->position.y == Paper[e]->position.y)
		{
			Player->position.x = (rand() % 10) + 1;
			Player->position.y = (rand() % 10) + 1;
		}
	}


	//Create Offset for the ui and buttons
	playeractualpox = (18 + (Player->position.x * 4));
	playeractualpoy = (7 + (Player->position.y * 4));

	Player->prevposition.x = playeractualpox;
	Player->prevposition.y = playeractualpoy;

	Border->position.x = playeractualpox;
	Border->position.y = playeractualpoy;

	//set pickup variable 
	ispickupsomthing = false;
	//set pickup variable for papers 
	for (int i = 0; i < 10; i++)
	{
		Paper[i]->pickupstatus = false;
	}
}

bool Puzzle::Wincheck()
{
	//Win condition Check
	int count = 0;
	//Check all papers in the same position
	for (int i = 0; i < 10; i++)
	{
		if (Paper[0]->prevposition.x == Paper[i]->prevposition.x && Paper[0]->prevposition.y == Paper[i]->prevposition.y)
		{
			count += 1;
		}
	}
	//Return result
	if (count == 10)
	{
		return true;
	}
}

void Puzzle::Resetgame()
{
	//Reset the game for next playthrough 
	srand(time(0));
	//randomize paper position
	for (int i = 0; i < 10; i++)
	{
		Paper[i]->position.x = (rand() % 10) + 1;
		Paper[i]->position.y = (rand() % 10) + 1;

		for (int e = 0; e < 10; e++)
		{
			while (Paper[i]->position.x == Paper[e]->position.x && Paper[i]->position.y == Paper[e]->position.y)
			{
				if (Paper[i] == Paper[e])
				{
					break;
				}
				else
				{
					Paper[i]->position.x = (rand() % 10) + 1;
					Paper[i]->position.y = (rand() % 10) + 1;
				}
			}
		}
	}
	//set paper position
	for (int i = 0; i < 10; i++)
	{
		Paper[i]->actlposition.x = (18 + (Paper[i]->position.x * 4));
		Paper[i]->actlposition.y = (7 + (Paper[i]->position.y * 4));

		Paper[i]->prevposition.x = Paper[i]->actlposition.x;
		Paper[i]->prevposition.y = Paper[i]->actlposition.y;
	}

	//reset player position
	Player->position.x = (rand() % 10) + 1;
	Player->position.y = (rand() % 10) + 1;
	//check for no stacking
	for (int e = 0; e < 10; e++)
	{
		while (Player->position.x == Paper[e]->position.x && Player->position.y == Paper[e]->position.y)
		{
			Player->position.x = (rand() % 10) + 1;
			Player->position.y = (rand() % 10) + 1;
		}
	}


	//set position with offset
	playeractualpox = (18 + (Player->position.x * 4));
	playeractualpoy = (7 + (Player->position.y * 4));

	Player->prevposition.x = playeractualpox;
	Player->prevposition.y = playeractualpoy;

	Border->position.x = playeractualpox;
	Border->position.y = playeractualpoy;

	//reset status
	ispickupsomthing = false;

	for (int i = 0; i < 10; i++)
	{
		Paper[i]->pickupstatus = false;
	}

}
