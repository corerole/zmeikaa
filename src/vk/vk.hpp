#ifndef App_VK
#define App_VK

#ifndef ANALYZE
#define ANALYZE 1
#endif

#include "../Window/Window.hpp"
#include <random>

#include "Instance/Instance.hpp"
#include "DebugUtils/DebugUtils.hpp"
#include "DebugUtils/DebugMarker/DebugMarker.hpp"
#include "Surface/Surface.hpp"
#include "PhysicalDevice/PhysicalDevice.hpp"
#include "QueueFamilies/QueueFamilies.hpp"
#include "LogicalDevice/LogicalDevice.hpp"
#include "LogicalQueues/LogicalQueue.hpp"
#include "Swapchain/Swapchain.hpp"
#include "ImageViews/ImageViews.hpp"
#include "RenderPass/RenderPass.hpp"
#include "DepthResource/DepthResource.hpp"
#include "Shaders/Shaders.hpp"
#include "PipeLines/PipeLines.hpp"
#include "Shaders/vkCube/vkCube.hpp"
#include "Framebuffers/Framebuffers.hpp"
#include "CommandPool/CommandPool.hpp"
#include "Buffers/Buffers.hpp"
#include "CommandBuffers/CommandBuffers.hpp"
#include "SyncObjects/SyncObjects.hpp"
#include "Renderer/Renderer.hpp"


constexpr int MAX_FRAMES_IN_FLIGHT = 2;

void run_vk(App_Window& Wnd);
void error_callback(int, const char* err_str);

#endif