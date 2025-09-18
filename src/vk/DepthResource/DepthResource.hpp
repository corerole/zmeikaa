#pragma once
#ifndef DEPTHRESOURCE
#define DEPTHRESOURCE

#include <vulkan/vulkan_raii.hpp>

namespace vk {
	namespace supp {
    std::pair<vk::raii::Image, vk::raii::DeviceMemory> createDepthResources(
      const vk::raii::Device& device,
      const vk::raii::PhysicalDevice& physicalDevice,
      const vk::Extent2D& extent,
      const vk::raii::CommandPool& commandPool,
      const vk::raii::Queue& graphicsQueue
    );

    vk::raii::ImageView createDepthImageView(
      const vk::raii::Device& device,
      const vk::raii::Image& depthImage
    );

	}
}

#endif