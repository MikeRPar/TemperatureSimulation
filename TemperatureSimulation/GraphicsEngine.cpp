#include "GraphicsEngine.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string.h>
#include <cstring>
#include <stdint.h>
#include <stdexcept>
#include <vector>
#include <iostream>

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
	createInstance();
}

//Vulkan Related Functions
void GraphicsEngine::createInstance()
{
	//Application Info
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = windowName;
	appInfo.applicationVersion = VK_MAKE_VERSION(PROGRAM_MAJOR, PROGRAM_MINOR, PROGRAM_PATCH);
	appInfo.pEngineName = "No Engine"; //Using a custom implementation
	appInfo.engineVersion = VK_MAKE_VERSION(ENGINE_MAJOR, ENGINE_MINOR, ENGINE_PATCH);
	appInfo.apiVersion = VK_API_VERSION_1_0; //Select Vulkan Version

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
	{
		throw std::runtime_error("instance creation failed!");
	}
}

//Detail function helpers

//Prints optional extensions for Vulkan Instance
void GraphicsEngine::printOptionalExtensions() {
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	for (const auto& extension : extensions)
	{
		std::cout << '\t' << extension.extensionName << '\n';
	}
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
	vkDestroyInstance(instance, nullptr);

	glfwDestroyWindow(window);

	glfwTerminate();
	
	//Free class variables
	delete[] windowName;
}
