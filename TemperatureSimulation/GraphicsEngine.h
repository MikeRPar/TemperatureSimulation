#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

//Validation layers are debug-only
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

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

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
								const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
								const VkAllocationCallbacks* pAllocator);

//Debug Callback Functions, cannot be in GraphicsEngine class for reasons
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData);


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
		VkDebugUtilsMessengerEXT debugMessenger;

		//SET UP FUNCTIONS
		void initVulkan();
		void initWindow();
		void createInstance();
		void setupDebugMessenger();

		//Detail Checking
		void printOptionalExtensions();
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		
		
		//Debug creation helper
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		void mainLoop();
		void cleanup();
};

#endif

