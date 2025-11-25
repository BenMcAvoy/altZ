#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

#include <optional>
#include <array>
#include <vector>
#include <string_view>

#include "vertex.h"

namespace altZ {
    const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"};

    const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    const int framesInFlight = 2;

    constexpr std::array<Vertex, 4> vertices = {
        Vertex{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        Vertex{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        Vertex{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        Vertex{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}};

    constexpr std::array<uint16_t, 6> indices = {0, 1, 2, 2, 3, 0};

    class App {
    public:
        App(int width = 800, int height = 600, std::string_view title = "altZ App");
        ~App();

        void run();

    private:
        void initWindow(int width, int height, std::string_view title);
        void initVulkan();
        void createInstance();
        void setupDebugMessenger();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createGraphicsPipeline();
        void createFramebuffers();
        void createCommandPool();
        void createCommandBuffers();
        void createSyncObjects();
        void createVertexBuffer();
        void createIndexBuffer();
        void cleanupSwapChain();
        void recreateSwapChain();
        void setupImGui();
        void checkExtensions(std::vector<const char *> &extensions);

        void mainLoop();
        void drawFrame();
        void cleanup();

        bool checkValidationLayerSupport();
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        std::vector<const char *> getRequiredExtensions();

        VkResult createDebugUtilsMessengerExt(
            VkInstance instance,
            const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
            const VkAllocationCallbacks *pAllocator,
            VkDebugUtilsMessengerEXT *pDebugMessenger);

        void destroyDebugUtilsMessengerExt(
            VkInstance instance,
            VkDebugUtilsMessengerEXT debugMessenger,
            const VkAllocationCallbacks *pAllocator);

        int rateDevice(VkPhysicalDevice device);

        struct QueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            bool isComplete() {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        struct SwapChainSupportDetails {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
        VkShaderModule createShaderModule(const std::vector<char> &code);
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        static void FramebufferResizeCallback(GLFWwindow *window, int width, int height);
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
            void *pUserData);

        std::vector<char> readFile(std::string_view filename);

        GLFWwindow *window;
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        VkSurfaceKHR surface;
        VkSwapchainKHR swapChain;
        VkFormat swapchainImageFormat;
        VkExtent2D swapchainExtent;
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        VkCommandPool commandPool;

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        VkDescriptorPool imguiDescriptorPool;
        VkClearValue clearColor = {{{0.01f, 0.01f, 0.02f, 1.0f}}};

        // VkCommandBuffer commandBuffer;
        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkImage> swapchainImages;
        std::vector<VkImageView> swapchainImageViews;

        std::vector<VkFramebuffer> swapchainFramebuffers;

        // This semaphore will signal when the image is available to render to.
        std::vector<VkSemaphore> imageAvailableSemaphores;
        // This semaphore will signal when rendering has finished and the image can be
        // presented.
        std::vector<VkSemaphore> renderFinishedSemaphores;
        // This fence will signal when the command buffer has finished executing.
        std::vector<VkFence> inFlightFences;

        bool extensionsSupported;
        bool framebufferResized = false;
        uint32_t currentFrame = 0;

        int width;
        int height;
    };
} // namespace altZ