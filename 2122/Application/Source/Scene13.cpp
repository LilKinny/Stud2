#include <iostream>
#include <string>
#include "Scene13.h"
#include "GL\glew.h"
#include "LoadTGA.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "EquipmentManager.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include <string>
#include "Light.h"

#include "Material.h"
#include <cstdlib>
#include <GLFW/glfw3.h>
EquipmentManager Manager;
using namespace std;
float scalex, countdown = 0, counterPlus, counterMinue, carmove;;
bool transition, stage2, stage3, rotatebackk = true, taxi, popo, truck;
int spinDD = 0;

string transitiontoscene;
Scene13::Scene13()
{
}

Scene13::~Scene13()
{
}
void Scene13::Init()
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
	/*m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader");
	*/m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Blending.fragmentshader");
	//m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Texture.fragmentshader");
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
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID,"numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] =glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID,"textColor");

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


	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_NUMLIGHTS], 5);

	//Replace previous code
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 0.5;
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
	light[1].power = 0.5;
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
	light[2].power = 0.5;
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
	light[3].power = 0.5;
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
	light[4].power = 0.5;
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


	for (int i = 0; i < 50; i++)
	{
		scalevall[i] = (rand() % 60) + 60;
	}

	for (int i = 0; i < 50; i++)
	{
		scalevalgrasss[i] = (rand() % 20) + 10;
	}

	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);

	//variable to rotate geometry
	rotateAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(175, 50, 175), Vector3(0, 100, 0), Vector3(0, 1, 0));

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

	meshList[GEO_GRASS] = MeshBuilder::GenerateOBJMTL("model211", "OBJ//ground_grass.obj", "OBJ//ground_grass.mtl");

	meshList[GEO_GRASS_V] = MeshBuilder::GenerateOBJMTL("model211", "OBJ//grassLarge.obj", "OBJ//grassLarge.mtl");

	meshList[GEO_LVL2] = MeshBuilder::GenerateOBJMTL("modelLVL2", "OBJ//LVL2.obj", "OBJ//LVL2.mtl");
	meshList[GEO_Tree] = MeshBuilder::GenerateOBJMTL("Tree", "OBJ//TreeTall.obj", "OBJ//TreeTall.mtl");

	meshList[GEO_LVL3] = MeshBuilder::GenerateOBJMTL("modelLVL3", "OBJ//LVL3.obj", "OBJ//LVL3.mtl");
	meshList[GEO_Lift] = MeshBuilder::GenerateOBJ("modelBUIDLING", "OBJ//Elevator.obj");
	meshList[GEO_Lift]->textureID = LoadTGA("Image//Elevator.tga");
	meshList[GEO_Table] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//simple_table.obj", "OBJ//simple_table.mtl");
	meshList[GEO_Laptop] = MeshBuilder::GenerateOBJMTL("Laptop", "OBJ//Laptop.obj", "OBJ//Laptop.mtl");
	meshList[GEO_Phone1] = MeshBuilder::GenerateOBJMTL("Phone1", "OBJ//Phone1.obj", "OBJ//Phone1.mtl");
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

	meshList[GEO_GRASS3D] = MeshBuilder::GenerateOBJMTL("Grass3D", "OBJ//Grass.obj", "OBJ//Grass.mtl");
	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//LVL1_withfloor.obj", "OBJ//LVL1_withfloor.mtl");

	meshList[GEO_LBUILDING1] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//large_buildingA.obj", "OBJ//large_buildingA.mtl");
	meshList[GEO_LBUILDING2] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//large_buildingB.obj", "OBJ//large_buildingB.mtl");
	meshList[GEO_LBUILDING3] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//large_buildingD.obj", "OBJ//large_buildingD.mtl");
	meshList[GEO_SKYSCRAPER1] = MeshBuilder::GenerateOBJMTL("modelSkyScraper", "OBJ//skyscraperF.obj", "OBJ//skyscraperF.mtl");
	meshList[GEO_STREETLIGHT] = MeshBuilder::GenerateOBJMTL("streetlight", "OBJ//streetlight.obj", "OBJ//streetlight.mtl");
	meshList[GEO_ROCK] = MeshBuilder::GenerateOBJMTL("Rock", "OBJ//rock_largeB.obj", "OBJ//rock_largeB.mtl");
	meshList[GEO_HIGHHOLE] = MeshBuilder::GenerateOBJMTL("HighHole", "OBJ//HighHole.obj", "OBJ//HighHole.mtl");

	meshList[GEO_TITLEBUTTONS] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_TITLEBUTTONS]->textureID = LoadTGA("Image//TitleButton.tga");

	meshList[GEO_FADE_TO_BLACK] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_FADE_TO_BLACK]->textureID = LoadTGA("Image//BlackPane.tga");


	meshList[GEO_TITLE] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_TITLE]->textureID = LoadTGA("Image//TitleFrame.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 0), 1.f);

	

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16,16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Agency_FB.tga");
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);
}

void Scene13::Update(double dt)
{
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

	camera.Update(10*dt);
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
	static bool bLButtonState = false;

		//Converting Viewport space to UI space
		double x, y;
		Application::GetCursorPos(&x, &y);
		unsigned w = Application::GetWindowWidth();
		unsigned h = Application::GetWindowHeight();
		float posX = (x / w) * 80; //convert (0,800) to (0,80)
		float posY = 60 - (y / h) *60; //convert (600,0) to (0,60)
		if (!bLButtonState && Application::IsMousePressed(0))
		{
			if (posX > 30 && posX < 50 && posY > 24 && posY < 40)
			{
				transition = true;
				PlaySound(TEXT("ButtonSound.wav"), NULL, SND_ASYNC);
			}
		}

	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
	}
	if (scalex < 20 && transition == true)
	{
		scalex = scalex + 0.25;
		Sleep(10);
	}
	if (scalex >= 10)
	{
		Sleep(50);
		
	}


	if (countdown >= 150) counterMinue = true;
	if (counterMinue == true) countdown = countdown - 1;
	if (countdown <= 0) counterMinue = false;
	if (counterMinue == false) countdown = countdown + 1;
	if (countdown >= 50) stage2 = true;
	else stage2 = false;
	if (countdown >= 100) stage3 = true;
	else stage3 = false;


	if (rotatebackk == false)
	{
		spinDD += 300;
	}
	if (rotatebackk == true)
	{
		spinDD -= -300;
	}
	if (rotateAngle >= 45) rotatebackk = true;
	else if (rotateAngle < 0) rotatebackk = false;
}

void Scene13::Render()
{
	
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RenderSkybox();
	//Temp variables
	Mtx44 translate, rotate, scale;
	Mtx44 MVP;
	//These will be replaced by matrix stack soon
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;

	//Set all matrices to identity
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();

	//Set view matrix using camera settings
	viewStack.LoadIdentity();
	viewStack.LookAt(

		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();



	Mtx44 mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();



	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	

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


	int randomno = rand() % 15 + 0;
	if (randomno == 1 && popo == false && truck == false && taxi == false)
	{
		taxi = true;
	}
	if (randomno == 2 && popo == false && truck == false && taxi == false)
	{
		popo = true;
	}
	if (randomno == 3 && popo == false && truck == false && taxi == false)
	{
		truck = true;
	}
	if (popo == true)
	{
		carmove += 15;
		if (carmove >= 1500)
		{
			carmove = -1500;
			popo = false;
		}
	}
	if (taxi == true)
	{
		carmove += 10;
		if (carmove >= 1500)
		{
			carmove = -1500;
			taxi = false;
		}
	}
	if (truck == true)
	{
		carmove += 8;
		if (carmove >= 1500)
		{
			carmove = -1500;
			truck = false;
		}
	}
}

void Scene13::RenderSkybox()
{


	CONST FLOAT OFFSET = 900;

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -998);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 998 + 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-998 + 0, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(998 + 0, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 998, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -998, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(9000, 10, 9000);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

	//Building
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 0);
		modelStack.Scale(10, 10, 10);
		{
			modelStack.PushMatrix();
			modelStack.Translate(6.52, 3, -7);
			modelStack.Rotate(90, 0, 0, 1);
			modelStack.Scale(1.5, 0.9, 1);
			RenderMesh(meshList[GEO_Lift], true);
			modelStack.PopMatrix();
		}
		RenderMesh(meshList[GEO_BUILDING], true);
		modelStack.PopMatrix();

		if (stage2 == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 50, 0);
			modelStack.Scale(10, 10, 10);
			{
				modelStack.PushMatrix();
				modelStack.Translate(6.52, 3, -7);
				modelStack.Rotate(90, 0, 0, 1);
				modelStack.Scale(1.5, 0.9, 1);
				RenderMesh(meshList[GEO_Lift], true);
				modelStack.PopMatrix();
			}
			RenderMesh(meshList[GEO_LVL2], true);
			modelStack.PopMatrix();
		}
		
		if (stage3 == true)
		{


			modelStack.PushMatrix();
			modelStack.Translate(0, 100, 0);
			modelStack.Scale(10, 10, 10);
			{
				modelStack.PushMatrix();
				modelStack.Translate(6.52, 3, -7);
				modelStack.Rotate(90, 0, 0, 1);
				modelStack.Scale(1.5, 0.9, 1);
				RenderMesh(meshList[GEO_Lift], true);
				modelStack.PopMatrix();
			}
			RenderMesh(meshList[GEO_LVL3], true);
			modelStack.PopMatrix();
		}
		
	}

	//Road and cars
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0.3, 250);
		modelStack.Scale(2500, 10, 80);
		RenderMesh(meshList[GEO_ROAD], true);
		modelStack.PopMatrix();

		if (taxi == true)
		{
			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Translate(-250, 0, carmove);
			modelStack.Scale(30, 30, 30);
			RenderMesh(meshList[GEO_TAXI], true);
			modelStack.PopMatrix();
		}

		if (popo == true)
		{
			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Translate(-250, 0, carmove);
			modelStack.Scale(30, 30, 30);
			RenderMesh(meshList[GEO_POLICE], true);
			modelStack.PopMatrix();
		}

		if (truck == true)
		{
			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Translate(-250, 0, carmove);
			modelStack.Scale(30, 30, 30);
			RenderMesh(meshList[GEO_TRUCK], true);
			modelStack.PopMatrix();
		}

		//modelStack.PushMatrix();
		//modelStack.Rotate (90, 0, 1, 0);
		//modelStack.Translate(-250, 0, carmove);
		//modelStack.Scale(40, 40, 40);
		//RenderMesh(meshList[GEO_TRUCK], true);
		//modelStack.PopMatrix();
	}


	/*modelStack.PushMatrix();
	modelStack.Translate(0, 30, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_CHAIR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 30, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_DART], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 30, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_DOORMAN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 30, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_SHOE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 30, 0);
	modelStack.Scale(100, 100, 100);
	RenderMesh(meshList[GEO_COTTAGE], true);
	modelStack.PopMatrix();*/

	modelStack.PushMatrix();
	modelStack.Translate(0, -50, 0);
	modelStack.Rotate(180, 0, 180, 180);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(180, 0, 1, 1);
	modelStack.Scale(5, 5, 5);
	RenderText(meshList[GEO_TEXT], "Hello world", Color(0, 1, 0));
	modelStack.PopMatrix();*/

	//Render WorkStation
	{
		//Render Worker
		modelStack.PushMatrix();
		modelStack.Translate(15, 5, 15);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_Body], false);
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_Head], false);
			{
				modelStack.PushMatrix();
				modelStack.Translate(0, 3, 0);
				modelStack.Rotate(-90, 0, 0, 1);
				modelStack.Rotate(spinDD, 0, 1, 0);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[GEO_Arms], false);
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
			//Render Desk and Equipment
			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(1, 1.5, 1);
			modelStack.Translate(0, -0.5, 2.2);
			RenderMesh(meshList[GEO_Table], false);
			{
				modelStack.PushMatrix();

					modelStack.Translate(0, 2.05, 0);
					modelStack.Rotate(90, 0, 1, 0);
					modelStack.Scale(0.4, 0.3, 0.7);
					RenderMesh(meshList[GEO_Laptop], true);//Render Laptop 

				modelStack.PopMatrix();

				modelStack.PushMatrix();

					modelStack.Translate(1, 2.2, 0);
					modelStack.Rotate(90, 0, 1, 0);
					modelStack.Rotate(90, 1, 0, 0);
					modelStack.Scale(0.4, 0.3, 0.6);
					RenderMesh(meshList[GEO_Phone1], true); //Render Phone 1
				
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	// NPC


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

	for (int x = 0; x < 4; x++)
	{
		for (int i = 0; i < 40; i++)
		{
			modelStack.PushMatrix();

			modelStack.Translate(-500 + (i * 30), 0, 320 + (x * 40));
			modelStack.Rotate(scalevall[i] * scalevall[i], 0, 1, 0);
			//modelStack.Scale(scalevall[i], scalevall[i], scalevall[i]);
			modelStack.Scale(scalevalgrasss[i], scalevalgrasss[i], scalevalgrasss[i]);

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
			modelStack.Rotate(scalevall[i] * scalevall[i], 0, 1, 0);
			//modelStack.Scale(scalevall[i], scalevall[i], scalevall[i]);
			modelStack.Scale(scalevalgrasss[i], scalevalgrasss[i], scalevalgrasss[i]);

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
			modelStack.Rotate(scalevall[i] * scalevall[i], 0, 1, 0);
			//modelStack.Scale(scalevall[i], scalevall[i], scalevall[i]);
			modelStack.Scale(scalevalgrasss[i], scalevalgrasss[i], scalevalgrasss[i]);

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
			modelStack.Rotate(scalevall[i] * scalevall[i], 0, 1, 0);
			//modelStack.Scale(scalevall[i], scalevall[i], scalevall[i]);
			modelStack.Scale(scalevalgrasss[i], scalevalgrasss[i], scalevalgrasss[i]);

			RenderMesh(meshList[GEO_GRASS3D], true);
			modelStack.PopMatrix();
		}
	}

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

	for (int i = 0; i < 30; i++)
	{

		modelStack.PushMatrix();

		modelStack.Translate(-450 + (i * 30), 0, -450);
		modelStack.Rotate(scalevall[i] * scalevall[i], 0, 1, 0);
		modelStack.Scale(scalevall[i], scalevall[i], scalevall[i]);

		RenderMesh(meshList[GEO_Tree], true);
		modelStack.PopMatrix();

	}

	for (int i = 0; i < 30; i++)
	{

		modelStack.PushMatrix();
		//modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Translate(-450 + (i * 30), 0, 450);
		modelStack.Rotate(scalevall[i] * scalevall[i], 0, 1, 0);
		modelStack.Scale(scalevall[i], scalevall[i], scalevall[i]);

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
			modelStack.Rotate(scalevall[i] * scalevall[i], 0, 1, 0);
			modelStack.Scale(scalevall[i], scalevall[i], scalevall[i]);

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
			modelStack.Rotate(scalevall[i] * scalevall[i], 0, 1, 0);
			modelStack.Scale(scalevall[i], scalevall[i], scalevall[i]);

			RenderMesh(meshList[GEO_Tree], true);
			modelStack.PopMatrix();
		}
	}

	RenderMeshOnScreen(meshList[GEO_TITLEBUTTONS], 4, 3, 2, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "PLAY", Color(0, 1, 0), 4, 36, 30);

	RenderMeshOnScreen(meshList[GEO_TITLE], 4, 5, 3, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "Scammer tycoon", Color(1, 1, 1), 4, 26, 50);
	RenderTextOnScreen(meshList[GEO_TEXT], "V1.0", Color(1, 1, 1), 2, 35, 46);
	RenderMeshOnScreen(meshList[GEO_FADE_TO_BLACK], 4, 3, scalex, scalex);

	}
void Scene13::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
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

void Scene13::Exit()
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

void Scene13::RenderText(Mesh* mesh, std::string text, Color color)
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

void Scene13::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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


void Scene13::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 8, 0, 6, -1, 1); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//to do: scale and translate accordingly

	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 0);

	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

