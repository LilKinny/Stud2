#ifndef Splevel1_H
#define Splevel1_H
#include "MatrixStack.h"
#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "Light.h"
#include "Material.h"
#include "EquipmentManager.h"
#include "../donotcarepackage.h"
#include "../Puzzle.h"
#include <windows.h>
class Splevel1 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_TITLE,
		GEO_NAME,
		GEO_TITLEBUTTONS,
		GEO_CUBE,
		GEO_GRASS,
		GEO_GRASS_V,
		GEO_CUBE_PURPLE,
		GEO_CUBE_GREEN,
		GEO_CUBE_BROWN,
		GEO_CUBE_WHITE,
		GEO_PAPER,
		GEO_EMPTYBOX,
		GEO_DOORS,
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
		GEO_TEXT,
		GEO_BUILDING,
		GEO_LBUILDING1,
		GEO_LBUILDING2,
		GEO_LBUILDING3,
		GEO_SBUILDING1,
		GEO_SKYSCRAPER1,
		GEO_LVL2,
		GEO_LVL3,
		GEO_LAPTOP_UI,
		GEO_TopUI,
		GEO_BotUI,
		GEO_CASH,
		GEO_MONEYPLANT,
		GEO_MONEYCAT,
		GEO_SideUIBig,
		GEO_SideUISmall,
		GEO_MaxPrestige,
		GEO_GreenUpgrade,
		GEO_GrayUpgrade,
		GEO_GREENBUTTON,
		GEO_GRAYBUTTON,
		GEO_UNLOCKTEXT,
		GEO_UPGRADETEXT,
		GEO_Table,
		GEO_Laptop,
		GEO_Laptop2,
		GEO_Laptop3,
		GEO_Phone1,
		GEO_Phone2,
		GEO_Phone3,
		GEO_Lift,
		GEO_Lift2,
		GEO_Lift3,
		GEO_Tree,
		GEO_Puzzlebg,
		GEO_Puzzlebgbg,
		GEO_PuzzlePlayer,
		GEO_PuzzlePaper,
		GEO_PuzzleBorder,
		GEO_Screen,
		GEO_op1,
		GEO_op2,
		GEO_op3,
		GEO_PREop1,
		GEO_PREop2,
		GEO_PREop3,
		GEO_HTP,
		GEO_HTPSCREEN,
		GEO_Body,
		GEO_Head,
		GEO_Arms,
		GEO_GRASS3D,
		GEO_CHEST,
		GEO_CAT,
		GEO_ROCK,
		GEO_HIGHHOLE,
		GEO_COIN,

		GEO_TAXI,
		GEO_TRUCK,
		GEO_POLICE,
		GEO_ROAD,
		GEO_STREETLIGHT,
		GEO_ROADTURN,
		GEO_ROADTSECT,


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
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};
public:
	Splevel1();
	~Splevel1();
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
	void RenderSkybox(void);
	void RenderWorkStation(int WorkStation);
	void RenderName(int Lvl);
	float rotateAngle;
	float rotateAngleF;
	float rotateAngleSF;
	float rotateAnglesC;
	float liftdoor;
	float liftdoor2;
	bool bEnableLight;
	bool questions,Pqeustions;
	std::string NameList[36];
	//void Playsoundfile(string filename)	
	//{
	//	mciSendString("play mp3", NULL, 0, NULL);
	//}

	void PuzzleRender();
	void UpdatePuzzleControls();
	void UpdateMainControls();

	void UpdateCarepackage(double dt);
	void RenderCarepackage();

	void packagedieanimation();

	void rendermoneyfly();

	

	EquipmentManager Manager;

	Puzzle puzzle;
	bool PuzzleActive;
	bool PuzzleUIActive;
	bool PuzzleWinUI;
	bool PuzzleLoseUI;
	bool PuzzlePlayerPickup;

	bool packagedie;

	float puzzletimer;
	float packagetimer;
	float packagecooltimer;

	float packagetruckoffset;


	enum class Gamestate {MainGame,PuzzleGame}gamestate;

	donotcarepackage* carepackage;

	int RenderUI;
	int RenderPrestige;
	int PageNum;

	int coinsrotation;

	int scaleval[50];
	int scalevalgrass[50];

	int coinsarray[50];

	float debugmouseposx;
	float debugmouseposy;
	
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey, bool RotateX = false);
	void RenderCoinsOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	int Random(int range);
	void InitName(void);
	Camera3 camera;
};

#endif