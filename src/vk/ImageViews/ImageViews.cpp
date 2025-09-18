#include "ImageViews.hpp"

#if 0
void App_ImageViews::update_SwapchainImages() {
	SwapchainImages.clear();
	SwapchainImages = Swapchain.getImages();
}
#endif

namespace vk {
	namespace supp {
		void set_ImageViews(
			const vk::raii::Device& Device,
			const vk::Format& SwapchainImageFormat,
			const std::vector<vk::Image>& SwapchainImages,
			std::vector<vk::raii::ImageView>& SwapchainImageViews
		) {
			SwapchainImageViews.clear();
			unsigned ImageCount = (unsigned)SwapchainImages.size();
			dbgs << "Swap chain image count " << ImageCount << std::endl;
			for (size_t i = 0; i < ImageCount; ++i) {
				vk::ImageViewCreateInfo createInfo(
					vk::ImageViewCreateFlags{},
					SwapchainImages[i],
					vk::ImageViewType::e3D,
					SwapchainImageFormat,
					{ // vk::ComponentMapping
						vk::ComponentSwizzle::eIdentity, // r
						vk::ComponentSwizzle::eIdentity, // g
						vk::ComponentSwizzle::eIdentity, // b
						vk::ComponentSwizzle::eIdentity  // a
					},
					{ // vk::ImageSubresourceRange
						vk::ImageAspectFlagBits::eColor, // aspectMask
						0, // baseMipLevel
						1, // levelCount
						0, // baseArrayLayer
						1  // layerCount
					},
					nullptr // pNext
				);
				SwapchainImageViews.emplace_back(Device, createInfo);
			}
		}
	}
}

#if 0
void App_ImageViews::update() {
	update_SwapchainImages();
	update_ImageViews();
}

App_ImageViews::App_ImageViews(vk::raii::Device &Device_,
	vk::raii::SwapchainKHR& Swapchain_,
	vk::SurfaceFormatKHR& SurfaceFormat_,
	vk::Extent2D& Extent_)
	:
	Device(Device_),
	Swapchain(Swapchain_),
	SurfaceFormat(SurfaceFormat_),
	Extent(Extent_)
{
	SwapchainExtent = Extent_;
	SwapchainImageFormat = SurfaceFormat_.format;
	update();
}

#endif