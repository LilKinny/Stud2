#include <iostream>
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

	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

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

	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);

	//variable to rotate geometry
	rotateAngle = 0;

	RenderUI = 0;
	PageNum = 1;
	//Initialize camera settings
	camera.Init(Vector3(80, 30, 50), Vector3(0, 0, 0), Vector3(0, 1, 0));

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

	meshList[GEO_GREENBUTTON] = MeshBuilder::GenerateRec("GreenButton", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_GREENBUTTON]->textureID = LoadTGA("Image//GreenButton.tga");

	meshList[GEO_GRAYBUTTON] = MeshBuilder::GenerateRec("GrayButton", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_GRAYBUTTON]->textureID = LoadTGA("Image//GrayButton.tga");

	meshList[GEO_UNLOCKTEXT] = MeshBuilder::GenerateRec("UnlockText", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_UNLOCKTEXT]->textureID = LoadTGA("Image//UnlockText.tga");

	meshList[GEO_UPGRADETEXT] = MeshBuilder::GenerateRec("UpgradeText", Color(1, 1, 1), 5.f, 1.f);
	meshList[GEO_UPGRADETEXT]->textureID = LoadTGA("Image//UpgradeText.tga");
	/*
	meshList[GEO_NYP] = MeshBuilder::GenerateQuad("nyplogo", Color(1, 1, 1), 1.f);
	meshList[GEO_NYP]->textureID = LoadTGA("Image//NYP.tga");

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1, 1, 1), 1.f);
 */
	meshList[GEO_TITLEBUTTONS] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_TITLEBUTTONS]->textureID = LoadTGA("Image//TitleButton.tga");

	meshList[GEO_TITLE] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_TITLE]->textureID = LoadTGA("Image//TitleFrame.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 0), 1.f);

	/*
	meshList[GEO_CHAIR] = MeshBuilder::GenerateOBJ("model1","OBJ//chair.obj");
	meshList[GEO_CHAIR]->textureID = LoadTGA("Image//chair.tga");

	meshList[GEO_DART] = MeshBuilder::GenerateOBJ("model1", "OBJ//dart.obj");
	meshList[GEO_DART]->textureID = LoadTGA("Image//dart.tga");

	meshList[GEO_DOORMAN] = MeshBuilder::GenerateOBJ("model1", "OBJ//doorman.obj");
	meshList[GEO_DOORMAN]->textureID = LoadTGA("Image//doorman.tga");

	meshList[GEO_SHOE] = MeshBuilder::GenerateOBJ("model1", "OBJ//shoe.obj");
	meshList[GEO_SHOE]->textureID = LoadTGA("Image//shoe.tga");

	meshList[GEO_COTTAGE] = MeshBuilder::GenerateOBJMTL("model7",
		"OBJ//cottage_obj.obj", "OBJ//cottage_obj.mtl");*/

	meshList[GEO_GRASS] = MeshBuilder::GenerateOBJMTL("model211", "OBJ//ground_grass.obj", "OBJ//ground_grass.mtl");

	meshList[GEO_GRASS_V] = MeshBuilder::GenerateOBJMTL("model211", "OBJ//grassLarge.obj", "OBJ//grassLarge.mtl");


	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJMTL("modelBUIDLING","OBJ//LVL1_withfloor.obj", "OBJ//LVL1_withfloor.mtl");
	meshList[GEO_Table] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//simple_table.obj", "OBJ//simple_table.mtl");
	/*meshList[GEO_Phone1] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//Phone1.obj", "OBJ//Phone1.mtl");*/
	/*meshList[GEO_Laptop] = MeshBuilder::GenerateOBJMTL("modelBUIDLING", "OBJ//Laptop.obj", "OBJ//Laptop.mtl");*/

	meshList[GEO_Tree] = MeshBuilder::GenerateOBJMTL("Tree", "OBJ//TreeTall.obj", "OBJ//TreeTall.mtl");

	


	meshList[GEO_PAPER] = MeshBuilder::GenerateOBJ("modelBUIDLING", "OBJ//Paper.obj");
	meshList[GEO_PAPER]->textureID = LoadTGA("Image//Notelines.tga");

	meshList[GEO_EMPTYBOX] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_EMPTYBOX]->textureID = LoadTGA("Image//TitleFrame.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16,16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Agency_FB.tga");
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
}
bool setuppolice = false, clearpolice, paper1, paper2, paper3, timerstart, win, lose;
double scaleevidence = 0.1;
float pposx, pposz, pposx2, pposz2, pposx3, pposz3, rotateangle, pposy, pposy2, pposy3, pushaway;

int mg1_start;
void Splevel1::Update(double dt)
{
	float cposx = camera.position.x;
	float cposz = camera.position.z;
	//cout << cposx;
	rotateangle = rotateangle + 0.1;
	if (setuppolice == false && clearpolice == false)
	{
		mg1_start = rand() % 300 + 1;
		/*cout << mg1_start << " , ";*/
	}
	if (mg1_start == 300 && clearpolice == false) setuppolice = true;
	if (setuppolice == true && clearpolice == false)
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
		clearpolice = true;
		
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
		if (paper1 == true && paper2 == true && paper3 == true)
		{
			win = true;
			clearpolice = false;

			paper1 = false;
			paper2 = false;
			paper3 = false;
			timerstart = false;
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

	if (camera.minigamestatus == false)
	{
		camera.Update(dt);
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
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;

		//Converting Viewport space to UI space
		double x, y;
		Application::GetCursorPos(&x, &y);
		unsigned w = Application::GetWindowWidth();
		unsigned h = Application::GetWindowHeight();
		float posX = (x / w) * 80; //convert (0,800) to (0,80)
		float posY = 60 - (y / h) *60; //convert (600,0) to (0,60)
		std::cout << "posX:" << posX << " , posY:" << posY << std::endl;
		if ((posY <= 59 && posY >= 53.5) && (posX >= 1.5 && posX <= 12.5)) //Clck Store
		{
			PageNum = 1;
			RenderUI = 1;
		}
		if ((posY <= 59 && posY >= 53.5) && (posX >= 15.5 && posX <= 26.5)) //Click Owned
		{
			PageNum = 1;
			RenderUI = 2;
		}
		if (RenderUI == 2)
		{
			if ((posY >= 46 && posY <= 48.5) && (posX >= 27.5 && posX <= 29)) //Left Button
			{
				if (PageNum != 1)
				{
					--PageNum;
				}
			}
			if ((posY >= 46 && posY <= 48.5) && (posX >= 50.5 && posX <= 52)) //Right Button
			{
				if (PageNum != 3)
				{
					++PageNum;
				}
			}
		}
		if ((posY >= 46 && posY <= 48.5) && (posX >= 62 && posX <= 63.5)) //Click Cross Button
		{
			RenderUI = 0;
		}
		if ((posY >= 32 && posY <= 35.5) && (posX >= 76.5 && posX <= 78)) //Side Open Arrow Button
		{
			RenderPrestige = 1;
		}
		if ((posY >= 32 && posY <= 35.5) && (posX >= 67 && posX <= 68.5)) //Side Close Arrow Button
		{
			RenderPrestige = 0;
		}
		if (RenderPrestige == 1)
		{
			if ((posY >= 30 && posY <= 33) && (posX >= 70 && posX <= 78))
			{
				Manager.UpgradePrestige(true);
			}
		}
		//
		if (posX > 35 && posX < 45 && posY > 8 && posY < 14)
		{
			if (setuppolice == true)
			{
				timerstart = true;
				setuppolice = false;
			}
			else if (win == true)
			{
				win = false;
			}
			else if (lose == true)
			{
				lose = false;
			}
		}
		//
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}
}

void Splevel1::Render()
{
	
	//// Render VBO here
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//RenderSkybox();
	//RenderLevel();
	////Temp variables
	//Mtx44 translate, rotate, scale;
	//Mtx44 MVP;
	////These will be replaced by matrix stack soon
	//Mtx44 model;
	//Mtx44 view;
	//Mtx44 projection;

	////Set all matrices to identity
	//translate.SetToIdentity();
	//rotate.SetToIdentity();
	//scale.SetToIdentity();
	//model.SetToIdentity();

	////Set view matrix using camera settings
	//viewStack.LoadIdentity();
	//viewStack.LookAt(

	//	camera.position.x, camera.position.y, camera.position.z,
	//	camera.target.x, camera.target.y, camera.target.z,
	//	camera.up.x, camera.up.y, camera.up.z);
	//modelStack.LoadIdentity();



	//Mtx44 mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();



	//Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	//glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	//


	//if (light[0].type == Light::LIGHT_DIRECTIONAL)
	//{
	//	Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
	//	Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
	//	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	//}
	//else if (light[0].type == Light::LIGHT_SPOT)
	//{
	//	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	//	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	//	Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
	//	glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	//}
	//else
	//{
	//	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	//	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	//}

	//modelStack.PushMatrix();
	////scale, translate, rotate

	/*------------------------------------------PREVIOUS CODE---------------------------------*/


	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	//glEnableVertexAttribArray(1);

	


	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();


	Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
	Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);

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

	

	RenderMesh(meshList[GEO_AXES], false);
	RenderSkybox();

	modelStack.PushMatrix();
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(10, 10, 10);

	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	//Render trees
	for (int i = 0; i < 30; i++)
	{
		modelStack.PushMatrix();
		//modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Translate(-450 + (i * 30), 0, -450);
		modelStack.Scale(70, 70, 70);

		RenderMesh(meshList[GEO_Tree], true);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 30; i++)
	{
		modelStack.PushMatrix();
		//modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Translate(-450 + (i * 30), 0, 450);
		modelStack.Scale(70, 70, 70);

		RenderMesh(meshList[GEO_Tree], true);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 30; i++)
	{
		modelStack.PushMatrix();
		//modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Translate(-450, 0, -450 + (i * 30));
		modelStack.Scale(70, 70, 70);

		RenderMesh(meshList[GEO_Tree], true);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 30; i++)
	{
		modelStack.PushMatrix();
		//modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Translate(450, 0, -450 + (i * 30));
		modelStack.Scale(70, 70, 70);

		RenderMesh(meshList[GEO_Tree], true);
		modelStack.PopMatrix();
	}

	//kjcode
	{
		modelStack.PushMatrix();
		modelStack.Translate(50, 0, 45);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(10, 10, 10);
		{
			modelStack.PushMatrix();
			modelStack.Translate(-1.5, 2.05, 0);
			modelStack.Rotate(90, 0, 0, 1);
			modelStack.Scale(0.5, 0.25, 0.5);
			RenderMesh(meshList[GEO_PAPER], true);
			modelStack.PopMatrix();
		}
		RenderMesh(meshList[GEO_Table], true);
		modelStack.PopMatrix();
		//Evidence mini game
		if (camera.position.x > 30 && camera.position.x < 45 &&(camera.position.z > 55 && camera.position.z <65))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to start evidence", Color(0, 1, 0), 4, 10, 30);
			if (Application::IsKeyPressed('E'))
			{
				setuppolice = true;
			}
		}
		//Laptop mini game
		if (camera.position.x > 30 && camera.position.x < 45 && (camera.position.z > 40 && camera.position.z < 55))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to start laptop", Color(0, 1, 0), 4, 10, 30);
			if (Application::IsKeyPressed('E'))
			{

			}
		}
		//Phone mini game
		if (camera.position.x > 30 && camera.position.x < 45 && (camera.position.z > 30 && camera.position.z < 40))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to start phone", Color(0, 1, 0), 4, 10, 30);
			if (Application::IsKeyPressed('E'))
			{

			}

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

		if (setuppolice == true)
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
		else if (win == true)
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
			RenderTextOnScreen(meshList[GEO_TEXT], "You didnt hide all the evidence in time", Color(1, 1, 1), 2, 23, 35);
			RenderTextOnScreen(meshList[GEO_TEXT], "The police has fined you 20% of your income", Color(1, 1, 1), 2, 22, 32);
			RenderTextOnScreen(meshList[GEO_TEXT], "Penalty: -20% of all cash", Color(1, 1, 1), 2, 24, 18);
			RenderMeshOnScreen(meshList[GEO_EMPTYBOX], 40, 10, 10, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "Pay up", Color(1, 1, 1), 2, 37, 9);
		}
	}

	//UI
	{
		//TopUI
		modelStack.PushMatrix();
		RenderMeshOnScreen(meshList[GEO_TopUI], 40, 30, 16, 54, true);
		modelStack.PopMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], Manager.ConvertMoneyToSuitableAmounts(), Color(1, 1, 0), 3, 61.5, 51);

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

			//Equipment
			//GrayButton
			modelStack.PushMatrix();
			RenderMeshOnScreen(meshList[GEO_BotUI], 40, 30, 16, 54, true);
			modelStack.PopMatrix();
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
		}
	}

	
	RenderMeshOnScreen(meshList[GEO_Puzzlebg], 30, 30, 10, 10, true);
	

	// -------------------------------------------------POSITION DEBUG----------------------------------------------
	float pox = camera.position.x;
	float poz = camera.position.z;
	RenderTextOnScreen(meshList[GEO_TEXT], "Pos X:" + std::to_string(pox), Color(1, 1, 0), 2, 0, 43);
	RenderTextOnScreen(meshList[GEO_TEXT], "Pos Z: " + std::to_string(poz), Color(1, 1, 0), 2, 0, 45);

}

void Splevel1::RenderSkybox()
{

	

	/*modelStack.PushMatrix();
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(180, 0, 180, 180);
	modelStack.Scale(500, 500, 500);
	RenderMesh(meshList[GEO_QUAD], false);
	modelStack.PopMatrix();*/


	CONST FLOAT OFFSET = 499;

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -OFFSET);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, OFFSET);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-OFFSET, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(OFFSET, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, OFFSET, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -OFFSET, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(900, 10, 900);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_GRASS], true);
	modelStack.PopMatrix();

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
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	modelStack.Rotate(180, 0, 180, 180);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_LIGHTBALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(180, 0, 1, 1);
	modelStack.Scale(5, 5, 5);
	RenderText(meshList[GEO_TEXT], "Hello world", Color(0, 1, 0));
	modelStack.PopMatrix();

	

	/*RenderMeshOnScreen(meshList[GEO_TITLEBUTTONS], 4, 3, 2, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "PLAY", Color(0, 1, 0), 2, 36, 30);

	RenderMeshOnScreen(meshList[GEO_TITLE], 4, 5, 3, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "Scammer tycoon", Color(0, 1, 0), 2, 26, 50);*/


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
