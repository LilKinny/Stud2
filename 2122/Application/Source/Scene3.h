#ifndef SCENE_3_H
#define SCENE_3_H

#include "Scene.h"

class Scene3 : public Scene
{
public:

	Scene3();
	~Scene3();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};

	enum GEOMETRY_TYPE
	{
		GEO_HOUSELIGHT_1,
		GEO_HOUSELIGHT_2,
		GEO_ROOF,
		GEO_FLOOR,
		GEO_TREE_BODY,
		TREE_HEAD,
		TREE_HEAD_DARK,
		SNOWFLAKE,
		MOON,
		NUM_GEOMETRY,
	};
	float rotateAngle;
	float translateX;
	float scaleAll;

private:
	unsigned m_parameters[U_TOTAL];
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
};	


#endif