#ifndef SCENE_5_H
#define SCENE_5_H
#include "MatrixStack.h"
#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"

class Scene5 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_CIRCLE_BLUE,
		GEO_SPHERE_YELLOW,
		GEO_SPHERE_ORANGE,
		GEO_SPHERE_WHITE,
		GEO_SPHERE_PURPLE,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};
public:
	Scene5();
	~Scene5();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];
	MS modelStack, viewStack, projectionStack;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;
	float rotateAngleF;
	float rotateAngleSF;

	Camera camera;
};

#endif