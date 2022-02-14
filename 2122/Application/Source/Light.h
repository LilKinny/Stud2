#pragma once
#include "Vertex.h"

struct Light
{
public:

	//add these after existing parameters
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,

		LIGHT_POINT_2 = 0,
		LIGHT_DIRECTIONAL_2,
		LIGHT_SPOT_2,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	//to do: add a constructor
};
