#include <iostream>
#include <windows.h>
#include <string>
#include "Splevel1.h"
#include "GL\glew.h"
#include "LoadTGA.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include <string>
#include "Light.h"
#include "Material.h"
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <ctime>
#include "../Puzzle.h"
#include "../donotcarepackage.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


using namespace std;
Splevel1::Splevel1()
{
}

Splevel1::~Splevel1()
{
}
void Splevel1::Init()
{
	// Set background color to dark blue
	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Blending.fragmentshader");
	m_programID = LoadShaders("Shader//Texture.vertexshader","Shader//Text.fragmentshader");



	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");


	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");


	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");



	m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
	m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
	m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
	m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
	m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
	m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
	m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
	m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");


	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID,"numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] =glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID,"textColor");

	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_NUMLIGHTS], 5);

	//Replace previous code
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 0.3;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);


	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(0, 0, 1);
	light[1].color.Set(1, 1, 1);
	light[1].power = 0.3;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);
	
	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	//Replace previous code
	light[2].type = Light::LIGHT_DIRECTIONAL;
	light[2].position.Set(0, 0, -1);
	light[2].color.Set(1, 1, 1);
	light[2].power = 0.3;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);


	light[3].type = Light::LIGHT_DIRECTIONAL;
	light[3].position.Set(1, 0, 0);
	light[3].color.Set(1, 1, 1);
	light[3].power = 0.3;
	light[3].kC = 1.f;
	light[3].kL = 0.01f;
	light[3].kQ = 0.001f;
	light[3].cosCutoff = cos(Math::DegreeToRadian(45));
	light[3].cosInner = cos(Math::DegreeToRadian(30));
	light[3].exponent = 3.f;
	light[3].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[3].exponent);

	//Replace previous code
	light[4].type = Light::LIGHT_DIRECTIONAL;
	light[4].position.Set(-1, 0, 0);
	light[4].color.Set(1, 1, 1);
	light[4].power = 0.3;
	light[4].kC = 1.f;
	light[4].kL = 0.01f;
	light[4].kQ = 0.001f;
	light[4].cosCutoff = cos(Math::DegreeToRadian(45));
	light[4].cosInner = cos(Math::DegreeToRadian(30));
	light[4].exponent = 3.f;
	light[4].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT4_TYPE], light[4].type);
	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &light[4].color.r);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], light[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], light[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], light[4].kQ);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], light[4].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], light[4].cosInner);
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], light[4].exponent);

	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);

	//variable to rotate geometry
	rotateAngle = 0;

	for (int i = 0; i < 50; i++)
	{
		scaleval[i] = (rand() % 60) + 60;
	}

	for (int i = 0; i < 50; i++)
	{
		scalevalgrass[i] = (rand() % 20) + 10;
	}

	for (int i = 0; i < 30; i++)
	{
		coinsarray[i].x = (rand() % 80) + 1;
		coinsarray[i].y = (rand() % 80) + 70;
		coinsarray[i].z = (rand() % 20) + 20;
	}

	RenderUI = 0;
	RenderPrestige = 1;
	PageNum = 1;

	coinsrotation = 0;

	puzzle.Init();

	packagetimer = 60;

	packagecooltimer = 10;

	packagetruckoffset = 2000;

	//Initialize camera settings
	camera.Init(Vector3(0, 30, 345), Vector3(0, 0, 0), Vector3(0, 1, 0));

	PuzzleActive = false;
	PuzzleUIActive = false;
	PuzzlePlayerPickup = false;

	gamestate = Splevel1::Gamestate::MainGame;

	carepackage = new donotcarepackage();

	puzzletimer = 60;
	
	// Init VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");

	meshList[GEO_TopUI] = MeshBuilder::GenerateRec("TopUI", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_TopUI]->textureID = LoadTGA("Image//SP2_TopUI.tga");

	meshList[GEO_BotUI] = MeshBuilder::GenerateRec("BotUI", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_BotUI]->textureID = LoadTGA("Image//SP2_BotUI.tga");

	meshList[GEO_Puzzlebg] = MeshBuilder::GenerateQuad("Quad", Color(1, 1, 1), 1.f);
	meshList[GEO_Puzzlebg]->textureID = LoadTGA("Image//TitleFrame.tga");

	meshList[GEO_SideUISmall] = MeshBuilder::GenerateRec("SideUISmall", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_SideUISmall]->textureID = LoadTGA("Image//SP2_SideUI_Small.tga");

	meshList[GEO_SideUIBig] = MeshBuilder::GenerateRec("SideUIBig", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_SideUIBig]->textureID = LoadTGA("Image//SP2_SideUI_Big.tga");

	meshList[GEO_MaxPrestige] = MeshBuilder::GenerateRec("MaxPrestige", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_MaxPrestige]->textureID = LoadTGA("Image//SP2_SideUI_Max.tga");

	meshList[GEO_GreenUpgrade] = MeshBuilder::GenerateRec("GreenUpgrade", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_GreenUpgrade]->textureID = LoadTGA("Image//SP2_SideUI_GreenUpgrade.tga");

	meshList[GEO_GrayUpgrade] = MeshBuilder::GenerateRec("GrayUpgrade", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_GrayUpgrade]->textureID = LoadTGA("Image//SP2_SideUI_GrayUpgrade.tga");

	meshList[GEO_GREENBUTTON] = MeshBuilder::GenerateRec("GreenButton", Color(0, 1, 0.16), 0.3f, 1.f);

	meshList[GEO_GRAYBUTTON] = MeshBuilder::GenerateRec("GrayButton", Color(0.39, 0.39, 0.39), 0.3f, 1.f);

	meshList[GEO_UNLOCKTEXT] = MeshBuilder::GenerateRec("UnlockText", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_UNLOCKTEXT]->textureID = LoadTGA("Image//UnlockText.tga");

	meshList[GEO_UPGRADETEXT] = MeshBuilder::GenerateRec("UpgradeText", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_UPGRADETEXT]->textureID = LoadTGA("Image//UpgradeText.tga");

	meshList[GEO_TITLEBUTTONS] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_TITLEBUTTONS]->textureID = LoadTGA("Image//TitleButton.tga");

	meshList[GEO_TITLE] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_TITLE]->textureID = LoadTGA("Image//TitleFrame.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 0.8), 1.f);

	meshList[GEO_GRASS] = MeshBuilder::GenerateOBJMTL("model211", "OBJ//ground_grass.obj", "OBJ//ground_grass.mtl");
	meshList[GEO_GRASS_V] = MeshBuilder::GenerateOBJMTL("model211", "OBJ//grassLarge.obj", "OBJ//grassLarge.mtl");


	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJMTL("modelBUIDLING","OBJ//LVL1_withfloor.obj", "OBJ//LVL1_withfloor.mtl");
	meshList[GEO_LBUILDING1] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//large_buildingA.obj", "OBJ//large_buildingA.mtl");
	meshList[GEO_LBUILDING2] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//large_buildingB.obj", "OBJ//large_buildingB.mtl");
	meshList[GEO_LBUILDING3] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//large_buildingD.obj", "OBJ//large_buildingD.mtl");
	meshList[GEO_SBUILDING1] = MeshBuilder::GenerateOBJMTL("modelSBUIDLING", "OBJ//small_buildingB.obj", "OBJ//small_buildingB.mtl");
	meshList[GEO_SKYSCRAPER1] = MeshBuilder::GenerateOBJMTL("modelSkyScraper", "OBJ//skyscraperF.obj", "OBJ//skyscraperF.mtl");

	meshList[GEO_LVL2] = MeshBuilder::GenerateOBJMTL("modelLVL2", "OBJ//LVL2.obj", "OBJ//LVL2.mtl");

	meshList[GEO_LVL3] = MeshBuilder::GenerateOBJMTL("modelLVL3", "OBJ//LVL3.obj", "OBJ//LVL3.mtl");

	meshList[GEO_Table] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//simple_table.obj", "OBJ//simple_table.mtl");

	meshList[GEO_ROCK] = MeshBuilder::GenerateOBJMTL("Rock", "OBJ//rock_largeB.obj", "OBJ//rock_largeB.mtl");

	meshList[GEO_COIN] = MeshBuilder::GenerateOBJMTL("Coin", "OBJ//Coin.obj", "OBJ//Coin.mtl");
	meshList[GEO_COIN]->textureID = LoadTGA("Image//Coin.tga");

	meshList[GEO_Screen] = MeshBuilder::GenerateRec("Rec", Color(1, 1, 1), 3.f, 5.f);
	meshList[GEO_Screen]->textureID = LoadTGA("Image//Phone.tga"); // beats me
	//whatever

	meshList[GEO_LAPTOP_UI] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_LAPTOP_UI]->textureID = LoadTGA("Image//Beetcoin.tga");


	meshList[GEO_op1] = MeshBuilder::GenerateRec("Rec", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_op1]->textureID = LoadTGA("Image//OP1.tga");

	meshList[GEO_op2] = MeshBuilder::GenerateRec("Rec", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_op2]->textureID = LoadTGA("Image//OP2.tga");

	meshList[GEO_op3] = MeshBuilder::GenerateRec("Rec", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_op3]->textureID = LoadTGA("Image//OP3.tga");

	meshList[GEO_PREop1] = MeshBuilder::GenerateRec("Rec", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_PREop1]->textureID = LoadTGA("Image//Pre_OP1.tga");

	meshList[GEO_PREop2] = MeshBuilder::GenerateRec("Rec", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_PREop2]->textureID = LoadTGA("Image//Pre_OP2.tga");

	meshList[GEO_PREop3] = MeshBuilder::GenerateRec("Rec", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_PREop3]->textureID = LoadTGA("Image//Pre_OP3.tga");

	meshList[GEO_HTP] = MeshBuilder::GenerateRec("Rec", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_HTP]->textureID = LoadTGA("Image//HTP.tga");

	meshList[GEO_HTPSCREEN] = MeshBuilder::GenerateQuad("Quad", Color(1, 1, 1), 1.f);
	meshList[GEO_HTPSCREEN]->textureID = LoadTGA("Image//HTPscreen.tga");

	meshList[GEO_Tree] = MeshBuilder::GenerateOBJMTL("Tree", "OBJ//TreeTall.obj", "OBJ//TreeTall.mtl");
	meshList[GEO_Laptop] = MeshBuilder::GenerateOBJMTL("Laptop", "OBJ//Laptop.obj", "OBJ//Laptop.mtl");
	meshList[GEO_Laptop2] = MeshBuilder::GenerateOBJMTL("Computerlvl2", "OBJ//ComputerLVL2.obj", "OBJ//ComputerLVL2.mtl");
	meshList[GEO_Laptop3] = MeshBuilder::GenerateOBJMTL("Computerlvl3", "OBJ//ComputerLVL3.obj", "OBJ//ComputerLVL3.mtL");
	meshList[GEO_Phone1] = MeshBuilder::GenerateOBJMTL("Phone1", "OBJ//PhoneLVL1.obj", "OBJ//PhoneLVL1.mtl");
	meshList[GEO_Phone2] = MeshBuilder::GenerateOBJMTL("Phone1", "OBJ//Phone1.obj", "OBJ//Phone1.mtl");
	meshList[GEO_Phone3] = MeshBuilder::GenerateOBJMTL("Phone1", "OBJ//PhoneLVL3.obj", "OBJ//PhoneLVL3.mtl");
	meshList[GEO_Body] = MeshBuilder::GenerateOBJMTL("Body", "OBJ//Body.obj", "OBJ//Body.mtl");
	meshList[GEO_Body]->textureID = LoadTGA("Image//Body.tga");
	meshList[GEO_Head] = MeshBuilder::GenerateOBJMTL("Head", "OBJ//Head.obj", "OBJ//Head.mtl");
	meshList[GEO_Head]->textureID = LoadTGA("Image//Skin.tga");
	meshList[GEO_Arms] = MeshBuilder::GenerateOBJMTL("Arms", "OBJ//Arms.obj", "OBJ//Arms.mtl");
	meshList[GEO_Arms]->textureID = LoadTGA("Image//Skin.tga");
	meshList[GEO_TAXI] = MeshBuilder::GenerateOBJMTL("Tree", "OBJ//taxi.obj", "OBJ//taxi.mtl");
	meshList[GEO_POLICE] = MeshBuilder::GenerateOBJMTL("Tree", "OBJ//police.obj", "OBJ//police.mtl");
	meshList[GEO_TRUCK] = MeshBuilder::GenerateOBJMTL("Tree", "OBJ//delivery.obj", "OBJ//delivery.mtl");
	meshList[GEO_ROAD] = MeshBuilder::GenerateOBJMTL("Tree", "OBJ//road_straight.obj", "OBJ//road_straight.mtl");
	meshList[GEO_ROADTURN] = MeshBuilder::GenerateOBJMTL("Turn", "OBJ//road_bendSquare.obj", "OBJ//road_bendSquare.mtl");
	meshList[GEO_ROADTSECT] = MeshBuilder::GenerateOBJMTL("Tsect", "OBJ//road_drivewaySingle.obj", "OBJ//road_drivewaySingle.mtl");
	meshList[GEO_STREETLIGHT] = MeshBuilder::GenerateOBJMTL("streetlight", "OBJ//streetlight.obj", "OBJ//streetlight.mtl");
	meshList[GEO_CASH] = MeshBuilder::GenerateOBJMTL("streetlight", "OBJ//Cash.obj", "OBJ//Cash.mtl");
	meshList[GEO_MONEYCAT] = MeshBuilder::GenerateOBJMTL("streetlight", "OBJ//Moneycat.obj", "OBJ//Moneycat.mtl");
	meshList[GEO_MONEYPLANT] = MeshBuilder::GenerateOBJMTL("streetlight", "OBJ//Moneyplant.obj", "OBJ//Moneyplant.mtl");


	meshList[GEO_Lift] = MeshBuilder::GenerateOBJ("modelBUIDLING", "OBJ//Elevator.obj");
	meshList[GEO_Lift]->textureID = LoadTGA("Image//Elevator.tga");

	meshList[GEO_PAPER] = MeshBuilder::GenerateOBJ("modelBUIDLING", "OBJ//Paper.obj");
	meshList[GEO_PAPER]->textureID = LoadTGA("Image//Notelines.tga");

	meshList[GEO_EMPTYBOX] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_EMPTYBOX]->textureID = LoadTGA("Image//TitleFrame.tga");

	meshList[GEO_DOORS] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_DOORS]->textureID = LoadTGA("Image//Elevator.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16,16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Agency_FB.tga");

	meshList[GEO_Puzzlebg] = MeshBuilder::GenerateQuad("puzzlebg", Color(1, 1, 1), 1.f);
	meshList[GEO_Puzzlebg]->textureID = LoadTGA("Image//Puzzlebg.tga");

	meshList[GEO_Puzzlebgbg] = MeshBuilder::GenerateQuad("puzzlebgbg", Color(1, 1, 1), 1.f);
	meshList[GEO_Puzzlebgbg]->textureID = LoadTGA("Image//Ricardo.tga");

	meshList[GEO_PuzzlePlayer] = MeshBuilder::GenerateQuad("puzzlebg", Color(1, 1, 1), 1.f);
	meshList[GEO_PuzzlePlayer]->textureID = LoadTGA("Image//Ricardo.tga");

	meshList[GEO_PuzzlePaper] = MeshBuilder::GenerateQuad("puzzlebg", Color(1, 1, 1), 1.f);
	meshList[GEO_PuzzlePaper]->textureID = LoadTGA("Image//PuzzlePaper.tga");

	meshList[GEO_PuzzleBorder] = MeshBuilder::GenerateQuad("puzzlebord", Color(1, 1, 1), 1.f);
	meshList[GEO_PuzzleBorder]->textureID = LoadTGA("Image//PlayerBorder.tga");

	meshList[GEO_GRASS3D] = MeshBuilder::GenerateOBJMTL("Grass3D", "OBJ//Grass.obj", "OBJ//Grass.mtl");

	meshList[GEO_CHEST] = MeshBuilder::GenerateOBJMTL("Grass3D", "OBJ//chest.obj", "OBJ//chest.mtl");

	meshList[GEO_HIGHHOLE] = MeshBuilder::GenerateOBJMTL("HighHole", "OBJ//HighHole.obj", "OBJ//HighHole.mtl");

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 100000.f);
	projectionStack.LoadMatrix(projection);
	liftdoor2 = 80;
	InitName();
}

bool setuppolice = false, clearpolice, paper1, paper2, paper3, paper4, timerstart, win, lose, NPC, NPC2, NPC3, NPC4, startlaptop = false, evidence_won_bonus, die;
double scaleevidence = 0.1, countdown, timer;
float prologuey = -40, scaletitle = 0 , pposx, pposz, pposx2, pposz2, pposx4, pposx3, pposz3, pposz4, rotateangle, pposy, pposy2, pposy3, pposy4, pushaway, movex = -500, movex2 = -500, movex3 = 500, movex4 = 500, movez, AlignX;
string timerstring, beetsinstringform, Dialogue, Answer1, Answer2;
int totalbeets = 0, countdownbonus = 1500, spinD = 0;

int mg1_start, dialoguepart, rannpc;
bool lvl2, lvl3,lvl1=true, playonce, NPCInteract;
bool Bankrupt, prologue = true, doneonce, OP1, OP2, OP3,OP1check, OP2check,OP3check,deleterest,LS_start,LS_Win,LS_Lose,POP1,POP2,POP3, rotateback = true, spawntaxi, spawnpolice, spawntruck,closed,closed2,closing, HTP;

float cposx, cposz, movecar;
void Splevel1::Update(double dt)
{
	Manager.UpdateMoney(dt);
	cposx = camera.position.x;
	cposz = camera.position.z;
	rotateangle = rotateangle + 0.1;

	int carepackagerand;
	carepackagerand = (rand() % 10) + 1;

	UpdateCoinsAnimation(dt);

	if (carepackage->active == false)
	{
		packagecooltimer -= dt;
	}

	
	if (carepackagerand == 9 && carepackage->active == false && packagecooltimer < 0)
	{
		carepackage->reset(-430,430,307,429);
		packagetimer = 60;
		packagecooltimer = 10;

		carepackage->active = true;
		carepackage->notitext = true;
		
	}

	UpdateCarepackage(dt);

	if (PuzzleActive == true)
	{
		gamestate = Splevel1::Gamestate::PuzzleGame;
	}
	else
	{
		gamestate = Splevel1::Gamestate::MainGame;
	}

	if (mg1_start == 300 && clearpolice == false) setuppolice = true;
	if (setuppolice == true && clearpolice == false)
	{
		if (Manager.PrestigeLvl <= 2)
		{
			pposz = 19;
			pposx = (rand() % 100 + 0) - 50;
			pposz = (rand() % 100 + 0) - 50;
			pposx2 = (rand() % 100 + 0) - 50;
			pposz2 = (rand() % 100 + 0) - 50;
			pposx3 = (rand() % 100 + 0) - 50;
			pposz3 = (rand() % 100 + 0) - 50;
			pposy = 18;
			pposy2 = 18;
			pposy3 = 18;
			scaleevidence = 2;
			countdown = 600;
			clearpolice = true;
		}
		else
		{
			pposz = 19;
			pposx = (rand() % 100 + 0) - 50;
			pposz = (rand() % 100 + 0) - 50;
			pposx2 = (rand() % 100 + 0) - 50;
			pposz2 = (rand() % 100 + 0) - 50;
			pposx3 = (rand() % 100 + 0) - 50;
			pposz3 = (rand() % 100 + 0) - 50;
			pposx4 = (rand() % 100 + 0) - 50;
			pposz4 = (rand() % 100 + 0) - 50;
			pposy = 18;
			pposy2 = 18;
			pposy3 = 18;
			pposy4 = 18;
			scaleevidence = 2;
			countdown = 550;
			clearpolice = true;
		}
	}
	if (clearpolice == true)
	{
		if (cposx > pposx - 10 && cposx < pposx + 10 && cposz > pposz - 10 && cposz < pposz + 10 && paper1 == false)
		{
			paper1 = true;
			pposy = 0;
		}
		else if (cposx > pposx2 - 10 && cposx < pposx2 + 10 && cposz > pposz2 - 10 && cposz < pposz2 + 10 && paper2 == false)
		{
			paper2 = true;
			pposy2 = 0;
		}
		else if (cposx > pposx3 - 10 && cposx < pposx3 + 10 && cposz > pposz3 - 10 && cposz < pposz3 + 10 && paper3 == false)
		{
			paper3 = true;
			pposy3 = 0;
		}
		else if (cposx > pposx4 - 10 && cposx < pposx4 + 10 && cposz > pposz4 - 10 && cposz < pposz4 + 10 && paper4 == false)
		{
			paper4 = true;
			pposy4 = 0;
		}

		if (Manager.PrestigeLvl <= 2)
		{
			if (paper1 == true && paper2 == true && paper3 == true)
			{
				win = true;
				clearpolice = false;

				paper1 = false;
				paper2 = false;
				paper3 = false;
				paper4 = false;
				timerstart = false;
			}
		}
		else
		{
			if (paper1 == true && paper2 == true && paper3 == true && paper4 == true)
			{
				win = true;
				clearpolice = false;

				paper1 = false;
				paper2 = false;
				paper3 = false;
				paper4 = false;
				timerstart = false;
			}
		}
	}

	if (startlaptop == true)
	{
		static bool bLButtonState = false;
		if (debugmouseposx > 35 && debugmouseposx < 48 && debugmouseposy > 18 && debugmouseposy < 35)
		{
			if (!bLButtonState && Application::IsMousePressed(0))
			{
				bLButtonState = true;
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				totalbeets++;
				Manager.Money = Manager.Money + 1;
				beetsinstringform = to_string(totalbeets);
			}
			else if (bLButtonState && !Application::IsMousePressed(0))
			{
				bLButtonState = false;
			}
		}

		if (debugmouseposx > 55 && debugmouseposx < 59 && debugmouseposy > 6 && debugmouseposy < 15)
		{
			if (!bLButtonState && Application::IsMousePressed(0))
			{
				startlaptop = false;
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
		}
	}
	if (timerstart == true)
	{
		Sleep(5);
		countdown--;
		timer = countdown / 10;
		timerstring = to_string(timer);


	}
	if (timer < 0)
	{
		lose = true;
		timer = 0;
		countdown = 0;
		pposy = 0;
		pposy2 = 0;
		pposy3 = 0;
		paper1 = false;
		paper2 = false;
		paper3 = false;
		paper4 = false;
	}


	int randomno = rand() % 7 + 0;
	if (randomno == 1 && spawnpolice == false && spawntruck == false && spawntaxi == false)
	{
		spawntaxi = true;
	}
	if (randomno == 2 && spawnpolice == false && spawntruck == false && spawntaxi == false)
	{
		spawnpolice = true;
	}
	if (randomno == 3 && spawnpolice == false && spawntruck == false && spawntaxi == false)
	{
		spawntruck = true;
	}

	if (randomno == 4 && NPCInteract == false)
	{
		NPC = true;
		movex += 5;
		if (movex >= 500)
		{
			movex = -500;
			NPC = false;
		}
	}
	if (randomno == 5 && NPCInteract == false)
	{
		NPC2 = true;
		movex2 += 6;
		if (movex >= 500)
		{
			movex = -500;
			NPC2 = false;
		}
	}
	if (randomno == 6 && NPCInteract == false)
	{
		NPC3 = true;
		movex3 -= 5;
		if (movex <= -500)
		{
			movex3 = 500;
			NPC3 = false;
		}
	}
	if (randomno == 7 && NPCInteract == false)
	{
		NPC4 = true;
		movex4 -= 4;
		if (movex4 <= -500)
		{
			movex = 500;
			NPC4 = false;
		}
	}


	if (spawnpolice == true)
	{
		movecar += 20;
		if (movecar >= 1200)
		{
			movecar = -1200;
			spawnpolice = false;
		}
	}
	if (spawntaxi == true)
	{
		movecar += 15;
		if (movecar >= 1200)
		{
			movecar = -1200;
			spawntaxi = false;
		}
	}
	if (spawntruck == true)
	{
		movecar += 11;
		if (movecar >= 1200)
		{
			movecar = -1200;
			spawntruck = false;
		}
	}

	
	//static const float 
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	rotateAngle += (float)(30 * dt);

	if (Application::IsKeyPressed('5'))
	{
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}

	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(10 * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(10 * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(10 * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(10 * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(10 * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(10 * dt);

	// Reset Position and variables

	//Mouse Inputs
	double x, y;
	Application::GetCursorPos(&x, &y);
	unsigned w = Application::GetWindowWidth();
	unsigned h = Application::GetWindowHeight();
	float posX = (x / w) * 80; //convert (0,800) to (0,80)
	float posY = 60 - (y / h) * 60; //convert (600,0) to (0,60)
	debugmouseposx = posX;
	debugmouseposy = posY;

	//luke
	switch (gamestate)
	{
	case Splevel1::Gamestate::MainGame:
		UpdateMainControls();
		break;
	case Splevel1::Gamestate::PuzzleGame:
		UpdatePuzzleControls();
		break;
	default:
		break;
	}

	if (PuzzleActive == true)
	{
		puzzletimer -= dt;
		if (puzzle.Wincheck() == true)
		{
			PuzzleActive = false;
			if (Manager.PrestigeLvl == 0)
			{
				puzzletimer = 60;
				Manager.MinigameBuffs += 1;
			}
			else if (Manager.PrestigeLvl == 1)
			{
				puzzletimer = 50;
				Manager.MinigameBuffs += 2;
			}
			else if (Manager.PrestigeLvl == 2)
			{
				puzzletimer = 40;
				Manager.MinigameBuffs += 3;
			}
			else if (Manager.PrestigeLvl == 3)
			{
				puzzletimer = 30;
				Manager.MinigameBuffs += 5;
			}
			PuzzleWinUI = true;
			
		}
		else if (puzzletimer < 0)
		{
			PuzzleActive = false;
			if (Manager.PrestigeLvl == 0)
			{
				puzzletimer = 60;
				
			}
			else if (Manager.PrestigeLvl == 1)
			{
				puzzletimer = 50;
				
			}
			else if (Manager.PrestigeLvl == 2)
			{
				puzzletimer = 40;
				
			}
			else if (Manager.PrestigeLvl == 3)
			{
				puzzletimer = 30;
				
			}
			
			PuzzleLoseUI = true;
		}
	}
	//end

	if (evidence_won_bonus == true)
	{
		int timerbonus = 0;
		Sleep(10);
		countdownbonus--;
		timerbonus = countdownbonus / 10;
		timerstring = to_string(timerbonus);

		if (timerbonus < 0)
		{
			Manager.MinigameBuffs -= 15;
			evidence_won_bonus = false;
		}

	}

	//player table
	{
		//Evidence mini game
		if (camera.position.x > 30 && camera.position.x < 45 && (camera.position.z > 55 && camera.position.z < 65) && (lvl1==true))
		{
			if (Application::IsKeyPressed('E'))
			{
				setuppolice = true;
			}
		}
		//Laptop mini game
		if (camera.position.x > 30 && camera.position.x < 45 && (camera.position.z > 40 && camera.position.z < 55) && (lvl1 == true))
		{
			if (Application::IsKeyPressed('E'))
			{
				startlaptop = true;
			}
			else if(Application::IsKeyPressed('F'))
			{
				if (PuzzleActive == false)
				{
					PuzzleUIActive = true;
				}
			}
		}
		//Phone mini game
		if (camera.position.x > 30 && camera.position.x < 45 && (camera.position.z > 30 && camera.position.z < 40) && (lvl1 == true))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to start phone", Color(0, 1, 0), 4, 10, 30);
			if (Application::IsKeyPressed('E'))
			{
				LS_start = true;
			}
			if (Manager.PrestigeLvl >= 1)
			{
				if (questions == true)
				{
					if (deleterest == false)
					{
						int rnd = rand() % 3 + 0;
						if (rnd == 0 && OP1check == false && OP2 != true && OP3 != true)
						{
							POP1 = true;
							deleterest = true;
						}
						if (rnd == 1 && OP2check == false && OP3 != true && OP1 != true)
						{
							POP2 = true;
							deleterest = true;
						}
						if (rnd == 2 && OP3check == false && OP2 != true && OP1 != true)
						{
							POP3 = true;
							deleterest = true;
						}
					}
				}
				else if (deleterest == true)
				{
					POP1 = false;
					POP2 = false;
					POP3 = false;
					deleterest = false;
				}
			}
			else
			{
				if (questions == true)
				{
					if (deleterest == false)
					{
						int rnd = rand() % 3 + 0;
						if (rnd == 0 && OP1check == false && OP2 != true && OP3 != true)
						{
							OP1 = true;
							deleterest = true;
						}
						if (rnd == 1 && OP2check == false && OP3 != true && OP1 != true)
						{
							OP2 = true;
							deleterest = true;
						}
						if (rnd == 2 && OP3check == false && OP2 != true && OP1 != true)
						{
							OP3 = true;
							deleterest = true;
						}
					}
				}
				else if (deleterest == true)
				{
					OP1 = false;
					OP2 = false;
					OP3 = false;
					deleterest = false;
				}
			}
		}
		static bool bLButtonState = false;
		if (!bLButtonState && Application::IsMousePressed(0))
		{
			bLButtonState = true;
			//Converting Viewport space to UI space
			double x, y;
			Application::GetCursorPos(&x, &y);
			unsigned w = Application::GetWindowWidth();
			unsigned h = Application::GetWindowHeight();
			float posX = x / w * 80; //convert (0,800) to (0,80)
			float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
			if (LS_start == true)
			{
				if (posX > 35 && posX < 45 && posY > 8 && posY < 18)
				{
					questions = true;
					LS_start = false;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}

			if (OP1 == true)
			{
				if (posX > 47 && posX < 62 && (posY > 47 && posY < 62))//op1
				{
					questions = false;
					LS_Win = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 27 && posY < 40))//op2
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 10 && posY < 22))//op3
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}
			if (OP2 == true)
			{
				if (posX > 47 && posX < 62 && (posY > 27 && posY < 40))//op2
				{
					questions = false;
					LS_Win = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 47 && posY < 62))//op1
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 10 && posY < 22))//op3
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}
			if (OP3 == true)
			{
				if (posX > 47 && posX < 62 && (posY > 10 && posY < 22))//op3
				{
					questions = false;
					LS_Win = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 27 && posY < 40))//op2
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 47 && posY < 62))//op1
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}
			//Prestiege ans
			if (POP1 == true)
			{
				if (posX > 47 && posX < 62 && (posY > 49 && posY < 58))//op1
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 35 && posY < 45))//op2 win
				{
					questions = false;
					LS_Win = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 23 && posY < 32))//op3
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 9.5 && posY < 19))//op4
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}
			if (POP2 == true)
			{
				if (posX > 47 && posX < 62 && (posY > 49 && posY < 58))//op1
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 35 && posY < 45))//op2
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 23 && posY < 32))//op3
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 9.5 && posY < 19))//op4 win
				{
					questions = false;
					LS_Win = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}
			if (POP3 == true)
			{
				if (posX > 47 && posX < 62 && (posY > 49 && posY < 58))//op1
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 35 && posY < 45))//op2
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 23 && posY < 32))//op3 win
				{
					questions = false;
					LS_Win = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 47 && posX < 62 && (posY > 9.5 && posY < 19))//op4 
				{
					questions = false;
					LS_Lose = true;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}
			if (LS_Win == true)
			{
				if (Manager.PrestigeLvl>=1 && (posX > 35 && posX < 44 && (posY > 10 && posY < 21)))
				{
					Manager.Money = Manager.Money + 100;
					PlaySound(TEXT("Sent.wav"), NULL, SND_ASYNC);
					LS_Win = false;
					PlaySound(TEXT("Sent.wav"), NULL, SND_ASYNC);
				}
				else if (posX > 35 && posX < 44 && (posY > 10 && posY < 21))
				{
					Manager.Money = Manager.Money + 50;
					PlaySound(TEXT("Sent.wav"), NULL, SND_ASYNC);
					LS_Win = false;
					PlaySound(TEXT("Sent.wav"), NULL, SND_ASYNC);
				}
				
			}
			if (LS_Lose == true)
			{
				if (Manager.PrestigeLvl >= 1 && (posX > 35 && posX < 44 && (posY > 10 && posY < 21)))
				{
					Manager.Money = Manager.Money - 150;
					PlaySound(TEXT("Sent.wav"), NULL, SND_ASYNC);
					LS_Lose = false;
				}
				if (posX > 35 && posX < 44 && (posY > 10 && posY < 21))
				{
					Manager.Money = Manager.Money - 100;
					PlaySound(TEXT("Sent.wav"), NULL, SND_ASYNC);
					LS_Lose = false;
				}
			}
			if (PuzzleUIActive == true)
			{
				if (posX > 35 && posX < 45 && posY > 8 && posY < 14)
				{
					PuzzleActive = true;
					puzzle.Resetgame();
					PuzzleUIActive = false;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}
			if (PuzzleWinUI == true)
			{
				if (posX > 35 && posX < 45 && posY > 8 && posY < 19)
				{
					PuzzleWinUI = false;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}

			if (PuzzleLoseUI == true)
			{
				if (posX > 35 && posX < 45 && posY > 8 && posY < 19)
				{
					PuzzleLoseUI = false;
					if(Manager.Money < 0)
					Manager.Money += Manager.Money / 5;

					else Manager.Money += Manager.Money / 5;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}
			if (die == true)
			{
				if (posX > 35 && posX < 45 && posY > 8 && posY < 19)
				{

					if (Manager.Money < 0)
						Manager.Money += Manager.Money;

					else Manager.Money -= Manager.Money / 2;
					die = false;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}
			if (posX > 72 && posX < 79.9 && posY > 5 && posY < 12)
			{
				HTP = true;
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			if (HTP == true)
			{
				if (posX > 56 && posX < 60 && posY > 8 && posY < 12)
				{
					HTP = false;
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
				}
			}
		}
		else if (bLButtonState && !Application::IsMousePressed(0))
		{
		bLButtonState = false;
		}
	}


	// Player get hit by car

	if (camera.position.z > 230 && camera.position.z < 270)
	{
		if (camera.position.x > movecar - 25 && camera.position.x < movecar + 25)
		{
			die = true;
			PlaySound(TEXT("Die.wav"), NULL, SND_ASYNC);
		}

		else if (camera.position.x > movecar - 25 && camera.position.x < movecar + 1200 && playonce == false )
		{
			PlaySound(TEXT("Horn.wav"), NULL, SND_ASYNC);
			playonce = true;
		}
	}

	//Character Animation
	if (rotateback == false)
	{
		spinD += 300;
	}
	if (rotateback == true)
	{
		spinD -= -300;
	}
	if (rotateAngle >= 45) rotateback = true;
	else if (rotateAngle < 0) rotateback = false;
	

	//lift animation
	{
		if (closing == true)
		{
			//door left
			if (closed == false)
			{
				liftdoor += (float)(40 * dt);
			}
			if (closed == true)
			{
				liftdoor -= (float)(40 * dt);
			}
			if (liftdoor >= 10)
			{
				closed = true;
			}
			else if (liftdoor <= -35)
			{
				closed = false;
				closing = false;
			}

			//door right
			if (closed2 == false)
			{
				liftdoor2 -= (float)(40 * dt);
			}
			if (closed2 == true)
			{
				liftdoor2 += (float)(40 * dt);
			}
			if (liftdoor2 >= 115)
			{
				closed2 = false;
			}
			else if (liftdoor2 <= 70)
			{
				closed2 = true;
				closing = false;
			}
		}
	}

	//Levels
	{
		static bool BButtonState = false;
		static bool CButtonState = false;
		if (lvl1 == true)
		{
			camera.target.y = 30 - camera.position.y + camera.target.y;
			camera.position.y = 30;
			camera.LevelNum = 1;
		}
		if (lvl2 == true)
		{
			camera.target.y = 80 - camera.position.y + camera.target.y;
			camera.position.y = 80;
			camera.LevelNum = 2;
		}
		if (lvl3 == true)
		{
			camera.target.y = 130 - camera.position.y + camera.target.y;
			camera.position.y = 130;
			camera.LevelNum = 3;
		}

		//Level Checker
		if (camera.position.x > 25 && camera.position.x < 60 && (camera.position.z < -50 && camera.position.z > -60) && (lvl1==true))//L1
		{
			if (!BButtonState && Application::IsKeyPressed('E'))
			{
				BButtonState = true;

				if (Manager.PrestigeLvl > 0)
				{
					lvl2 = true;
					lvl1 = false;
					closing = true;
				}
			}
			else if (BButtonState && !Application::IsKeyPressed('E'))
			{
				BButtonState = false;
			}
		}
		if (camera.position.x > 25 && camera.position.x < 60 && (camera.position.z < -50 && camera.position.z > -60 &&(lvl2 == true)))//L2
		{
			if (!BButtonState && Application::IsKeyPressed('E'))
			{
				BButtonState = true;

				if (Manager.PrestigeLvl >=2)
				{
					lvl3 = true;
					lvl2 = false;
					closing = true;
				}
			}
			else if (BButtonState && !Application::IsKeyPressed('E'))
			{
				BButtonState = false;
			}
			if (!CButtonState && Application::IsKeyPressed('F'))
			{
				CButtonState = true;
				lvl2 = false;
				lvl1 = true;
				closing = true;
			}
			else if (CButtonState && !Application::IsKeyPressed('F'))
			{
				CButtonState = false;
			}
		}
		if (camera.position.x > 25 && camera.position.x < 60 && (camera.position.z < -50 && camera.position.z > -60 && (lvl3 == true)))//L3
		{
			if (!BButtonState && Application::IsKeyPressed('E'))
			{
				BButtonState = true;
				lvl3 = false;
				lvl2 = true;
				closing = true;
			}
			else if (BButtonState && !Application::IsKeyPressed('E'))
			{
				BButtonState = false;
			}
			if (!CButtonState && Application::IsKeyPressed('F'))
			{
				CButtonState = true;
				lvl3 = false;
				lvl1 = true;
				closing = true;
			}
			else if (CButtonState && !Application::IsKeyPressed('F'))
			{
				CButtonState = false;
			}
		}
	}
	

	if (Application::IsKeyPressed('C') || camera.AbleStand == 1 ) //enable crouching
	{
		if (lvl1 == true)
		{
			camera.target.y = 14 - camera.position.y + camera.target.y;
			camera.position.y = 14;
		}
		if (lvl2 == true)
		{
			camera.target.y = 64 - camera.position.y + camera.target.y;
			camera.position.y = 64;
		}
		if (lvl3 == true)
		{
			camera.target.y = 114 - camera.position.y + camera.target.y;
			camera.position.y = 114;
		}
		camera.LevelNum += 3;
	}
	if (camera.minigamestatus == false)
	{
		if (Manager.NumOfComputers() >= Manager.NumOfPhones())
		{
			camera.EquipNum = Manager.NumOfComputers();
		}
		else
		{
			camera.EquipNum = Manager.NumOfPhones();
		}

		if (packagedie == false)
		{
			camera.Update(dt);
		}
		

	}

	//NPC interactions
	{
		
		if (NPCInteract == true)
		{
			int ran = rand() % 1 + 1;

			if (doneonce == false)
			{
				rannpc = rand() % 2 + 1;
				doneonce = true;
			}
			static bool bLButtonState = false;
			if (ran == 1)
				if (rannpc == 1)
				{
					if (dialoguepart == 0)
					{
						Dialogue = "Whats up?";
						AlignX = 24;
						Answer1 = "Do you want a FREE product?";
						Answer2 = "Im here to scam you";
						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							Sleep(150);
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								dialoguepart = 1;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 4;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
						}
						else bLButtonState = false;
					}
					if (dialoguepart == 1)
					{
						Dialogue = "Sounds legit, im listening.";
						Answer2 = "There is a shipping fee";
						Answer1 = "I need your credit card info";

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							Sleep(150);
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
								dialoguepart = 5;
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 2;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
						}
						else bLButtonState = false;
					}

					if (dialoguepart == 2)
					{
						Dialogue = "Whats the fee?";
						Answer2 = "$50";
						Answer1 = "$400";

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							Sleep(150);
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
								dialoguepart = 6;
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 3;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
						}
						else bLButtonState = false;
					}

					if (dialoguepart == 3)
					{
						Dialogue = "Sounds totally legit! Im in!";
						Answer1 = "Nice";
						Answer2 = "Nice";

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								Manager.Money += 50;
								dialoguepart = 0;
								NPCInteract = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
								doneonce = false;
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								Manager.Money += 50;
								dialoguepart = 0;
								NPCInteract = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
								doneonce = false;
							}
						}
						else bLButtonState = false;
					}

					if (dialoguepart == 4)
					{
						Dialogue = "What? Get away from me you creep!";
						Answer1 = "Ok";
						Answer2 = "Ok";

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								dialoguepart = 0;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
								NPCInteract = false;
								doneonce = false;

							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 0;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
								NPCInteract = false;
								doneonce = false;
							}
						}
						else bLButtonState = false;
					}

					if (dialoguepart == 5)
					{
						Dialogue = "i need my credit card for a free product? scam!";
						Answer1 = "end";
						Answer2 = "end";

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								dialoguepart = 0;
								NPCInteract = false;
								doneonce = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 0;
								NPCInteract = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
								doneonce = false;
							}
						}
						else bLButtonState = false;
					}

					if (dialoguepart == 6)
					{
						Dialogue = "Thats way too expensive! Clearly a scam!";
						Answer1 = "end";
						Answer2 = "end";

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								dialoguepart = 0;
								NPCInteract = false;
								doneonce = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 0;
								NPCInteract = false;
								doneonce = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
						}
						else bLButtonState = false;
					}
				}

				else if (rannpc == 2)
				{
					if (dialoguepart == 0)
					{
						Dialogue = "Hi! I can double your money!";
						AlignX = 24;
						Answer2 = "No, its a scam"; // w
						Answer1 = "Sounds interesting!"; // c
						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							Sleep(150);
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								dialoguepart = 1;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 0;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
								NPCInteract = false;
							}
						}
						else bLButtonState = false;
					}
					if (dialoguepart == 1)
					{
						Dialogue = "Just pay it now and ill return you double instantly!";
						Answer1 = "Pay $2000"; // w
						Answer2 = "Pay $50"; // c

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							Sleep(150);
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
								dialoguepart = 5;
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 2;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
						}
						else bLButtonState = false;
					}

					if (dialoguepart == 2)
					{
						Dialogue = "*he gives you $100, hoping you give more*";
						Answer1 = "i believe you! Pay $2000"; // w
						Answer2 = "Run with the money lol"; // c

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							Sleep(150);
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								dialoguepart = 5;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 3;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
						}
						else bLButtonState = false;
					}

					if (dialoguepart == 3)
					{
						Dialogue = "Hey! My money!";
						Answer1 = "Run";
						Answer2 = "Run";

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								dialoguepart = 0;
								Manager.Money += 100;
								NPCInteract = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 0;
								Manager.Money += 100;
								NPCInteract = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
						}
						else bLButtonState = false;
					}

					if (dialoguepart == 4)
					{
						Dialogue = "What? Get away from me you creep!";
						Answer1 = "Ok";
						Answer2 = "Ok";

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								dialoguepart = 0;
								NPCInteract = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 0;
								NPCInteract = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
						}
						else bLButtonState = false;
					}

					if (dialoguepart == 5)
					{
						Dialogue = "*He takes your money and runs*";
						Answer1 = "end";
						Answer2 = "end";

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								dialoguepart = 0;
								Manager.Money += -2000;
								NPCInteract = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 0;
								Manager.Money += -2000;
								NPCInteract = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
						}
						else bLButtonState = false;
					}

					if (dialoguepart == 6)
					{
						Dialogue = "*He takes your money and runs*";
						Answer1 = "end";
						Answer2 = "end";

						if (!bLButtonState && Application::IsMousePressed(0))
						{
							bLButtonState = true;
							double x, y;
							Application::GetCursorPos(&x, &y);
							unsigned w = Application::GetWindowWidth();
							unsigned h = Application::GetWindowHeight();
							float posX = x / w * 80; //convert (0,800) to (0,80)
							float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
							if (posX > 5 && posX < 35 && (posY > 10 && posY < 18)) // Box1
							{
								dialoguepart = 0;
								Manager.Money += -1950;
								NPCInteract = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
							if (posX > 45 && posX < 75 && (posY > 10 && posY < 18)) // Box2
							{
								dialoguepart = 0;
								Manager.Money += -1950;
								NPCInteract = false;
								PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
							}
						}
						else bLButtonState = false;
					}
			}
		}
	}


	// prologue
	

	if (prologue == true)
	{
		static bool bLButtonState = false;
		prologuey += 0.1;

		if (prologuey >= 50)
		{
			scaletitle += 0.3;
		}
		
		if (scaletitle >= 6)
		{
			Sleep(1500);
			prologue = false;
		}
		if (!bLButtonState && Application::IsMousePressed(0))
		{
			bLButtonState = true;
			double x, y;
			Application::GetCursorPos(&x, &y);
			unsigned w = Application::GetWindowWidth();
			unsigned h = Application::GetWindowHeight();
			float posX = x / w * 80; //convert (0,800) to (0,80)
			float posY = 60 - y / h * 60; //convert (600,0) to (0,60)
			if (posX > 0 && posX < 12 && (posY > 18 && posY < 25)) // Box1
			{
				prologue = false;
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			else
				prologuey += 0.5;
		}
		else bLButtonState = false;
	}

	if (Manager.Money < 0) Bankrupt = false;

	
}

	



void Splevel1::Render()
{
	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,camera.target.x, camera.target.y, camera.target.z,camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();


	Vector3 lightDir1(light[1].position.x, light[1].position.y, light[1].position.z);
	Vector3 lightDirection_cameraspace1 = viewStack.Top() * lightDir1;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace1.x);

	Vector3 lightDir2(light[2].position.x, light[2].position.y, light[2].position.z);
	Vector3 lightDirection_cameraspace2 = viewStack.Top() * lightDir2;
	glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace2.x);

	Vector3 lightDir3(light[3].position.x, light[3].position.y, light[3].position.z);
	Vector3 lightDirection_cameraspace3 = viewStack.Top() * lightDir3;
	glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightDirection_cameraspace3.x);

	Vector3 lightDir4(light[4].position.x, light[4].position.y, light[4].position.z);
	Vector3 lightDirection_cameraspace4 = viewStack.Top() * lightDir4;
	glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightDirection_cameraspace4.x);

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	
	srand(time(0));
	RenderSkybox();

	//Render trees
	{
		for (int i = 0; i < 30; i++)
		{
		
				modelStack.PushMatrix();
				
				modelStack.Translate(-450 + (i * 30), 0, -450);
				modelStack.Rotate(scaleval[i] * scaleval[i], 0, 1, 0);
				modelStack.Scale(scaleval[i], scaleval[i], scaleval[i]);

				RenderMesh(meshList[GEO_Tree], true);
				modelStack.PopMatrix();
			
		}

		for (int i = 0; i < 30; i++)
		{
			
			modelStack.PushMatrix();
			//modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Translate(-450 + (i * 30), 0, 450);
			modelStack.Rotate(scaleval[i] * scaleval[i], 0, 1, 0);
			modelStack.Scale(scaleval[i], scaleval[i], scaleval[i]);

			RenderMesh(meshList[GEO_Tree], true);
			modelStack.PopMatrix();
		}

		for (int i = 0; i < 30; i++)
		{
			int x = -450 + (i * 30);
			if (x > 200 && x < 300);
			else
			{
				modelStack.PushMatrix();
				//modelStack.Rotate(-90, 1, 0, 0);
				modelStack.Translate(-450, 0, -450 + (i * 30));
				modelStack.Rotate(scaleval[i] * scaleval[i], 0, 1, 0);
				modelStack.Scale(scaleval[i], scaleval[i], scaleval[i]);

				RenderMesh(meshList[GEO_Tree], true);
				modelStack.PopMatrix();
			}
		}

		for (int i = 0; i < 30; i++)
		{
			int x = -450 + (i * 30);
			if (x > 200 && x < 300);
			else
			{
				modelStack.PushMatrix();
				//modelStack.Rotate(-90, 1, 0, 0);
				modelStack.Translate(450, 0, -450 + (i * 30));
				modelStack.Rotate(scaleval[i] * scaleval[i], 0, 1, 0);
				modelStack.Scale(scaleval[i], scaleval[i], scaleval[i]);

				RenderMesh(meshList[GEO_Tree], true);
				modelStack.PopMatrix();
			}
		}
	}

	//Grass3D
	//front
	for (int x = 0; x < 4; x++)
	{
		for (int i = 0; i < 40; i++)
		{
			modelStack.PushMatrix();

			modelStack.Translate(-500 + (i * 30), 0, 320 + (x * 40));
			modelStack.Rotate(scaleval[i] * scaleval[i], 0, 1, 0);
			//modelStack.Scale(scaleval[i], scaleval[i], scaleval[i]);
			modelStack.Scale(scalevalgrass[i], scalevalgrass[i], scalevalgrass[i]);

			RenderMesh(meshList[GEO_GRASS3D], true);
			modelStack.PopMatrix();
		}
	}

	//back
	for (int x = 0; x < 6; x++)
	{
		for (int i = 0; i < 40; i++)
		{
			modelStack.PushMatrix();

			modelStack.Translate(-500 + (i * 30), 0, -220 - (x * 40));
			modelStack.Rotate(scaleval[i] * scaleval[i], 0, 1, 0);
			//modelStack.Scale(scaleval[i], scaleval[i], scaleval[i]);
			modelStack.Scale(scalevalgrass[i], scalevalgrass[i], scalevalgrass[i]);

			RenderMesh(meshList[GEO_GRASS3D], true);
			modelStack.PopMatrix();
		}
	}

	//left
	for (int x = 0; x < 10; x++)
	{
		for (int i = 0; i < 10; i++)
		{
			modelStack.PushMatrix();

			modelStack.Translate(-210 - (i * 30), 0, 180 - (x * 40));
			modelStack.Rotate(scaleval[i] * scaleval[i], 0, 1, 0);
			modelStack.Scale(scalevalgrass[i], scalevalgrass[i], scalevalgrass[i]);

			RenderMesh(meshList[GEO_GRASS3D], true);
			modelStack.PopMatrix();
		}
	}

	//right
	for (int x = 0; x < 10; x++)
	{
		for (int i = 0; i < 10; i++)
		{
			modelStack.PushMatrix();

			modelStack.Translate(210 + (i * 30), 0, 180 - (x * 40));
			modelStack.Rotate(scaleval[i] * scaleval[i], 0, 1, 0);
			modelStack.Scale(scalevalgrass[i], scalevalgrass[i], scalevalgrass[i]);

			RenderMesh(meshList[GEO_GRASS3D], true);
			modelStack.PopMatrix();
		}
	}

	//Surrounding buildings
	{
		modelStack.PushMatrix();
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Translate(0, 0, 320);
		modelStack.Scale(180, 180, 180);
		RenderMesh(meshList[GEO_LBUILDING1], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Translate(0, 0, 320);
		modelStack.Scale(300, 180, 180);
		RenderMesh(meshList[GEO_LBUILDING2], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Translate(0, 0, 300);
		modelStack.Scale(300, 180, 180);
		RenderMesh(meshList[GEO_LBUILDING3], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Translate(300, 0, 300);
		modelStack.Scale(120, 120, 120);
		RenderMesh(meshList[GEO_SKYSCRAPER1], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(330, 0, -300);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(200, 200, 200);
		RenderMesh(meshList[GEO_SBUILDING1], true);
		modelStack.PopMatrix();
	}
	//upgrades
	{
		if (Manager.MoneyPlantUpgrade == 1)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-50, 0, 150);
			modelStack.Scale(5,7,5);
			{
				modelStack.PushMatrix();
				modelStack.Translate(0, 3, 2);
				modelStack.Rotate(90, 0, 1, 0);
				modelStack.Rotate(90, 0, 0, 1);
				modelStack.Rotate(rotateAngle, 0, 1, 0);
				modelStack.Scale(0.7, 0.7, 0.7);
				RenderMesh(meshList[GEO_CASH], true);
				modelStack.PopMatrix();
			}
			RenderMesh(meshList[GEO_MONEYPLANT], true);
			modelStack.PopMatrix();
		}
		if (Manager.LuckyCatUpgrade == 1)
		{
			modelStack.PushMatrix();
			modelStack.Translate(50, -7, 150);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(10, 10, 10);
			{
				modelStack.PushMatrix();
				modelStack.Translate(0, 3, 0);
				modelStack.Rotate(rotateAngle, 0, 1, 0);
				modelStack.Scale(0.3, 0.3, 0.3);
				RenderMesh(meshList[GEO_CASH], true);
				modelStack.PopMatrix();
			}
			RenderMesh(meshList[GEO_MONEYCAT], true);
			modelStack.PopMatrix();
		}
	}
	//Outside Border
	{
		//HighWay Gate
		modelStack.PushMatrix();
		modelStack.Scale(50, 120, 180);
		modelStack.Rotate(90, 0, 1, 0);
		{
			modelStack.PushMatrix();
			modelStack.Translate(-1.4, 0, 21.5);
			RenderMesh(meshList[GEO_HIGHHOLE], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-1.4, 0, -21.5);
			RenderMesh(meshList[GEO_HIGHHOLE], true);
			modelStack.PopMatrix();

		}
		modelStack.PopMatrix();

		//Gate Rock
		modelStack.PushMatrix();
		modelStack.Scale(500, 500, 500);
		{
			modelStack.PushMatrix();
			modelStack.Translate(-2.4, 0, 0.6);
			modelStack.Rotate(-45, 0, 1, 0);
			RenderMesh(meshList[GEO_ROCK], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(2.4, 0, 0.5);
			modelStack.Rotate(-45, 0, 1, 0);
			modelStack.Rotate(-180, 0, 1, 0);
			RenderMesh(meshList[GEO_ROCK], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();

		//Grass Side
		{
			modelStack.PushMatrix();
			modelStack.Translate(300, 0, 600);
			modelStack.Scale(300, 180, 180);
			modelStack.Rotate(180, 0, 1, 0);
			RenderMesh(meshList[GEO_LBUILDING2], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-300, 0, 600);
			modelStack.Scale(300, 180, 180);
			modelStack.Rotate(180, 0, 1, 0);
			RenderMesh(meshList[GEO_LBUILDING2], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Translate(0, 0, -650);
			modelStack.Scale(300, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING3], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-650, 0, 650);
			modelStack.Scale(180, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING1], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(650, 0, 650);
			modelStack.Scale(180, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING1], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(450, 0, 900);
			modelStack.Scale(120, 120, 120);
			modelStack.Rotate(180, 0, 1, 0);
			RenderMesh(meshList[GEO_SKYSCRAPER1], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-450, 0, 900);
			modelStack.Scale(120, 120, 120);
			modelStack.Rotate(180, 0, 1, 0);
			RenderMesh(meshList[GEO_SKYSCRAPER1], true);
			modelStack.PopMatrix();
		}
		//Building Side
		{
			modelStack.PushMatrix();
			modelStack.Translate(300, 0, -600);
			modelStack.Scale(300, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING2], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-300, 0, -600);
			modelStack.Scale(300, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING2], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(0, 0, -650);
			modelStack.Scale(300, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING3], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-650, 0, -650);
			modelStack.Scale(180, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING1], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(650, 0, -650);
			modelStack.Scale(180, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING1], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(450, 0, -900);
			modelStack.Scale(120, 120, 120);
			RenderMesh(meshList[GEO_SKYSCRAPER1], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-450, 0, -900);
			modelStack.Scale(120, 120, 120);
			RenderMesh(meshList[GEO_SKYSCRAPER1], true);
			modelStack.PopMatrix();
		}
		//Road Side Right Side
		modelStack.PushMatrix();
		modelStack.Scale(1, 1, 1);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Translate(300, 0, 0);
		{
			modelStack.PushMatrix();
			modelStack.Translate(300, 0, 600);
			modelStack.Scale(300, 180, 180);
			modelStack.Rotate(180, 0, 1, 0);
			RenderMesh(meshList[GEO_LBUILDING2], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-300, 0, 600);
			modelStack.Scale(300, 180, 180);
			modelStack.Rotate(180, 0, 1, 0);
			RenderMesh(meshList[GEO_LBUILDING2], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Translate(0, 0, -650);
			modelStack.Scale(300, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING3], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Translate(-700, 0, -350);
			modelStack.Scale(300, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING3], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Translate(-1000, 0, -350);
			modelStack.Scale(180, 180, 180);
			RenderMesh(meshList[GEO_SKYSCRAPER1], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Translate(750, 0, 750);
			modelStack.Scale(300, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING1], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();


		//Road Side Left Side
		modelStack.PushMatrix();
		modelStack.Scale(1, 1, 1);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Translate(300, 0, -1600);
		{
			modelStack.PushMatrix();
			modelStack.Translate(300, 0, 600);
			modelStack.Scale(300, 180, 180);
			modelStack.Rotate(180, 0, 1, 0);
			RenderMesh(meshList[GEO_LBUILDING2], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-300, 0, 600);
			modelStack.Scale(300, 180, 180);
			modelStack.Rotate(180, 0, 1, 0);
			RenderMesh(meshList[GEO_LBUILDING2], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Translate(0, 0, -650);
			modelStack.Scale(300, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING3], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Translate(-700, 0, -350);
			modelStack.Scale(300, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING3], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Translate(-1000, 0, -350);
			modelStack.Scale(180, 180, 180);
			RenderMesh(meshList[GEO_SKYSCRAPER1], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Translate(750, 0, 750);
			modelStack.Scale(300, 180, 180);
			RenderMesh(meshList[GEO_LBUILDING1], true);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	//Road and cars
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0.3, 250);
		modelStack.Scale(100, 10, 80);
		RenderMesh(meshList[GEO_ROAD], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0.3, -130);
		modelStack.Scale(225, 10, 100);
		RenderMesh(meshList[GEO_ROAD], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(150, 0.3, 250);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(246, 10, 80);
		RenderMesh(meshList[GEO_ROADTSECT], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-150, 0.3, 250);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(246, 10, 80);
		RenderMesh(meshList[GEO_ROADTSECT], true);
		modelStack.PopMatrix();


		modelStack.PushMatrix();
		modelStack.Translate(150, 0.3, 60);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(300, 10, 80);
		RenderMesh(meshList[GEO_ROAD], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-150, 0.3, 60);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(300, 10, 80);
		RenderMesh(meshList[GEO_ROAD], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(150, 0.3, -130);
		modelStack.Scale(80, 10, 100);
		RenderMesh(meshList[GEO_ROADTURN], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-150, 0.3, -130);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(100, 10, 80);
		RenderMesh(meshList[GEO_ROADTURN], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(700, 0.3, 250);
		modelStack.Scale(1000, 10, 80);
		RenderMesh(meshList[GEO_ROAD], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-700, 0.3, 250);
		modelStack.Scale(1000, 10, 80);
		RenderMesh(meshList[GEO_ROAD], true);
		modelStack.PopMatrix();

		if (spawntaxi == true)
		{
			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Translate(-250, 0, movecar);
			modelStack.Scale(30, 30, 30);
			RenderMesh(meshList[GEO_TAXI], true);
			modelStack.PopMatrix();
		}

		if (spawnpolice == true)
		{
			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Translate(-250, 0, movecar);
			modelStack.Scale(30, 30, 30);
			RenderMesh(meshList[GEO_POLICE], true);
			modelStack.PopMatrix();
		}

		if (spawntruck == true)
		{
			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Translate(-250, 0, movecar);
			modelStack.Scale(30, 30, 30);
			RenderMesh(meshList[GEO_TRUCK], true);
			modelStack.PopMatrix();
		}
	}

	packagedieanimation();

	//streetlight
	for (int i = 0; i < 5; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-400 + (i * 300), 0, 290);
		/*modelStack.Rotate(90, 0, 1, 0);
		modelStack.Rotate(90, 1, 0, 0);*/
		modelStack.Scale(150, 250, 150);
		RenderMesh(meshList[GEO_STREETLIGHT], true);
		modelStack.PopMatrix();
	}
	for (int i = 0; i < 5; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-550 + (i * 300), 0, 210);
		modelStack.Rotate(180, 0, 1, 0);

		modelStack.Scale(150, 250, 150);
		RenderMesh(meshList[GEO_STREETLIGHT], true);
		modelStack.PopMatrix();
	}

	if (NPC == true)
	{
		//Render NPC
		modelStack.PushMatrix();
		modelStack.Translate(movex, 5, 200);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_Body], false);
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_Head], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	if (NPC2 == true)
	{
		//Render NPC
		modelStack.PushMatrix();
		modelStack.Translate(movex2, 5, 190);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_Body], false);
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_Head], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	if (NPC3 == true)
	{
		//Render NPC
		modelStack.PushMatrix();
		modelStack.Translate(movex3, 5, 210);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_Body], false);
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_Head], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	if (NPC4 == true)
	{
		//Render NPC
		modelStack.PushMatrix();
		modelStack.Translate(movex4, 5, 220);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_Body], false);
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_Head], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}




	//Building
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 0);
		modelStack.Scale(10, 10, 10);
		{
			modelStack.PushMatrix();
			modelStack.Translate(6.52, 2.5, -7);
			modelStack.Rotate(90, 0, 0, 1);
			modelStack.Scale(1.3, 0.9, 1);
			RenderMesh(meshList[GEO_Lift], true);
			modelStack.PopMatrix();
		}
		RenderMesh(meshList[GEO_BUILDING], true);
		modelStack.PopMatrix();

		if (lvl1 == true)
		{
			modelStack.PushMatrix();
			RenderName(1);
			modelStack.PopMatrix();
		}

		if (Manager.PrestigeLvl > 0)
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 50, 0);
			modelStack.Scale(10, 10, 10);
			{
				modelStack.PushMatrix();
				modelStack.Translate(6.52, 2.5, -7);
				modelStack.Rotate(90, 0, 0, 1);
				modelStack.Scale(1.3, 0.9, 1);
				RenderMesh(meshList[GEO_Lift], true);
				modelStack.PopMatrix();
			}
			RenderMesh(meshList[GEO_LVL2], true);
			modelStack.PopMatrix();
			if (lvl2 == true)
			{
				modelStack.PushMatrix();
				RenderName(2);
				modelStack.PopMatrix();
			}
		}
		if (Manager.PrestigeLvl > 1)
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 100, 0);
			modelStack.Scale(10, 10, 10);
			{
				modelStack.PushMatrix();
				modelStack.Translate(6.52, 2.5, -7);
				modelStack.Rotate(90, 0, 0, 1);
				modelStack.Scale(1.3, 0.9, 1);
				RenderMesh(meshList[GEO_Lift], true);
				modelStack.PopMatrix();
			}
			RenderMesh(meshList[GEO_LVL3], true);
			modelStack.PopMatrix(); 
			if (lvl3 == true)
			{
				modelStack.PushMatrix();
				RenderName(3);
				modelStack.PopMatrix();
			}
		}
		//L1 lift
		if (camera.position.x > 25 && camera.position.x < 60 && (camera.position.z < -50 && camera.position.z > -60) && (lvl1==true))
		{
			if (Manager.PrestigeLvl > 0)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to L2", Color(0, 1, 0), 4,25, 30);
			}
			else
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Reach prestige 1 for lift access", Color(0, 1, 0), 4, 25, 30);
			}
		}
		//L2 lift
		if (camera.position.x > 25 && camera.position.x < 60 && (camera.position.z < -50 && camera.position.z > -60) && (lvl2 == true))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'F' to L1", Color(0, 1, 0), 4, 25, 27);

			if (Manager.PrestigeLvl > 1)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to L3", Color(0, 1, 0), 4, 25, 30);
			}
			else
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Reach prestige 2 for L3", Color(0, 1, 0), 4, 25, 30);
			}
		}
		//L3 lift
		if (camera.position.x > 25 && camera.position.x < 60 && (camera.position.z < -50 && camera.position.z > -60) && (lvl3 == true))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to L2", Color(0, 1, 0), 4, 25, 30);
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'F' to L1", Color(0, 1, 0), 4, 25, 27);
		}
	}


	//WorkStation Rendering
	{
		int WorkStationPositionX, WorkStationPositionY, WorkStationPositionZ;
		WorkStationPositionX = WorkStationPositionY = WorkStationPositionZ = 0;
		for (int i = 0; i < (Manager.PrestigeLvl + 1) * 6; ++i)
		{
			if (i < 6)
			{
				WorkStationPositionY = 0;
			}
			else if (i < 12)
			{
				WorkStationPositionY = 50;
			}
			else if (i < 18)
			{
				WorkStationPositionY = 100;
			}
			WorkStationPositionX = -75;
			if (i % 6 == 0)
			{
				WorkStationPositionZ = 40;
			}
			else if (i % 6 == 1)
			{
				WorkStationPositionZ = 20;
			}
			else if (i % 6 == 2)
			{
				WorkStationPositionZ = 0;
			}
			else if (i % 6 == 3)
			{
				WorkStationPositionZ = -30;
			}
			else if (i % 6 == 4)
			{
				WorkStationPositionZ = -50;
			}
			else if (i % 6 == 5)
			{
				WorkStationPositionZ = -70;
			}
			modelStack.PushMatrix();
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(WorkStationPositionX, WorkStationPositionY, WorkStationPositionZ);
			RenderWorkStation(i);
			modelStack.PopMatrix();
		}
	}


	//kjcode
	{
		//Default Equipment
		modelStack.PushMatrix();
		modelStack.Translate(50, 0, 45);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(10, 10, 10);
		{
			modelStack.PushMatrix();
			modelStack.Translate(-1.5, 2.05, 0);
			modelStack.Rotate(90, 0, 0, 1);
			modelStack.Scale(0.5, 0.25, 0.5);
			{
				modelStack.PushMatrix();
				modelStack.Translate(0, -6, -1);
				modelStack.Rotate(90, 0, 1, 0);
				modelStack.Rotate(90, 1, 0, 0);
				modelStack.Scale(0.6, 0.5, 1.5);
				{
					modelStack.PushMatrix();
					modelStack.Translate(0, 0, 3);
					modelStack.Rotate(90, 1, 0, 0);
					modelStack.Scale(1, 0.6, 1.2);
					RenderMesh(meshList[GEO_Phone1], true); //Render Phone 1
					modelStack.PopMatrix();
				}
				RenderMesh(meshList[GEO_Laptop], true);
				modelStack.PopMatrix();
			}
			RenderMesh(meshList[GEO_PAPER], true);
			modelStack.PopMatrix();
		}
		RenderMesh(meshList[GEO_Table], true);
		modelStack.PopMatrix();

		RenderCarepackage();

		rendermoneyfly();

		//Evidence mini game
		if (camera.position.x > 30 && camera.position.x < 45 && (camera.position.z > 55 && camera.position.z < 65) && (lvl1 == true))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to start Evidence", Color(0, 1, 0), 4, 10, 30);
		}
		//Laptop mini game
		if (camera.position.x > 30 && camera.position.x < 45 && (camera.position.z > 40 && camera.position.z < 55) && (lvl1 == true))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to start Laptop", Color(0, 1, 0), 4, 10, 30);
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'F' to start stack minigame", Color(0, 1, 0), 4, 6, 25);

			if (Application::IsKeyPressed('F'))
			{
				PuzzleUIActive = true;
			}
		}
		//Phone mini game
		if (camera.position.x > 30 && camera.position.x < 45 && (camera.position.z > 30 && camera.position.z < 40) && (lvl1 == true))
		{
			if (questions == false)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to start phone", Color(0, 1, 0), 4, 10, 30);
			}
		}

		// NPC
		static bool BButtonState = false;
		static bool CButtonState = false;
		if (camera.position.x > movex - 40 && camera.position.x < movex + 40 && (camera.position.z < 240 && camera.position.z > 160))//L3
		{
			
			if (NPCInteract == false)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to Interact with NPC", Color(0, 1, 0), 4, 10, 30);
			}
			if (!BButtonState && Application::IsKeyPressed('E'))
			{
				NPCInteract = true;

			}
			else if (BButtonState && !Application::IsKeyPressed('E'))
			{

				BButtonState = false;
			}
		}
		if (camera.position.x > movex2 - 40 && camera.position.x < movex2 + 40 && (camera.position.z < 240 && camera.position.z > 160))//L3
		{

			if (NPCInteract == false)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to Interact with NPC", Color(0, 1, 0), 4, 10, 30);
			}
			if (!BButtonState && Application::IsKeyPressed('E'))
			{
				NPCInteract = true;

			}
			else if (BButtonState && !Application::IsKeyPressed('E'))
			{

				BButtonState = false;
			}
		}
		if (camera.position.x > movex3 - 40 && camera.position.x < movex3 + 40 && (camera.position.z < 240 && camera.position.z > 160))//L3
		{

			if (NPCInteract == false)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to Interact with NPC", Color(0, 1, 0), 4, 10, 30);
			}
			if (!BButtonState && Application::IsKeyPressed('E'))
			{
				NPCInteract = true;

			}
			else if (BButtonState && !Application::IsKeyPressed('E'))
			{

				BButtonState = false;
			}
		}
		if (camera.position.x > movex4 - 40 && camera.position.x < movex4 + 40 && (camera.position.z < 240 && camera.position.z > 160))//L3
		{

			if (NPCInteract == false)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to Interact with NPC", Color(0, 1, 0), 4, 10, 30);
			}
			if (!BButtonState && Application::IsKeyPressed('E'))
			{
				NPCInteract = true;

			}
			else if (BButtonState && !Application::IsKeyPressed('E'))
			{

				BButtonState = false;
			}
		}
		//Lovescam mini game
		if (LS_start == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Minigame: Lovers Scam!", Color(1, 1, 1), 2, 30, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "You have a data base of random numbers", Color(1, 1, 1), 2, 21, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "you must use your scam skills to pick", Color(1, 1, 1), 2, 21, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "the most convincing answer without", Color(1, 1, 1), 2, 21, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "raising suspicion.", Color(1, 1, 1), 2, 21, 26);
			RenderTextOnScreen(meshList[GEO_TEXT], "Reward: $50  Premium Reward: $100", Color(1, 1, 1), 2, 21, 21);
			RenderTextOnScreen(meshList[GEO_TEXT], "Penalty: -$100  Premium Penalty: -$150", Color(1, 1, 1), 2, 21, 18);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Start!", Color(1, 1, 1), 2, 37, 9);
		}
		if (LS_Win == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Congratulations!", Color(1, 1, 1), 2, 32, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "You managed to earn your", Color(1, 1, 1), 2, 21, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "targets trust and scam their money.", Color(1, 1, 1), 2, 21, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "Reward: $50", Color(1, 1, 1), 2, 21, 21);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Hooray!", Color(1, 1, 1), 2, 37, 9);
		}
		if (LS_Win == true && Manager.PrestigeLvl > 1)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Congratulations!", Color(1, 1, 1), 2, 32, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "You managed to earn your", Color(1, 1, 1), 2, 21, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "targets trust and scam their money.", Color(1, 1, 1), 2, 21, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "Reward: $100", Color(1, 1, 1), 2, 21, 21);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Hooray!", Color(1, 1, 1), 2, 37, 9);
		}
		if (LS_Lose == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Oh No!", Color(1, 1, 1), 2, 37, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "You didn't manage to convince", Color(1, 1, 1), 2, 21, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "the target they've reported you and", Color(1, 1, 1), 2, 21, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "have to pay a fine.", Color(1, 1, 1), 2, 21, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "Penalty: -$100", Color(1, 1, 1), 2, 21, 18);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Pay up", Color(1, 1, 1), 2, 37, 9);
		}
		if (LS_Lose == true && Manager.PrestigeLvl > 1)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Oh No!", Color(1, 1, 1), 2, 37, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "You didn't manage to convince", Color(1, 1, 1), 2, 21, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "the target they've reported you and", Color(1, 1, 1), 2, 21, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "have to pay a fine.", Color(1, 1, 1), 2, 21, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "Penalty: -$150", Color(1, 1, 1), 2, 21, 18);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Pay up", Color(1, 1, 1), 2, 37, 9);
		}

		if (PuzzleUIActive == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Minigame: Stack Overflow!", Color(1, 1, 1), 2, 27, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Someone has hacked into your computer", Color(1, 1, 1), 2, 23, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "and you have to block the hack!", Color(1, 1, 1), 2, 22, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "You have to drag rico to the blocks", Color(1, 1, 1), 2, 22, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "of code. If he is near a block, you can ", Color(1, 1, 1), 2, 20.5, 26);
			RenderTextOnScreen(meshList[GEO_TEXT], "pick it up and move it. Your goal is to", Color(1, 1, 1), 2, 20.5, 23);
			RenderTextOnScreen(meshList[GEO_TEXT], "stack all blocks together in one spot", Color(1, 1, 1), 2, 22, 21);
			RenderTextOnScreen(meshList[GEO_TEXT], "Reward: 5% permanent income boost", Color(1, 1, 1), 2, 24, 18);
			RenderTextOnScreen(meshList[GEO_TEXT], "Penalty: -20% of total income", Color(1, 1, 1), 2, 24, 15);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Start!", Color(1, 1, 1), 2, 37, 9);
		}

		if (PuzzleWinUI == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Congratulations!", Color(1, 1, 1), 2, 27, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "You managed to block the hack!", Color(1, 1, 1), 2, 23, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "You decided to upgrade your ", Color(1, 1, 1), 2, 24, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "computers antivirus.", Color(1, 1, 1), 2, 22, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "They will now work harder ", Color(1, 1, 1), 2, 24, 26);
			RenderTextOnScreen(meshList[GEO_TEXT], "Reward: 5% income boost permanently", Color(1, 1, 1), 2, 22, 21);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Hooray!", Color(1, 1, 1), 2, 37, 9);
		}
		if (PuzzleLoseUI == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Ouch!", Color(1, 1, 1), 2, 29, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "You didnt block the hack in time!", Color(1, 1, 1), 2, 21, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "The hacker demands your income as ransom", Color(1, 1, 1), 2, 21, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "Penalty: -20% of all cash", Color(1, 1, 1), 2, 24, 18);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Pay up", Color(1, 1, 1), 2, 37, 9);
		}

		if (Bankrupt == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 60, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Youre in debt!", Color(1, 1, 1), 2, 29, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Would you like to restart or keep going?", Color(1, 1, 1), 2, 21, 35);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 20, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Restart", Color(1, 1, 1), 2, 13, 9);

			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 60, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Keep going", Color(1, 1, 1), 2, 47, 9);
		}


		if (closing == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], liftdoor, 30, 60, 60);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], liftdoor2, 30, 60, 60);
		}
		
		RenderMeshOnScreen(meshList[GEO_HTP], 76, 5, 8, 8, true);

		if (HTP == true)
		{
			RenderMeshOnScreen(meshList[GEO_HTPSCREEN], 40, 25, 40, 40);
		}
		
	}

	//Koh Win Code
	{
		modelStack.PushMatrix();
		modelStack.Translate(pposx, pposy, pposz);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Rotate(rotateangle * 10, 0, 0, 1);
		modelStack.Scale(scaleevidence, scaleevidence, scaleevidence);
		RenderMesh(meshList[GEO_PAPER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(pposx2, pposy2, pposz2);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Rotate(rotateangle * 10, 0, 0, 1);
		modelStack.Scale(scaleevidence, scaleevidence, scaleevidence);
		RenderMesh(meshList[GEO_PAPER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(pposx3, pposy3, pposz3);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Rotate(rotateangle * 10, 0, 0, 1);
		modelStack.Scale(scaleevidence, scaleevidence, scaleevidence);
		RenderMesh(meshList[GEO_PAPER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(pposx4, pposy4, pposz4);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Rotate(rotateangle * 10, 0, 0, 1);
		modelStack.Scale(scaleevidence, scaleevidence, scaleevidence);
		RenderMesh(meshList[GEO_PAPER], true);
		modelStack.PopMatrix();


		

		

		if (timerstart == true) RenderTextOnScreen(meshList[GEO_TEXT], "Time left: " + timerstring, Color(1, 1, 1), 2, 37, 5);

		else if (setuppolice == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Minigame: Hide the Evidence!", Color(1, 1, 1), 2, 27, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Someone has filed a search warrant", Color(1, 1, 1), 2, 23, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "Against you for running a scam center", Color(1, 1, 1), 2, 22, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "You have to hide the evidence papers", Color(1, 1, 1), 2, 22, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "before the police arrive.", Color(1, 1, 1), 2, 24, 26);
			RenderTextOnScreen(meshList[GEO_TEXT], "Reward: +15% income boost for 30s", Color(1, 1, 1), 2, 22, 21);
			RenderTextOnScreen(meshList[GEO_TEXT], "Penalty: -20% of all cash", Color(1, 1, 1), 2, 24, 18);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Start!", Color(1, 1, 1), 2, 37, 9);
		}
		if (win == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Congratulations!", Color(1, 1, 1), 2, 27, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "You managed to hide all the evidence", Color(1, 1, 1), 2, 23, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "The police find you innocent", Color(1, 1, 1), 2, 24, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "Your workers feel motivated by this", Color(1, 1, 1), 2, 22, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "They will now work harder ", Color(1, 1, 1), 2, 24, 26);
			RenderTextOnScreen(meshList[GEO_TEXT], "Reward: +15% income boost for 30s", Color(1, 1, 1), 2, 22, 21);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Hooray!", Color(1, 1, 1), 2, 37, 9);
			
		}
		else if (lose == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Ouch!", Color(1, 1, 1), 2, 29, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "You didnt hide all the evidence in time", Color(1, 1, 1), 2, 21, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "The police has fined 20% of your income", Color(1, 1, 1), 2, 21, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "Penalty: -20% of all cash", Color(1, 1, 1), 2, 24, 18);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Pay up", Color(1, 1, 1), 2, 37, 9);
		}

		if (startlaptop == true)
		{
			RenderMeshOnScreen(meshList[GEO_LAPTOP_UI], 40, 25, 38, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "COMG OS", Color(0.5, 0.5, 1), 3, 24, 41);
			RenderTextOnScreen(meshList[GEO_TEXT], "Beetcoin clicker Legacy 2.0 deluxe (Free)", Color(1, 1, 1), 1.5, 25, 38);
			RenderTextOnScreen(meshList[GEO_TEXT], "Click the beet to earn beetcoins (worth $1)", Color(1, 1, 1), 1.5, 24.1, 34.5);
			RenderTextOnScreen(meshList[GEO_TEXT], "Total beetcoins earned: " + beetsinstringform, Color(1, 1, 1), 1.5, 29.1, 12);
		}

		if (die == true)
		{
			camera.Reset();
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 40, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "Ouch!", Color(1, 1, 1), 2, 29, 40);
			RenderTextOnScreen(meshList[GEO_TEXT], "You got hit by a car!", Color(1, 1, 1), 2, 21, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "Your hospital bill is expensive...", Color(1, 1, 1), 2, 21, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "Its probably a good idea not to.", Color(1, 1, 1), 2, 21, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "stay on the road for too long...", Color(1, 1, 1), 2, 21, 26);
			RenderTextOnScreen(meshList[GEO_TEXT], "Penalty: 50% of total income", Color(1, 1, 1), 2, 24, 18);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Pay up", Color(1, 1, 1), 2, 37, 9);
		}


		if (prologue == true)
		{
			camera.Reset();
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 25, 100, 100);
			RenderTextOnScreen(meshList[GEO_TEXT], "-- PROLOGUE --", Color(1, 1, 1), 2, 22, 40 + prologuey);
			RenderTextOnScreen(meshList[GEO_TEXT], "A long time ago", Color(1, 1, 1), 2, 22, 35 + prologuey);
			RenderTextOnScreen(meshList[GEO_TEXT], "In Nigeria, far far away", Color(1, 1, 1), 2, 22, 30 + prologuey);
			RenderTextOnScreen(meshList[GEO_TEXT], "There lived Ben Dover", Color(1, 1, 1), 2, 22, 25 + prologuey);
			RenderTextOnScreen(meshList[GEO_TEXT], "One day, he fell in love with a woman", Color(1, 1, 1), 2, 22, 20 + prologuey);
			RenderTextOnScreen(meshList[GEO_TEXT], "The woman asked for financial help", Color(1, 1, 1), 2, 22, 15 + prologuey);
			RenderTextOnScreen(meshList[GEO_TEXT], "Which Ben Dover obliged", Color(1, 1, 1), 2, 22, 10 + prologuey);
			RenderTextOnScreen(meshList[GEO_TEXT], "But it turned out to be a SCAM!", Color(1, 1, 1), 2, 22, 5 + prologuey);
			RenderTextOnScreen(meshList[GEO_TEXT], "Heartbroken, Ben sought revenge", Color(1, 1, 1), 2, 22, 0 + prologuey);
			RenderTextOnScreen(meshList[GEO_TEXT], "And he will do it by scamming other people!", Color(1, 1, 1), 2, 22, -5 + prologuey);
			RenderTextOnScreen(meshList[GEO_TEXT], "Welcome to...", Color(1, 1, 1), 2, 22, -10 + prologuey);
			RenderTextOnScreen(meshList[GEO_TEXT], "SCAMMER TYCOON!", Color(1, 1, 1), scaletitle, 22, 20);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 4, 20, 11, 5);
			RenderTextOnScreen(meshList[GEO_TEXT], "Skip", Color(1, 1, 1), 2, 2, 18);
		}

		if (NPCInteract == true)
		{
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 20, 40, 10);
			RenderTextOnScreen(meshList[GEO_TEXT], Dialogue, Color(1, 1, 1), 1.5, AlignX, 20);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 20, 10, 30, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], Answer1, Color(1, 1, 1), 2, 7, 9);

			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 60, 10, 30, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], Answer2, Color(1, 1, 1), 2, 47, 9);
		}
		
	}

	//UI
	{
		//TopUI
		modelStack.PushMatrix();
		RenderMeshOnScreen(meshList[GEO_TopUI], 40, 30, 16, 54, true);
		modelStack.PopMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], Manager.ConvertMoneyToSuitableAmounts(Manager.Money), Color(1, 1, 0), 3, 61.5, 51);

		if (RenderPrestige == 0)
		{
			//Small UI
			modelStack.PushMatrix();
			RenderMeshOnScreen(meshList[GEO_SideUISmall], 40, 30, 16, 54, true);
			modelStack.PopMatrix();
		}
		if (RenderPrestige == 1)
		{
			//Big UI
			modelStack.PushMatrix();
			RenderMeshOnScreen(meshList[GEO_SideUIBig], 40, 30, 16, 54, true);
			modelStack.PopMatrix();

			if (Manager.PrestigeLvl == 3)
			{
				//Max Button
				modelStack.PushMatrix();
				RenderMeshOnScreen(meshList[GEO_MaxPrestige], 40, 30, 16, 54, true);
				modelStack.PopMatrix();
			}
			else if (Manager.UpgradePrestige(false) == 0)
			{
				//Gray Upgrade Button
				modelStack.PushMatrix();
				RenderMeshOnScreen(meshList[GEO_GrayUpgrade], 40, 30, 16, 54, true);
				modelStack.PopMatrix();
			}
			else if (Manager.UpgradePrestige(false) == 1)
			{
				//Green Upgrade Button
				modelStack.PushMatrix();
				RenderMeshOnScreen(meshList[GEO_GreenUpgrade], 40, 30, 16, 54, true);
				modelStack.PopMatrix();
			}
		}

		if (RenderUI == 1)
		{
			//BotUI
			modelStack.PushMatrix();
			RenderMeshOnScreen(meshList[GEO_BotUI], 40, 30, 16, 54, true);
			modelStack.PopMatrix();

			//Text
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Store Page: " + std::to_string(PageNum), Color(1, 1, 0), 2, 30, 43);
			modelStack.PopMatrix();

			//Equipment Store
			{
				//Gray Button
				{
					if (Manager.UnlockComputer(false) == 0)
					{
						//GrayButton Left Top
						modelStack.PushMatrix();
						RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 24, 29, 24, 3, true);
						modelStack.PopMatrix();
					}
					if (Manager.UnlockPhone(false) == 0)
					{
						//GrayButton Mid Top
						modelStack.PushMatrix();
						RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 40, 29, 24, 3, true);
						modelStack.PopMatrix();
					}
					if (Manager.UnlockLuckyCat(false) == 0)
					{
						//GrayButton Right Top
						modelStack.PushMatrix();
						RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 56, 29, 24, 3, true);
						modelStack.PopMatrix();
					}
					if (Manager.UnlockMoneyPlant(false) == 0)
					{
						//GrayButton Left Bot
						modelStack.PushMatrix();
						RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 24, 16, 24, 3, true);
						modelStack.PopMatrix();
					}
				}
				//Green Button
				{
					if (Manager.UnlockComputer(false) == 1)
					{
						//GreenButton Left Top
						modelStack.PushMatrix();
						RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 24, 29, 24, 3, true);
						modelStack.PopMatrix();
					}
					if (Manager.UnlockPhone(false) == 1)
					{
						//GreenButton Mid Top
						modelStack.PushMatrix();
						RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 40, 29, 24, 3, true);
						modelStack.PopMatrix();
					}
					if (Manager.UnlockLuckyCat(false) == 1)
					{
						//GreenButton Right Top
						modelStack.PushMatrix();
						RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 56, 29, 24, 3, true);
						modelStack.PopMatrix();
					}
					if (Manager.UnlockMoneyPlant(false) == 1 )
					{
						//GreenButton Left Bot
						modelStack.PushMatrix();
						RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 24, 16, 24, 3, true);
						modelStack.PopMatrix();
					}
				}
				//Unlock
				{
					//Text
					modelStack.PushMatrix();
					RenderTextOnScreen(meshList[GEO_TEXT], "Unlock", Color(1, 0, 0), 2, 21, 28);
					RenderTextOnScreen(meshList[GEO_TEXT], "Unlock", Color(1, 0, 0), 2, 37, 28);
					RenderTextOnScreen(meshList[GEO_TEXT], "Unlock", Color(1, 0, 0), 2, 53, 28);
					RenderTextOnScreen(meshList[GEO_TEXT], "Unlock", Color(1, 0, 0), 2, 21, 15);
					modelStack.PopMatrix();
				}
				//Description
				{
					modelStack.PushMatrix();
					RenderTextOnScreen(meshList[GEO_TEXT], "Computer", Color(0.5, 0, 0.5), 1, 18, 36);
					RenderTextOnScreen(meshList[GEO_TEXT], "Income: $1/s", Color(0.5, 0, 0.5), 1, 18, 34);
					RenderTextOnScreen(meshList[GEO_TEXT], "Price: $"+Manager.ConvertMoneyToSuitableAmounts(50 + 50 * Manager.NumOfComputers() * 0.2), Color(0.5, 0, 0.5), 1, 18, 32);

					RenderTextOnScreen(meshList[GEO_TEXT], "Phone", Color(0.5, 0, 0.5), 1, 34, 36);
					RenderTextOnScreen(meshList[GEO_TEXT], "Income: $1/s", Color(0.5, 0, 0.5), 1, 34, 34);
					RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(50 + 50 * Manager.NumOfPhones() * 0.2), Color(0.5, 0, 0.5), 1, 34, 32);

					RenderTextOnScreen(meshList[GEO_TEXT], "Lucky Cat", Color(0.5, 0, 0.5), 1, 50, 36);
					RenderTextOnScreen(meshList[GEO_TEXT], "Each Equipment Income x 2 ", Color(0.5, 0, 0.5), 1, 50, 34);
					RenderTextOnScreen(meshList[GEO_TEXT], "Price: $10000, Prestige: 2", Color(0.5, 0, 0.5), 1, 50, 32);

					RenderTextOnScreen(meshList[GEO_TEXT], "Money Plant", Color(0.5, 0, 0.5), 1, 18, 23);
					RenderTextOnScreen(meshList[GEO_TEXT], "+$2/s for each equipment", Color(0.5, 0, 0.5), 1, 18, 21);
					RenderTextOnScreen(meshList[GEO_TEXT], "Price: $5000, Prestige: 1", Color(0.5, 0, 0.5), 1, 18, 19);
					modelStack.PopMatrix();
				}
			}
		}
		else if (RenderUI == 2)
		{
			//BotUI
			modelStack.PushMatrix();
			RenderMeshOnScreen(meshList[GEO_BotUI], 40, 30, 16, 54, true);
			modelStack.PopMatrix();
			//Text
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Owned Page: " + std::to_string(PageNum), Color(1, 1, 0), 2, 30, 43);
			modelStack.PopMatrix();

			//Gray Button
			{
				if (Manager.EquipArray[(PageNum - 1) * 6 + 0] == nullptr || Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 0) != 1)
				{
					//GrayButton Left Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 24, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 1] == nullptr || Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 1) != 1)
				{
					//GrayButton Mid Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 40, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 2] == nullptr || Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 2) != 1)
				{
					//GrayButton Right Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 56, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 3] == nullptr || Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 3) != 1)
				{
					//GrayButton Left Bot
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 24, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 4] == nullptr || Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 4) != 1)
				{
					//GrayButton Mid Bot
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 40, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 5] == nullptr || Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 5) != 1)
				{
					//GrayButton Right Bot
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 56, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
			}

			//Green Button
			{
				if (Manager.EquipArray[(PageNum - 1) * 6 + 0] != nullptr && Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 0) == 1)
				{
					//GreenButton Left Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 24, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 1] != nullptr && Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 1) == 1)
				{
					//GreenButton Mid Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 40, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 2] != nullptr && Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 2) == 1)
				{
					//GreenButton Right Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 56, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 3] != nullptr && Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 3) == 1)
				{
					//GreenButton Left Bot
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 24, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 4] != nullptr && Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 4) == 1)
				{
					//GreenButton Mid Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 40, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 5] != nullptr && Manager.UpgradeComputer(false, (PageNum - 1) * 6 + 5) == 1)
				{
					//GreenButton Right Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 56, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
			}
				
			//Text
			{
				//Text
				modelStack.PushMatrix();
				std::string TempText;
				for (int i = 0; i < 6; ++i)
				{
					TempText = "";
					if (Manager.EquipArray[(PageNum - 1) * 6 + i] == nullptr || Manager.EquipArray[(PageNum - 1) * 6 + i]->ComputerLvl == 0)
					{
						TempText = "Locked";
					}
					else if (Manager.UpgradeComputer(false, (PageNum - 1) * 6 + i) != 2)
					{
						TempText = "Upgrade";
					}
					else if (Manager.UpgradeComputer(false, (PageNum - 1) * 6 + i) == 2)
					{
						TempText = "Maxed";
					}
					if (i == 0)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText, Color(1, 0, 0), 2, 21, 28);
					}
					if (i == 1)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText, Color(1, 0, 0), 2, 37, 28);
					}
					if (i == 2)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText , Color(1, 0, 0), 2, 53, 28);
					}
					if (i == 3)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText, Color(1, 0, 0), 2, 21, 15);
					}
					if (i == 4)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText, Color(1, 0, 0), 2, 37, 15);
					}
					if (i == 5)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText, Color(1, 0, 0), 2, 53, 15);
					}
				}
				modelStack.PopMatrix();
			}

			//Description
			{
				modelStack.PushMatrix();
				std::string ObjName, Income;
				float Price;
				for (int i = 0; i < 6; ++i)
				{
					ObjName = Income = "";
					Price = 0;
					if (Manager.EquipArray[(PageNum - 1) * 6 + i] == nullptr || Manager.EquipArray[(PageNum - 1) * 6 + i]->ComputerLvl == 0)
					{
					}
					else
					{
						ObjName = "Computer Level " + std::to_string(Manager.EquipArray[(PageNum - 1) * 6 + i]->ComputerLvl);
						Income = "Income: $" + Manager.ConvertMoneyToSuitableAmounts(Manager.CalculateIncome((PageNum - 1) * 6 + i,1)) + "/s";
						if (Manager.EquipArray[(PageNum - 1) * 6 + i]->ComputerLvl == 1)
						{
							Price = 500 + 500 *((PageNum-1 )* 6 + i) * 0.2;
						}
						else if (Manager.EquipArray[(PageNum - 1) * 6 + i]->ComputerLvl == 2)
						{
							Price = 5000 + 5000 * ((PageNum - 1) * 6 + i) * 0.2;
						}
						else
						{
							Price = 0;
						}
						if (i == 0)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 18, 36);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 18, 34);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 18, 32);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 18, 32);
							}
						}
						if (i == 1)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 34, 36);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 34, 34);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 34, 32);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 34, 32);
							}
						}
						if (i == 2)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 50, 36);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 50, 34);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 50, 32);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 50, 32);
							}
						}
						if (i == 3)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 18, 23);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 18, 21);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 18, 19);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 18, 19);
							}
						}
						if (i == 4)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 34, 23);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 34, 21);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 34, 19);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 34, 19);
							}
						}
						if (i == 5)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 50, 23);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 50, 21);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 50, 19);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 50, 19);
							}
						}
					}
				}
				modelStack.PopMatrix();
			}
		
			//Switch for Phone and Computer
			{
				//GrayButton Top
				modelStack.PushMatrix();
				RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 22, 44, 24, 3, true);
				modelStack.PopMatrix();
				//GreenButton Bot
				modelStack.PushMatrix();
				RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 22, 41, 24, 3, true);
				modelStack.PopMatrix();
			}
		}
		else if (RenderUI == 3)
		{
			//BotUI
			modelStack.PushMatrix();
			RenderMeshOnScreen(meshList[GEO_BotUI], 40, 30, 16, 54, true);
			modelStack.PopMatrix();
			//Text
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Owned Page: " + std::to_string(PageNum), Color(1, 1, 0), 2, 30, 43);
			modelStack.PopMatrix();

			//Gray Button
			{
				if (Manager.EquipArray[(PageNum - 1) * 6 + 0] == nullptr || Manager.UpgradePhone(false, (PageNum - 1) * 6 + 0) != 1)
				{
					//GrayButton Left Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 24, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 1] == nullptr || Manager.UpgradePhone(false, (PageNum - 1) * 6 + 1) != 1)
				{
					//GrayButton Mid Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 40, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 2] == nullptr || Manager.UpgradePhone(false, (PageNum - 1) * 6 + 2) != 1)
				{
					//GrayButton Right Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 56, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 3] == nullptr || Manager.UpgradePhone(false, (PageNum - 1) * 6 + 3) != 1)
				{
					//GrayButton Left Bot
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 24, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 4] == nullptr || Manager.UpgradePhone(false, (PageNum - 1) * 6 + 4) != 1)
				{
					//GrayButton Mid Bot
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 40, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 5] == nullptr || Manager.UpgradePhone(false, (PageNum - 1) * 6 + 5) != 1)
				{
					//GrayButton Right Bot
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 56, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
			}

			//Green Button
			{
				if (Manager.EquipArray[(PageNum - 1) * 6 + 0] != nullptr && Manager.UpgradePhone(false, (PageNum - 1) * 6 + 0) == 1)
				{
					//GreenButton Left Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 24, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 1] != nullptr && Manager.UpgradePhone(false, (PageNum - 1) * 6 + 1) == 1)
				{
					//GreenButton Mid Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 40, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 2] != nullptr && Manager.UpgradePhone(false, (PageNum - 1) * 6 + 2) == 1)
				{
					//GreenButton Right Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 56, 29, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 3] != nullptr && Manager.UpgradePhone(false, (PageNum - 1) * 6 + 3) == 1)
				{
					//GreenButton Left Bot
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 24, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 4] != nullptr && Manager.UpgradePhone(false, (PageNum - 1) * 6 + 4) == 1)
				{
					//GreenButton Mid Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 40, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
				if (Manager.EquipArray[(PageNum - 1) * 6 + 5] != nullptr && Manager.UpgradePhone(false, (PageNum - 1) * 6 + 5) == 1)
				{
					//GreenButton Right Top
					modelStack.PushMatrix();
					RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 56, 16, 24, 3, true);
					modelStack.PopMatrix();
				}
			}

			//Text
			{
				//Text
				modelStack.PushMatrix();
				std::string TempText;
				for (int i = 0; i < 6; ++i)
				{
					TempText = "";
					if (Manager.EquipArray[(PageNum - 1) * 6 + i] == nullptr || Manager.EquipArray[(PageNum - 1) * 6 + i]->PhoneLvl == 0)
					{
						TempText = "Locked";
					}
					else if (Manager.UpgradePhone(false, (PageNum - 1) * 6 + i) != 2)
					{
						TempText = "Upgrade";
					}
					else if (Manager.UpgradePhone(false, (PageNum - 1) * 6 + i) == 2)
					{
						TempText = "Maxed";
					}
					if (i == 0)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText, Color(1, 0, 0), 2, 21, 28);
					}
					if (i == 1)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText, Color(1, 0, 0), 2, 37, 28);
					}
					if (i == 2)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText, Color(1, 0, 0), 2, 53, 28);
					}
					if (i == 3)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText, Color(1, 0, 0), 2, 21, 15);
					}
					if (i == 4)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText, Color(1, 0, 0), 2, 37, 15);
					}
					if (i == 5)
					{
						RenderTextOnScreen(meshList[GEO_TEXT], TempText, Color(1, 0, 0), 2, 53, 15);
					}
				}
				modelStack.PopMatrix();
			}


			//Description
			{
				modelStack.PushMatrix();
				std::string ObjName, Income;
				float Price;
				for (int i = 0; i < 6; ++i)
				{
					ObjName = Income = "";
					Price = 0;
					if (Manager.EquipArray[(PageNum - 1) * 6 + i] == nullptr || Manager.EquipArray[(PageNum - 1) * 6 + i]->PhoneLvl == 0)
					{
					}
					else
					{
						ObjName = "Phone Level " + std::to_string(Manager.EquipArray[(PageNum - 1) * 6 + i]->PhoneLvl);
						Income = "Income: $" + Manager.ConvertMoneyToSuitableAmounts(Manager.CalculateIncome((PageNum - 1) * 6 + i,2)) + "/s";
						if (Manager.EquipArray[(PageNum - 1) * 6 + i]->PhoneLvl == 1)
						{
							Price = 250 + 250 * ((PageNum - 1) * 6 + i) * 0.2;
						}
						else if (Manager.EquipArray[(PageNum - 1) * 6 + i]->PhoneLvl == 2)
						{
							Price = 1250 + 1250 * ((PageNum - 1) * 6 + i) * 0.2;
						}
						else
						{
							Price = 0;
						}
						if (i == 0)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 18, 36);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 18, 34);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 18, 32);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 18, 32);
							}
						}
						if (i == 1)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 34, 36);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 34, 34);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 34, 32);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 34, 32);
							}
						}
						if (i == 2)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 50, 36);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 50, 34);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 50, 32);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 50, 32);
							}
						}
						if (i == 3)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 18, 23);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 18, 21);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 18, 19);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 18, 19);
							}
						}
						if (i == 4)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 34, 23);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 34, 21);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 34, 19);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 34, 19);
							}
						}
						if (i == 5)
						{
							RenderTextOnScreen(meshList[GEO_TEXT], ObjName, Color(0.5, 0, 0.5), 1, 50, 23);
							RenderTextOnScreen(meshList[GEO_TEXT], Income, Color(0.5, 0, 0.5), 1, 50, 21);
							if (Price != 0)
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: $" + Manager.ConvertMoneyToSuitableAmounts(Price), Color(0.5, 0, 0.5), 1, 50, 19);
							}
							else
							{
								RenderTextOnScreen(meshList[GEO_TEXT], "Price: N/A", Color(0.5, 0, 0.5), 1, 50, 19);
							}	
						}
					}
				}
				modelStack.PopMatrix();
			}

			//Switch for Phone and Computer
			{
				//GrayButton Bot
				modelStack.PushMatrix();
				RenderMeshOnScreen(meshList[GEO_GRAYBUTTON], 22, 41, 24, 3, true);
				modelStack.PopMatrix();
				//GreenButton Top
				modelStack.PushMatrix();
				RenderMeshOnScreen(meshList[GEO_GREENBUTTON], 22, 44, 24, 3, true);
				modelStack.PopMatrix();
			}
		}
		if (RenderUI == 2 || RenderUI == 3)
		{
			//Computer Text
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Phone", Color(1, 0, 0), 1.5, 19, 40);
			modelStack.PopMatrix();
			//Phone Text
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Computer", Color(1, 0, 0), 1.5, 19, 43);
			modelStack.PopMatrix();
		}
	}

	if (questions == true)
	{
		if (OP1 == true && OP1check == false)
		{
			RenderMeshOnScreen(meshList[GEO_Screen], 40, 30, 16, 54, true);
			RenderMeshOnScreen(meshList[GEO_op1], 55, 30, 16, 54, true);
		}
		else if (OP2 == true && OP2check == false)
		{
			RenderMeshOnScreen(meshList[GEO_Screen], 40, 30, 16, 54, true);
			RenderMeshOnScreen(meshList[GEO_op2], 55, 30, 16, 54, true);
		}
		else if (OP3 == true && OP3check == false)
		{
			RenderMeshOnScreen(meshList[GEO_Screen], 40, 30, 16, 54, true);
			RenderMeshOnScreen(meshList[GEO_op3], 55, 30, 16, 54, true);
		}
		else if (POP1 == true && OP1check == false)
		{
			RenderMeshOnScreen(meshList[GEO_Screen], 40, 30, 16, 54, true);
			RenderMeshOnScreen(meshList[GEO_PREop1], 55, 30, 16, 54, true);
		}
		else if (POP2 == true && OP1check == false)
		{
			RenderMeshOnScreen(meshList[GEO_Screen], 40, 30, 16, 54, true);
			RenderMeshOnScreen(meshList[GEO_PREop2], 55, 30, 16, 54, true);
		}
		else if (POP3 == true && OP1check == false)
		{
			RenderMeshOnScreen(meshList[GEO_Screen], 40, 30, 16, 54, true);
			RenderMeshOnScreen(meshList[GEO_PREop3], 55, 30, 16, 54, true);
		}
		else
		{

		}
	}

	


	if (PuzzleActive == true)
	{
		PuzzleRender();
	}
	
}

void Splevel1::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(cposx, 0, -9979 + cposz);
	modelStack.Scale(20000, 20000, 20000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(cposx, 0, 9979 + cposz);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(20000, 20000, 20000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-9979 + cposx, 0, cposz);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(20000, 20000, 20000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(9979 + cposx, 0, cposz);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(20000, 20000, 20000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(cposx, 9979, cposz);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(20000, 20000, 20000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(cposx, -9979, cposz);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(20000, 20000, 20000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(9000, 10, 9000);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y + 800, light[0].position.z);
	modelStack.Rotate(180, 0, 180, 180);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(180, 0, 1, 1);
	modelStack.Scale(5, 5, 5);
	RenderText(meshList[GEO_TEXT], "Hello world", Color(0, 1, 0));
	modelStack.PopMatrix();

	
}

void Splevel1::RenderWorkStation(int WorkStation)
{
	//Render WorkStation
	if (Manager.EquipArray[WorkStation] != nullptr)
	{
		//Render WorkStation
		{
			//Render Worker
			modelStack.PushMatrix();
			modelStack.Translate(15, 5, 15);
			modelStack.Scale(5, 5, 5);
			RenderMesh(meshList[GEO_Body], false);
			{

				RenderMesh(meshList[GEO_Head], false);
				{
					modelStack.PushMatrix();
					modelStack.Translate(0, 3, 0);
					modelStack.Rotate(-90, 0, 0, 1);
					modelStack.Rotate(spinD, 0, 1, 0);
					modelStack.Scale(1, 1, 1);
					RenderMesh(meshList[GEO_Arms], false);
					modelStack.PopMatrix();
				}
				//Render Desk and Equipment
				modelStack.PushMatrix();
				modelStack.Rotate(90, 0, 1, 0);
				modelStack.Scale(1, 1.5, 1);
				modelStack.Translate(0, -0.5, 2.2);
				RenderMesh(meshList[GEO_Table], false);
				{
					modelStack.PushMatrix();
					if (Manager.EquipArray[WorkStation]->ComputerLvl == 1)
					{
						modelStack.Translate(0, 2.05, 0);
						modelStack.Rotate(90, 0, 1, 0);
						modelStack.Scale(0.4, 0.3, 0.7);
						RenderMesh(meshList[GEO_Laptop], true);//Render Laptop 
					}
					else if (Manager.EquipArray[WorkStation]->ComputerLvl == 2)
					{
						modelStack.Translate(0, 2.05, 0);
						modelStack.Rotate(90, 0, 1, 0);
						modelStack.Scale(0.4, 0.3, 0.7);
						RenderMesh(meshList[GEO_Laptop2], true); //Render Laptop 2
					}
					else if (Manager.EquipArray[WorkStation]->ComputerLvl == 3)
					{
						modelStack.Translate(0, 2.05, 0);
						modelStack.Rotate(90, 0, 1, 0);
						modelStack.Scale(0.4, 0.3, 0.7);
						RenderMesh(meshList[GEO_Laptop3], true); //Render Laptop 3
					}
					modelStack.PopMatrix();

					modelStack.PushMatrix();
					if (Manager.EquipArray[WorkStation]->PhoneLvl == 1)
					{
						modelStack.Translate(1, 2.1, -0.4);
						modelStack.Rotate(90, 0, 1, 0);
						modelStack.Rotate(90, 1, 0, 0);
						modelStack.Scale(0.4, 0.3, 0.6);
						RenderMesh(meshList[GEO_Phone1], true); //Render Phone 1
					}
					else if (Manager.EquipArray[WorkStation]->PhoneLvl == 2)
					{
						modelStack.Translate(1, 2.2, -0.4);
						modelStack.Rotate(90, 0, 1, 0);
						modelStack.Rotate(90, 1, 0, 0);
						modelStack.Scale(0.4, 0.3, 0.6);
						RenderMesh(meshList[GEO_Phone2], true); //Render Phone 2
					}
					else if (Manager.EquipArray[WorkStation]->PhoneLvl == 3)
					{
						modelStack.Translate(0, 3.7, -0.4);
						modelStack.Rotate(90, 0, 1, 0);
						modelStack.Rotate(90, 1, 0, 0);
						modelStack.Scale(0.4, 0.3, 0.6);
						RenderMesh(meshList[GEO_Phone3], true); //Render Phone 3
					}
					modelStack.PopMatrix();
				}
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
		}
	}
}

void Splevel1::RenderName(int Lvl)
{
	int XPos, YPos, ZPos;
	XPos = YPos = ZPos = 0;
	for (int i = (Lvl-1)*6; i < Lvl * 6; ++i)
	{
		if (Manager.EquipArray[i] != nullptr)
		{
			if (i < 6)
			{
				YPos = 0;
			}
			else if (i < 12)
			{
				YPos = 50;
			}
			else if (i < 18)
			{
				YPos = 100;
			}
			XPos = -75;
			if (i % 6 == 0)
			{
				ZPos = 40;
			}
			else if (i % 6 == 1)
			{
				ZPos = 20;
			}
			else if (i % 6 == 2)
			{
				ZPos = 0;
			}
			else if (i % 6 == 3)
			{
				ZPos = -30;
			}
			else if (i % 6 == 4)
			{
				ZPos = -50;
			}
			else if (i % 6 == 5)
			{
				ZPos = -70;
			}
			modelStack.PushMatrix();
			modelStack.Scale(1, 1, 1);
			modelStack.Translate(XPos, YPos, ZPos);
			{
				modelStack.PushMatrix();
				modelStack.Scale(2, 2, 2);
				modelStack.Rotate(90, 0, 1, 0);
				modelStack.Translate(-10, 20, 10);
				RenderText(meshList[GEO_TEXT], NameList[i + 18], Color(1, 1, 1));
				{
					modelStack.PushMatrix();
					modelStack.Translate(0, 2, 0);
					RenderText(meshList[GEO_TEXT], NameList[i], Color(1, 1, 1));
					modelStack.PopMatrix();
				}
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
		}
	}
}

void Splevel1::PuzzleRender()
{
	//Luke
	//Renderfunc for puzzle minigame
	RenderMeshOnScreen(meshList[GEO_Puzzlebgbg], 40, 25, 80, 80);
	RenderMeshOnScreen(meshList[GEO_Puzzlebg], 40, 25, 40, 40);

	RenderMeshOnScreen(meshList[GEO_PuzzleBorder], puzzle.Border->position.x, puzzle.Border->position.y, 11, 11);

	for (int i = 0; i < 10; i++)
	{
		RenderMeshOnScreen(meshList[GEO_PuzzlePaper], puzzle.Paper[i]->actlposition.x, puzzle.Paper[i]->actlposition.y, 3, 3);
	}

	RenderMeshOnScreen(meshList[GEO_PuzzlePlayer], puzzle.playeractualpox, (puzzle.playeractualpoy), 3, 3);

	RenderTextOnScreen(meshList[GEO_TEXT], "Time left: "+ std::to_string(puzzletimer), Color(1, 1, 1), 2, 3, 50);
}

void Splevel1::UpdatePuzzleControls()
{
	//Update Func for Puzzle minigame
	static bool bLButtonState = false;
	if (Application::IsMousePressed(0))
	{
		bLButtonState = true;

		//Converting Viewport space to UI space
		double x, y;
		Application::GetCursorPos(&x, &y);
		unsigned w = Application::GetWindowWidth();
		unsigned h = Application::GetWindowHeight();
		float posX = (x / w) * 80; //convert (0,800) to (0,80)
		float posY = 60 - (y / h) * 60; //convert (600,0) to (0,60)
		
		posY -= 3;

		//player
		if (puzzle.ispickupsomthing == false)
		{
			if ((posY <= (puzzle.playeractualpoy + 1.5) && posY >= (puzzle.playeractualpoy - 1.5)) && (posX >= (puzzle.playeractualpox - 2) && posX <= (puzzle.playeractualpox + 2))) //Clck Store
			{
				puzzle.ispickupsomthing = true;
				PuzzlePlayerPickup = true;
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					if ((posY <= (puzzle.Paper[i]->actlposition.y + 1.5) && posY >= (puzzle.Paper[i]->actlposition.y - 1.5)) && (posX >= (puzzle.Paper[i]->actlposition.x - 2) && posX <= (puzzle.Paper[i]->actlposition.x + 2)))
					{
						if (puzzle.Paper[i]->actlposition.x > (puzzle.playeractualpox - 6) && (puzzle.Paper[i]->actlposition.x < (puzzle.playeractualpox + 6))
							&& (puzzle.Paper[i]->actlposition.y > (puzzle.playeractualpoy - 6) && (puzzle.Paper[i]->actlposition.y < (puzzle.playeractualpoy + 6))))
						{
							puzzle.ispickupsomthing = true;
							puzzle.Paper[i]->pickupstatus = true;
							break;
						}
					}
				}
			}
		}

		//checking
		if (PuzzlePlayerPickup == true)
		{

			puzzle.playeractualpox = posX;
			puzzle.playeractualpoy = posY;
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{

				if (puzzle.Paper[i]->pickupstatus == true)
				{
					puzzle.Paper[i]->actlposition.x = posX;
					puzzle.Paper[i]->actlposition.y = posY;
					break;
				}
			}
		}
	}
	else if (bLButtonState == true && !Application::IsMousePressed(0))
	{
		bLButtonState = false;

		double x, y;
		Application::GetCursorPos(&x, &y);
		unsigned w = Application::GetWindowWidth();
		unsigned h = Application::GetWindowHeight();
		float posX = (x / w) * 80; //convert (0,800) to (0,80)
		float posY = 60 - (y / h) * 60; //convert (600,0) to (0,60)


		if (PuzzlePlayerPickup == true)
		{
			puzzle.ispickupsomthing = false;
			PuzzlePlayerPickup = false;

			bool spottaken = false;

			posY -= 3;

			posX -= 2;

			int resultx = posX + 4 / 2;
			resultx -= resultx % 4;

			puzzle.playeractualpox = (resultx + 2);

			//boundary
			if (puzzle.playeractualpox < 22)
			{
				puzzle.playeractualpox = 22;
			}
			else if (puzzle.playeractualpox > 58)
			{
				puzzle.playeractualpox = 58;
			}
			

			int resulty = posY + 4 / 2;
			resulty -= resulty % 4;

			puzzle.playeractualpoy = (resulty - 1);

			//boundary
			if (puzzle.playeractualpoy < 7)
			{
				puzzle.playeractualpoy = 7;
			}
			else if (puzzle.playeractualpoy > 43)
			{
				puzzle.playeractualpoy = 43;
			}

			//colison
			for (int i = 0; i < 10; i++)
			{
				if (puzzle.playeractualpox == puzzle.Paper[i]->actlposition.x && puzzle.playeractualpoy == puzzle.Paper[i]->actlposition.y)
				{
					spottaken = true;
					
					puzzle.playeractualpox = puzzle.Player->prevposition.x;
					puzzle.playeractualpoy = puzzle.Player->prevposition.y;

				}
			}

			if (spottaken == false)
			{
				puzzle.Player->prevposition.x = puzzle.playeractualpox;
				puzzle.Player->prevposition.y = puzzle.playeractualpoy;

				puzzle.Border->position.x = puzzle.playeractualpox;
				puzzle.Border->position.y = puzzle.playeractualpoy;

				PlaySound(TEXT("WOW.wav"), NULL, SND_ASYNC);
				
			}

		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				if (puzzle.Paper[i]->pickupstatus == true)
				{
					puzzle.ispickupsomthing = false;
					puzzle.Paper[i]->pickupstatus = false;

					bool spottaken = false;
					

					posY -= 3;

					posX -= 2;

					int resultx = posX + 4 / 2;
					resultx -= resultx % 4;

					puzzle.Paper[i]->actlposition.x = (resultx + 2);

					//boundary
					if (puzzle.Paper[i]->actlposition.x < (puzzle.playeractualpox - 6))
					{
						puzzle.Paper[i]->actlposition.x = (puzzle.playeractualpox - 4);
					}
					else if (puzzle.Paper[i]->actlposition.x > (puzzle.playeractualpox + 6))
					{
						puzzle.Paper[i]->actlposition.x = (puzzle.playeractualpox + 4);
					}


					int resulty = posY + 4 / 2;
					resulty -= resulty % 4;

					puzzle.Paper[i]->actlposition.y = (resulty - 1);

					//boundary
					if (puzzle.Paper[i]->actlposition.y < (puzzle.playeractualpoy - 6))
					{
						puzzle.Paper[i]->actlposition.y = (puzzle.playeractualpoy - 4);
					}
					else if (puzzle.Paper[i]->actlposition.y > (puzzle.playeractualpoy + 6))
					{
						puzzle.Paper[i]->actlposition.y = (puzzle.playeractualpoy + 4);
					}


					if (puzzle.playeractualpox == puzzle.Paper[i]->actlposition.x && puzzle.playeractualpoy == puzzle.Paper[i]->actlposition.y)
					{
						spottaken = true;

						puzzle.Paper[i]->actlposition.x = puzzle.Paper[i]->prevposition.x;
						puzzle.Paper[i]->actlposition.y = puzzle.Paper[i]->prevposition.y;
						

					}

					if (spottaken == false)
					{
						puzzle.Paper[i]->prevposition.x = puzzle.Paper[i]->actlposition.x;
						puzzle.Paper[i]->prevposition.y = puzzle.Paper[i]->actlposition.y;

						PlaySound(TEXT("LoseMinigame.wav"), NULL, SND_ASYNC);
						
					}
					break;
				}
			}
		}
	}
}

void Splevel1::UpdateMainControls()
{
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;

		//Converting Viewport space to UI space
		double x, y;
		Application::GetCursorPos(&x, &y);
		unsigned w = Application::GetWindowWidth();
		unsigned h = Application::GetWindowHeight();
		float posX = (x / w) * 80; //convert (0,800) to (0,80)
		float posY = 60 - (y / h) * 60; //convert (600,0) to (0,60)
		if ((posY <= 59 && posY >= 53.5) && (posX >= 1.5 && posX <= 12.5)) //Clck Store
		{
			PageNum = 1;
			RenderUI = 1;
			PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
		}
		if ((posY <= 59 && posY >= 53.5) && (posX >= 15.5 && posX <= 26.5)) //Click Owned
		{
			RenderUI = 2;
			PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
		}
		if (((posY >= 46 && posY <= 49) && (posX >= 18.5 && posX <= 25.5)) && RenderUI == 3) //Top Computer clicked
		{
			RenderUI = 2;
			PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
		}
		if (((posY >= 43 && posY <= 46) && (posX >= 18.5 && posX <= 25.5)) && RenderUI == 2) //Bot Phone Clicked
		{
			RenderUI = 3;
			PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
		}
		if (RenderUI == 2 || RenderUI == 3)
		{
			if ((posY >= 46 && posY <= 48.5) && (posX >= 27.5 && posX <= 29)) //Left Button
			{
				if (PageNum != 1)
				{
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
					--PageNum;
				}
			}
			if ((posY >= 46 && posY <= 48.5) && (posX >= 50.5 && posX <= 52)) //Right Button
			{
				if (PageNum != 3)
				{
					PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
					++PageNum;
				}
			}
		}
		if (((posY >= 46 && posY <= 48.5) && (posX >= 62 && posX <= 63.5)) && RenderUI > 0) //Click Cross Button
		{
			PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			RenderUI = 0;
		}
		if (((posY >= 32 && posY <= 35.5) && (posX >= 76.5 && posX <= 78)) && RenderPrestige == 0) //Side Open Arrow Button
		{
			PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			RenderPrestige = 1;
		}
		if (((posY >= 32 && posY <= 35.5) && (posX >= 67 && posX <= 68.5)) && RenderPrestige == 1) //Side Close Arrow Button
		{
			PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			RenderPrestige = 0;
		}
		if (RenderPrestige == 1)  //Upgrade Prestige
		{
			if ((posY >= 30 && posY <= 33) && (posX >= 70 && posX <= 78))
			{
				PlaySound(TEXT("Lvlup.wav"), NULL, SND_ASYNC);
				Manager.UpgradePrestige(true);
			}
		}
		if ((posY >= 31.5 && posY <= 34) && (posX >= 20.5 && posX <= 27.5)) //Top Left Button
		{
			if (RenderUI == 1)
			{
				Manager.UnlockComputer(true);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			else if (RenderUI == 2)
			{
				Manager.UpgradeComputer(true, (PageNum - 1) * 6 + 0);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			else if (RenderUI == 3)
			{
				Manager.UpgradePhone(true, (PageNum - 1) * 6 + 0);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
		}
		if ((posY >= 31.5 && posY <= 34) && (posX >= 36.5 && posX <= 43.5)) //Top Mid Button
		{
			if (RenderUI == 1)
			{
				Manager.UnlockPhone(true);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			else if (RenderUI == 2)
			{
				Manager.UpgradeComputer(true, (PageNum - 1) * 6 + 1);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			else if (RenderUI == 3)
			{
				Manager.UpgradePhone(true, (PageNum - 1) * 6 + 1);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
		}
		if ((posY >= 31.5 && posY <= 34) && (posX >= 52.5 && posX <= 59.5)) //Top Right Button
		{
			if (RenderUI == 1)
			{
				Manager.UnlockLuckyCat(true);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			else if (RenderUI == 2)
			{
				Manager.UpgradeComputer(true, (PageNum - 1) * 6 + 2);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			else if (RenderUI == 3)
			{
				Manager.UpgradePhone(true, (PageNum - 1) * 6 + 2);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
		}
		if ((posY >= 18.5 && posY <= 21.5) && (posX >= 20.5 && posX <= 27.5)) //Bot Left Button
		{
			if (RenderUI == 1)
			{
				Manager.UnlockMoneyPlant(true);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			else if (RenderUI == 2)
			{
				Manager.UpgradeComputer(true, (PageNum - 1) * 6 + 3);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			else if (RenderUI == 3)
			{
				Manager.UpgradePhone(true, (PageNum - 1) * 6 + 3);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
		}
		if ((posY >= 18.5 && posY <= 21.5) && (posX >= 36.5 && posX <= 43.5)) //Bot Mid Button
		{
			if (RenderUI == 2)
			{
				Manager.UpgradeComputer(true, (PageNum - 1) * 6 + 4);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			else if (RenderUI == 3)
			{
				Manager.UpgradePhone(true, (PageNum - 1) * 6 + 4);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
		}
		if ((posY >= 18.5 && posY <= 21.5) && (posX >= 52.5 && posX <= 59.5)) //Bot Right Button
		{
			if (RenderUI == 2)
			{
				Manager.UpgradeComputer(true, (PageNum - 1) * 6 + 5);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
			else if (RenderUI == 3)
			{
				Manager.UpgradePhone(true, (PageNum - 1) * 6 + 5);
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
		}

		if (posX > 35 && posX < 45 && posY > 10 && posY < 20)
		{
			if (setuppolice == true)
			{
				timerstart = true;
				setuppolice = false;
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);

			}
			else if (win == true)
			{
				PlaySound(TEXT("WinMinigame.wav"), NULL, SND_ASYNC);
				Manager.MinigameBuffs += 15;
				win = false;
				timerstart = false;
				clearpolice = false;
				evidence_won_bonus = true;
			}
			else if (lose == true)
			{
				PlaySound(TEXT("LoseMinigame.wav"), NULL, SND_ASYNC);
				lose = false;
				timerstart = false;
				clearpolice = false;
				float takeaway;
				if(Manager.Money != 0) takeaway = Manager.Money / 5;
				if (Manager.Money < 0)
				{
					Manager.Money = Manager.Money + takeaway;
				}
				else Manager.Money = Manager.Money - takeaway;

			}
		}

	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
	}
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
	}
	
}

void Splevel1::UpdateCarepackage(double dt)
{
	if (carepackage->active == true)
	{
		packagetimer -= dt;
		if (packagetimer < 55)
		{
			carepackage->notitext = false;
		}
		if (packagetimer < 0)
		{
			carepackage->active = false;
		}
		if ((camera.position.x > (carepackage->position.x - 10) && camera.position.x < (carepackage->position.x +10)) && (camera.position.z > (carepackage->position.z - 10) && camera.position.z < (carepackage->position.z + 10)))
		{
			carepackage->pickuptext = true;
			if (Application::IsKeyPressed('E'))
			{
				int result = (rand() % 10) + 1;
				if (result > 5)
				{
					if (Manager.Money < 0) Manager.Money = Manager.Money / 2;
					else Manager.Money = Manager.Money * 2;
					carepackage->notitext = false;
					carepackage->pickuptext = false;
					carepackage->active = false;
					carepackage->wintext = true;
				}
				else
				{
					
					packagedie = true;
					carepackage->notitext = false;
					carepackage->pickuptext = false;
					carepackage->active = false;
					camera.target.x = camera.position.x;
					camera.target.y = 1000;
					camera.target.z = camera.position.z;
					

				}
			}
		}
		else
		{
			carepackage->pickuptext = false;
		}
	}

	if (packagedie == true)
	{
		packagetruckoffset -= 1000 * dt;

		if (packagetruckoffset < 0)
		{
			packagedie = false;
			die = true;
			packagetruckoffset = 2000;
			PlaySound(TEXT("Die.wav"), NULL, SND_ASYNC);
		}
	}

	if (carepackage->wintext == true)
	{
		carepackage->wintexttimer -= dt;
		if (carepackage->wintexttimer < 0)
		{
			carepackage->wintext = false;
			carepackage->wintexttimer = 3;
		}
	}
}

void Splevel1::RenderCarepackage()
{
	//Render func for the carepackage
	if (carepackage->active == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(carepackage->position.x, 0, carepackage->position.z);
		modelStack.Scale(10, 10, 10);

		RenderMesh(meshList[GEO_CHEST], true);
		modelStack.PopMatrix();
	}
	if (carepackage->notitext == true)
	{
		RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 15, 45, 15);
		RenderTextOnScreen(meshList[GEO_TEXT], "A ?PACKAGE? HAS DROPPED SOMEWHERE OUTSIDE!", Color(1, 1, 1), 2, 18, 15);
	}
	if (carepackage->pickuptext == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to open the ??GIFT??", Color(1, 1, 1), 3, 20, 25);
	}
	if (carepackage->wintext == true)
	{
		RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 15, 45, 15);
		RenderTextOnScreen(meshList[GEO_TEXT], "Money DOUBLED!!!", Color(1, 1, 1), 2, 22, 15);
	}
}

void Splevel1::packagedieanimation()
{
	//Death animation for the care package 
	if (packagedie == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, packagetruckoffset, camera.position.z - 10);
		modelStack.Rotate(90, 1, 0, 0);
		
		modelStack.Scale(30, 30, 30);
		RenderMesh(meshList[GEO_TRUCK], true);
		modelStack.PopMatrix();
	}
}

void Splevel1::rendermoneyfly()
{
	//Render animation for the coins falling UI
	//Number of coins is relative to the income per second 
	if (Manager.TotalIncomePerSecond > 0)
	{
		for (int i = 0; i < 10; i++)
		{
			RenderCoinsOnScreen(meshList[GEO_COIN], coinsarray[i * 2].x, coinsarray[i * 2].y, 1, 1);
		}
	}
	else if (Manager.TotalIncomePerSecond > 700 )
	{
		for (int i = 0; i < 20; i++)
		{
			RenderCoinsOnScreen(meshList[GEO_COIN], coinsarray[i].x, coinsarray[i].y, 1, 1);
		}
	}
	else if (Manager.TotalIncomePerSecond > 1400)
	{
		for (int i = 0; i < 30; i++)
		{
			RenderCoinsOnScreen(meshList[GEO_COIN], coinsarray[i].x, coinsarray[i].y, 1, 1);
		}
	}
}

void Splevel1::UpdateCoinsAnimation(double dt)
{
	//Update func for coins animation 
	coinsrotation += 3;

	for (int i = 0; i < 30; i++)
	{
		coinsarray[i].y -= (coinsarray[i].z)* dt; //z is speed
		if (coinsarray[i].y < 0)
		{
			coinsarray[i].x = (rand() % 80) + 1;
			coinsarray[i].y = 70;
		}
	}
}

void Splevel1::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED],  1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);

	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once


	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Splevel1::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
		{
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void Splevel1::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
			Mtx44 MVP = projectionStack.Top() * viewStack.Top() *
			modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST); 
}

void Splevel1::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		//Change this line inside for loop
		characterSpacing.SetToTranslation(0.5f + i * 0.5f, 0.5f, 0);
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() *
			modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
	
}

void Splevel1::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey, bool RotateX)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();//to do: scale and translate accordingly
	modelStack.Translate(x, y, 0);
	if (RotateX == true)
	{
		modelStack.Rotate(180, 0, 0, 1);
		modelStack.Rotate(180, 0, 1, 0);
	}
	modelStack.Scale(sizex, sizey, 1);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Splevel1::RenderCoinsOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();//to do: scale and translate accordingly
	modelStack.Translate(x, y, 0);

	modelStack.Rotate(coinsrotation, 0, 0, 1);
	modelStack.Rotate(coinsrotation, 0, 1, 0);
	
	modelStack.Scale(sizex, sizey, 1);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);

}

int Splevel1::Random(int range)
{
	srand(time(0));  // Initialize random number generator.
	return rand()%1 + range;
}


void Splevel1::InitName(void)
{
	std::string Temp[36] = { "Watson","Pat","Frankie","Valentine","Sidney","Wilson","Tilden","Sanford","Madison","Sid","Kirby","Peter","Maurice","Hugh","Almer","Wiley","John","Perry","Pruitt","Roger","Hayes","Parks","Flowers","Russell","Armstrong","Dillon", "Barnett","Roberson","Mays","Sims","Kelley", "Hickman","Mueller","Tyler","Cena","Johnson"};
	for (int i = 0; i < 36; ++i)
	{
		NameList[i] = Temp[i];
	}
}
