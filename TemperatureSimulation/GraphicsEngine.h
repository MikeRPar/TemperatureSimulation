#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <optional>
#include <fstream>

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

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
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

//Struct type for storing Queue Family Indices
struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

//Struct type for storing Swap chain support details
struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

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
		VkSurfaceKHR surface;
		VkSwapchainKHR swapChain;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device; //Logical device

		VkQueue graphicsQueue;
		VkQueue presentQueue;

		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		std::vector<VkImageView> swapChainImageViews;

		VkRenderPass renderPass;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;

		std::vector<VkFramebuffer> swapChainFramebuffers;

		VkCommandPool commandPool;
		VkCommandBuffer commandBuffer;

		VkSemaphore imageAvailableSemaphore;
		VkSemaphore renderFinishedSemaphore;
		VkFence inFlightFence;

		//SET UP FUNCTIONS
		void initVulkan();
		void initWindow();
		void createInstance();
		void createSurface();
		void createSwapChain();
		void createImageViews();
		void createRenderPass();
		void createGraphicsPipeline();
		void createFramebuffers();
		void createCommandPool();
		void createCommandBuffer();
		void createSyncObjects();
		void setupDebugMessenger();

		//Physical Device Selection
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

		//Logical Device Creation
		void createLogicalDevice();

		//Swapchain & Surface
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		//Shaders
		static std::vector<char> readFile(const std::string& filename);
		VkShaderModule createShaderModule(const std::vector<char>& code);

		//Command recording
		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

		//Detail Checking
		void printOptionalExtensions();
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		
		
		//Debug creation helper
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		void mainLoop();

		void drawFrame();

		void cleanup();
};

#endif

