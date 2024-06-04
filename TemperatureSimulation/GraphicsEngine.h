#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#define DEFAULT_NAME "Graphics Window"
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

class GraphicsEngine {
	public:
		GraphicsEngine();
		GraphicsEngine(const char* name);
		void run();
	private:
		//PRIVATE CLASS MEMBERS
		GLFWwindow* window;
		char* windowName; //Should not change during runtime

		//SET UP FUNCTIONS
		void initVulkan();
		void initWindow();

		void mainLoop();
		void cleanup();
};

#endif

