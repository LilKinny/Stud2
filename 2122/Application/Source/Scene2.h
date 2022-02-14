#ifndef SCENE_2_H
#define SCENE_2_H

#include "Scene.h"
#include "Mesh.h"

class Scene2 : public Scene
{
public:

	Scene2();
	~Scene2();
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
		GEO_TRIANGLE_1,
		GEO_TRIANGLE_2,
		GEO_TRIANGLE_3,
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		NUM_GEOMETRY,
	};
	float rotateAngle;
	float translateX;
	float scaleAll;

private:
	unsigned m_parameters[U_TOTAL];
	unsigned m_vertexArrayID;
	/*unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];*/
	Mesh* meshList[NUM_GEOMETRY];	
	unsigned m_programID;
};	


#endif