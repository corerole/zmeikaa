#include "DepthResource.hpp"
#include <stdexcept>

namespace {
  static inline unsigned findMemoryType(
    unsigned typeFilter,
    vk::MemoryPropertyFlags properties,
    const vk::raii::PhysicalDevice& PhysDevice
  ) {
    vk::PhysicalDeviceMemoryProperties memProperties = PhysDevice.getMemoryProperties();
    for (unsigned i = 0; i < memProperties.memoryTypeCount; ++i) {
      if ((typeFilter & (1 << i)) && ((memProperties.memoryTypes[i].propertyFlags & properties) == properties)) {
        return i;
      }
    }
    return 0u;
  }
}

namespace vk {
  namespace supp {
    std::pair<vk::raii::Image, vk::raii::DeviceMemory> createDepthResources(
      const vk::raii::Device& device,
      const vk::raii::PhysicalDevice& physicalDevice,
      const vk::Extent2D& extent,
      const vk::raii::CommandPool& commandPool,
      const vk::raii::Queue& graphicsQueue
    ) {
      vk::Format depthFormat = vk::Format::eD32Sfloat;

      // Создаем image для глубины
      vk::ImageCreateInfo imageInfo{};
      imageInfo.imageType = vk::ImageType::e2D;
      imageInfo.extent.width = extent.width;
      imageInfo.extent.height = extent.height;
      imageInfo.extent.depth = 1;
      imageInfo.mipLevels = 1;
      imageInfo.arrayLayers = 1;
      imageInfo.format = depthFormat;
      imageInfo.tiling = vk::ImageTiling::eOptimal;
      imageInfo.initialLayout = vk::ImageLayout::eUndefined;
      imageInfo.usage = vk::ImageUsageFlagBits::eDepthStencilAttachment;
      imageInfo.samples = vk::SampleCountFlagBits::e1;
      imageInfo.sharingMode = vk::SharingMode::eExclusive;

      vk::raii::Image depthImage = device.createImage(imageInfo);

      // Выделяем память для image
      vk::MemoryRequirements memRequirements = depthImage.getMemoryRequirements();

      vk::MemoryAllocateInfo allocInfo{};
      allocInfo.allocationSize = memRequirements.size;
      allocInfo.memoryTypeIndex = findMemoryType(
        memRequirements.memoryTypeBits,
        vk::MemoryPropertyFlagBits::eDeviceLocal,
        physicalDevice
      );

      vk::raii::DeviceMemory depthImageMemory = device.allocateMemory(allocInfo);

      // Связываем память с image
      depthImage.bindMemory(*depthImageMemory, 0);

      return std::make_pair(std::move(depthImage), std::move(depthImageMemory));
    }

    vk::raii::ImageView createDepthImageView(
      const vk::raii::Device& device,
      const vk::raii::Image& depthImage
    ) {
      vk::ImageViewCreateInfo viewInfo{};
      viewInfo.image = *depthImage;
      viewInfo.viewType = vk::ImageViewType::e2D;
      viewInfo.format = vk::Format::eD32Sfloat;
      viewInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;
      viewInfo.subresourceRange.baseMipLevel = 0;
      viewInfo.subresourceRange.levelCount = 1;
      viewInfo.subresourceRange.baseArrayLayer = 0;
      viewInfo.subresourceRange.layerCount = 1;

      return vk::raii::ImageView(device, viewInfo);
    }
  }
}