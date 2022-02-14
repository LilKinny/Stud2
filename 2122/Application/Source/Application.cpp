
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene13.h"
#include "Splevel1.h"


GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{

}

Application::~Application()
{

}

void resize_callback(GLFWwindow* window, int w, int h)
{

	Application::m_width = w;
	Application::m_height = h;
	glViewport(0, 0, w, h); //update opengl the new window size


}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{

		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 



	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(1920, 1080, "Test Window", NULL, NULL);
	resize_callback(m_window, 1920, 1080);
	//If the window couldn't be created
	if (!m_window)
	{

		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;

	}
}

void Application::Run()
{
	Scene* scene1 = new Scene13();
	Scene* scene2 = new Splevel1();
	Scene* scene = scene1;
	scene1->Init();
	scene2->Init();
	bool changescene = false;
	float timer = 0;
	bool done = false;

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		static bool bLButtonState = false;
		
			//Converting Viewport space to UI space
			double x, y;
			Application::GetCursorPos(&x, &y);
			unsigned w = Application::GetWindowWidth();
			unsigned h = Application::GetWindowHeight();
			float posX = (x / w) * 80; //convert (0,800) to (0,80)
			float posY = 60 - (y / h) * 60; //convert (600,0) to (0,60)
			std::cout << "posX:" << posX << " , posY:" << posY << std::endl;
			if (!bLButtonState && Application::IsMousePressed(0))
		{
			if (posX > 30 && posX < 50 && posY > 24 && posY < 40)
			{
				std::cout << "Hit! transition start" << std::endl;
				changescene = true;

				//trigger user action or function
			}
			else
			{
				std::cout << "Miss!" << std::endl;
			}
		}
		if (timer < 12 && changescene == true)
		{
			timer = timer + 0.25;
			Sleep(10);
		}
		if (timer >= 12 && done == false)
		{
			Sleep(50);
			std::cout << "Change scene";
			scene = scene2;
			done = true;

		}


		scene->Update(m_timer.getElapsedTime());
		scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	scene1->Exit();
	scene2->Exit();
	delete scene1;
	delete scene2;

	scene = NULL;
}

void Application::Exit()
{


	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

unsigned Application::m_width;
unsigned Application::m_height;

bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}
void Application::GetCursorPos(double* xpos, double* ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}
int Application::GetWindowWidth()
{
	return m_width;
}
int Application::GetWindowHeight()
{
	return m_height;
}
