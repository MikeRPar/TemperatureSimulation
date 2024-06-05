#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#define DEFAULT_NAME "Graphics Window"
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

//Program Version Details
#define PROGRAM_MAJOR 1
#define PROGRAM_MINOR 0
#define PROGRAM_PATCH 0

//Engine Version Details
#define ENGINE_MAJOR 1
#define ENGINE_MINOR 0
#define ENGINE_PATCH 0

class GraphicsEngine {
	public:
		GraphicsEngine();
		GraphicsEngine(const char* name);
		void run();
	private:
		//PRIVATE CLASS MEMBERS
		GLFWwindow* window;
		char* windowName; //Should not change during runtime, can't make const though

		VkInstance instance; 

		//SET UP FUNCTIONS
		void initVulkan();
		void initWindow();
		void createInstance();

		//Detail Checking
		void printOptionalExtensions();

		void mainLoop();
		void cleanup();
};

#endif

