#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <vector>
#include <array>
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

//Program constants
#define MAX_FRAMES_IN_FLIGHT 2

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

//Struct for Vertices
struct Vertex {
	glm::vec3 pos;
	glm::vec3 color;

	static VkVertexInputBindingDescription getBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() 
	{
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
};

class GraphicsEngine {
	public:
		GraphicsEngine();
		GraphicsEngine(const char* name);
		void run();

		//Used to fill the vertex and index arrays
		void fillArrays(std::vector<Vertex>& n_vertices, std::vector<uint16_t>& n_indices);

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
		VkDescriptorSetLayout descriptorSetLayout;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;

		std::vector<VkFramebuffer> swapChainFramebuffers;

		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> commandBuffers;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		uint32_t currentFrame = 0;
		bool framebufferResized = false;

		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;

		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;
		std::vector<void*> uniformBuffersMapped;

		VkDescriptorPool descriptorPool;
		std::vector<VkDescriptorSet> descriptorSets;

		//Vertex data
		std::vector<Vertex> vertices = {}; //{
			/* cool symbol data
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
			{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},

			{{-0.2f, -0.2f, 0.0f}, {0.0f, 0.0f, 0.0f}},
			{{0.2f, -0.2f, 0.0f}, {0.0f, 0.0f, 0.0f}},
			{{0.2f, 0.2f, 0.0f}, {0.0f, 0.0f, 0.0f}},
			{{-0.2f, 0.2f, 0.0f}, {0.0f, 0.0f, 0.0f}}
			*/
		//};
		//Indices 
		std::vector<uint16_t> indices = {
			/* Cool symbol data
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
			*/
		};

		struct UniformBufferObject {
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 proj;
		};

		//SET UP FUNCTIONS
		void initVulkan();
		void initWindow();
		void createInstance();
		void createSurface();
		void createLogicalDevice();
		void createSwapChain();
		void createImageViews();
		void createRenderPass();
		void createDescriptorSetLayout();
		void createGraphicsPipeline();
		void createFramebuffers();
		void createCommandPool();
		void createVertexBuffer();
		void createIndexBuffer();
		void createUniformBuffers();
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory); //Helper
		void createDescriptorPool();
		void createDescriptorSets();
		void createCommandBuffers();
		void createSyncObjects();
		void setupDebugMessenger();

		//Physical Device Selection
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

		//Swapchain & Surface
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		//Swapchain recreation
		void recreateSwapChain();
		//Helper to remove old swap chain
		void cleanupSwapChain();
		//frame buffer resize callback, used for init window with GLFW
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
		
		//Shaders
		static std::vector<char> readFile(const std::string& filename);
		VkShaderModule createShaderModule(const std::vector<char>& code);

		//Command recording
		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

		//Detail Checking
		void printOptionalExtensions();
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		
		//Buffer helpers
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

		//used in drawframe to update uniform buffer
		void updateUniformBuffer(uint32_t currentImage);

		//Debug creation helper
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		void mainLoop();

		void drawFrame();

		void cleanup();
};

#endif

