#include "Puzzle.h"
#include <ctime>
#include <cstdlib>

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

	for (int i = 0; i < 10; i++)
	{
		Paper[i] = new Puzzle();
	}

	

	Player = new PuzzleEntity();

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


	//y offset by 4
	playeractualpox = (18 + (Player->position.x * 4));
	playeractualpoy = (8 + (Player->position.y * 4));

	pickupstatus = false;



}
