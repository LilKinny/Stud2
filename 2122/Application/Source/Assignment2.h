#ifndef SCENE_11_H
#define SCENE_11_H
#include "MatrixStack.h"
#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "Light.h"
#include "Material.h"
class Assignment2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CUBE_PURPLE,
		GEO_CUBE_GREEN,
		GEO_CUBE_BROWN,
		GEO_CUBE_WHITE,
		GEO_CUBE_GREY,
		GEO_SPHERE_JOINT,
		GEO_CIRCLE,
		GEO_SPHERE,
		GEO_LIGHTBALL,
		GEO_SPHERE_PEARL,
		GEO_SPHERE_PEARL_INNER,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_BLEND,
		GEO_NYP,
		GEO_CHAIR,
		GEO_SHOE,
		GEO_DOORMAN,
		GEO_DART,
		GEO_COTTAGE,
		GEO_TEXT,
		GEO_FENCE,
		GEO_MODEL8,
		GEO_GRASS,
		GEO_GRASS_V,
		GEO_TREE,
		GEO_HOUSE1,
		GEO_LESHYHOUSE,
		GEO_HOUSE3,
		GEO_MOUNTAIN,
		GEO_MOUNTAIN_2,
		GEO_MOUNTAIN_3,
		GEO_CAMPFIRELOGS,
		GEO_WATERLINE,
		GEO_MONKE,
		GEO_PROSPECTOR,
		GEO_ANGLER,
		GEO_TRAPPER,
		GEO_GOLD,
		GEO_LANTERN,

		GEO_MINER,
		GEO_ROCK_FLAT,
		GEO_ROCK_MINE,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT1_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};
public:
	Assignment2();
	~Assignment2();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	MS modelStack, viewStack, projectionStack;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Light light[2];
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderSkybox();
	float rotateAngle;
	float rotateAngleF;
	float rotateAngleSF;
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderText(Mesh* mesh, std::string text, Color color);
	Camera3 camera;
};

#endif