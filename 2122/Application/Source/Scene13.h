#ifndef SCENE_11_H
#define SCENE_11_H
#include "MatrixStack.h"
#include "Scene.h"
#include "Camera2.h"
#include "Mesh.h"
#include "Light.h"
#include "Material.h"
class Scene13 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_TITLE,
		GEO_TITLEBUTTONS,
		GEO_FADE_TO_BLACK,
		GEO_GRASS,
		GEO_GRASS_V,
		GEO_CUBE,
		GEO_Tree,
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
		GEO_BUILDING,
		GEO_Lift,
		GEO_LVL2,
		GEO_LVL3,
		GEO_Laptop,
		GEO_Phone1,
		GEO_Table,
		GEO_Body,
		GEO_Head,
		GEO_Arms,
		GEO_TAXI,
		GEO_TRUCK,
		GEO_GRASS3D,
		GEO_POLICE,
		GEO_ROAD,
		GEO_LBUILDING1,
		GEO_STREETLIGHT,
		GEO_LBUILDING2,
		GEO_LBUILDING3,
		GEO_SKYSCRAPER1,

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

		U_LIGHT1_POSITION,
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

		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		U_LIGHT3_POSITION,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_TYPE,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,
		U_LIGHT4_POSITION,
		U_LIGHT4_COLOR,
		U_LIGHT4_POWER,
		U_LIGHT4_KC,
		U_LIGHT4_KL,
		U_LIGHT4_KQ,
		U_LIGHT4_TYPE,
		U_LIGHT4_SPOTDIRECTION,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT4_COSINNER,
		U_LIGHT4_EXPONENT,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};
public:
	Scene13();
	~Scene13();
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
	Light light[5];
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderSkybox();
	float rotateAngle;
	float rotateAngleF;

	int scalevall[50];
	int scalevalgrasss[50];

	float rotateAngleSF;
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	Camera2 camera;
};

#endif