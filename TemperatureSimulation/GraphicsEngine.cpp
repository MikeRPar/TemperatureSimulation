#include "GraphicsEngine.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string.h>
#include <cstring>

void GraphicsEngine::run()
{
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}

//SECTION: SET UP FUNCTIONS

/* Default Constructor - Sets default settings
*/
GraphicsEngine::GraphicsEngine()
{	
	windowName = new char[std::strlen(DEFAULT_NAME) + 1]; 
	std::strcpy(windowName, DEFAULT_NAME);
}

/* Parameter constructor - Allow a window name to be set for the program
* Args: char* name - name of the program for window title
* Returns: GraphicsEngine object
*/
GraphicsEngine::GraphicsEngine(const char* name)
{
	windowName = new char[std::strlen(name) + 1];
	std::strcpy(windowName, name);
}

//These functions set up engine and its resources
void GraphicsEngine::initVulkan()
{

}

//Function sets up the window for the program with GLFW
void GraphicsEngine::initWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);	//Tell GLFW to not use an API for now (GLFW defaults to openGL)
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);		//Disable window resizing

	window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, windowName, nullptr, nullptr);
}

void GraphicsEngine::mainLoop()
{
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}

void GraphicsEngine::cleanup()
{
	glfwDestroyWindow(window);

	glfwTerminate();
	
	//Free class variables
	delete[] windowName;
}
