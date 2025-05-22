#include "ImageViews.hpp"

void App_ImageViews::update_SwapchainImages() {
	SwapchainImages.clear();
	SwapchainImages = Swapchain.getImages();
}

void App_ImageViews::update_ImageViews() {
	SwapchainImageViews.clear();
	unsigned ImageCount = (unsigned)SwapchainImages.size();
	dbgs << "Swap chain image count " << ImageCount << std::endl;
	for (size_t i = 0; i < ImageCount; ++i) {
		vk::ImageViewCreateInfo createInfo{};
		createInfo.sType = vk::StructureType::eImageViewCreateInfo;
		createInfo.image = SwapchainImages[i];
		createInfo.viewType = vk::ImageViewType::e2D;
		createInfo.format = SwapchainImageFormat;
		createInfo.components.r = vk::ComponentSwizzle::eIdentity;
		createInfo.components.g = vk::ComponentSwizzle::eIdentity;
		createInfo.components.b = vk::ComponentSwizzle::eIdentity;
		createInfo.components.a = vk::ComponentSwizzle::eIdentity;
		createInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;
		SwapchainImageViews.push_back(Device.createImageView(createInfo)); // is it?
	}
}

void App_ImageViews::update() {
	update_SwapchainImages();
	update_ImageViews();
}

App_ImageViews::App_ImageViews(vk::raii::Device &Device_,
	vk::raii::SwapchainKHR& Swapchain_,
	vk::SurfaceFormatKHR& SurfaceFormat_,
	vk::Extent2D& Extent_)
	: Device(Device_), Swapchain(Swapchain_), SurfaceFormat(SurfaceFormat_), Extent(Extent_)
{
	SwapchainExtent = Extent_;
	SwapchainImageFormat = SurfaceFormat_.format;
	update();
}