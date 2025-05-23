#include "Swapchain.hpp"

template <typename T>
static T myclamp(T x, T low, T hi) {
	if (x > hi)
		return hi;
	if (x < low)
		return low;
	return x;
}

vk::raii::SwapchainKHR& App_Swapchain::get() {
	return *Swapchain;
}

vk::SurfaceFormatKHR& App_Swapchain::get_SurfaceFormatKHR() {
	return SurfaceFormat;
}

vk::Extent2D& App_Swapchain::get_Extent2D() {
	return Extent;
}

static vk::PresentModeKHR create_PresentModeKHR(vk::raii::PhysicalDevice& PhysDevice, vk::raii::SurfaceKHR& Surface) {
	std::vector<vk::PresentModeKHR> presentModes = PhysDevice.getSurfacePresentModesKHR(Surface);
	unsigned presentModeCount = (unsigned)presentModes.size();


	dbgs << presentModeCount << " presentation modes found\n";

	if (presentModeCount == 0) {
		throw std::runtime_error("No presentation modes supported");
	}

	vk::PresentModeKHR presentMode = vk::PresentModeKHR::eFifo;

	if ((std::find(presentModes.begin(), presentModes.end(), (vk::PresentModeKHR::eFifo))) != presentModes.end()) {
		dbgs << "VK_PRESENT_MODE_FIFO_KHR found\n";
	} else {
		dbgs << "VK_PRESENT_MODE_FIFO_KHR not found, found following:\n";
		for (auto m : presentModes) {
			dbgs << "\t" << ((VkPresentModeKHR)(m)) << std::endl;
			presentMode = m;
		}
		dbgs << "Using mode: " << ((VkPresentModeKHR)(presentMode)) << std::endl;
	}

	return presentMode;
}

vk::SurfaceFormatKHR create_SurfaceFormatKHR(vk::raii::PhysicalDevice& PhysDevice, vk::raii::SurfaceKHR& Surface) {
	vk::SurfaceFormatKHR SurfaceFormat;
	std::vector<vk::SurfaceFormatKHR> formats = PhysDevice.getSurfaceFormatsKHR(Surface);
	uint32_t format_count = (uint32_t)formats.size();
	dbgs << format_count << " physical device surface formats found\n";

	SurfaceFormat = formats[0];
	auto lmbd = [](const auto& f) {
		bool fst = (f.format == vk::Format::eB8G8R8A8Srgb);
		bool snd = (f.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear);
		return (fst && snd);
	};
	auto res = std::find_if(formats.begin(), formats.end(), lmbd);

	if (res != formats.end()) {
		dbgs << "B8G8R8A8_SRGB available\n";
		SurfaceFormat = *res;
	}
	return SurfaceFormat;
}

vk::Extent2D create_Extent2D(vk::raii::PhysicalDevice& PhysDevice, vk::raii::SurfaceKHR& Surface, App_Window& Wnd) {
	vk::SurfaceCapabilitiesKHR capabilities = PhysDevice.getSurfaceCapabilitiesKHR(Surface);
	vk::Extent2D Extent;

	FramebufferSize fbs = Wnd.getFramebufferSize();
	unsigned width = fbs.getWidth();
	unsigned height = fbs.getHeight();

	Extent.width = myclamp(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
	Extent.height = myclamp(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
	dbgs << "Extent: W = " << Extent.width << "; H = " << Extent.height << std::endl;

	return Extent;
}

std::unique_ptr<vk::raii::SwapchainKHR> create_Swapchain(vk::raii::Device& Device,
	vk::raii::PhysicalDevice& PhysDevice,
	vk::raii::SurfaceKHR& Surface,
	App_QueueFamily& qFamily,
	vk::SurfaceFormatKHR& SurfaceFormat,
	vk::Extent2D& Extent)
{
	unsigned GraphicsFamily = qFamily.get_GraphicsFamily();
	unsigned PresentFamily = qFamily.get_PresentFamily();

	unsigned queueFamilyIndices[] = { GraphicsFamily, PresentFamily };
	vk::SurfaceCapabilitiesKHR capabilities = PhysDevice.getSurfaceCapabilitiesKHR(Surface);
	vk::PresentModeKHR presentMode = create_PresentModeKHR(PhysDevice, Surface);

	dbgs << "Image count: min = " << capabilities.minImageCount << "; max = " << capabilities.maxImageCount << std::endl;

	unsigned ImageCount = capabilities.minImageCount + 1;
	if (capabilities.maxImageCount > 0 && ImageCount > capabilities.maxImageCount) {
		ImageCount = capabilities.maxImageCount;
	}

	dbgs << "Capability image count: " << ImageCount << std::endl;

	vk::SwapchainCreateInfoKHR createInfo{};
	createInfo.sType = vk::StructureType::eSwapchainCreateInfoKHR;
	createInfo.flags = vk::SwapchainCreateFlagsKHR();
	createInfo.surface = Surface;
	createInfo.minImageCount = ImageCount;
	createInfo.imageFormat = SurfaceFormat.format;
	createInfo.imageColorSpace = SurfaceFormat.colorSpace;
	createInfo.imageExtent = Extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;

	if (GraphicsFamily != PresentFamily) {
		createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
		dbgs << "Graphics != Present, peeking concurrent mode\n";
	} else {
		createInfo.imageSharingMode = vk::SharingMode::eExclusive;
		dbgs << "Graphics == Present, peeking exclusive mode\n";
	}

	createInfo.preTransform = capabilities.currentTransform;
	createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	// createInfo.oldSwapchain = ;

	return std::make_unique<vk::raii::SwapchainKHR>(Device, createInfo);
}

void App_Swapchain::update_Swapchain() {
	Extent = create_Extent2D(PhysicalDevice, Surface, Wnd);
	SurfaceFormat = create_SurfaceFormatKHR(PhysicalDevice, Surface);
	Swapchain = create_Swapchain(Device, PhysicalDevice, Surface, qFamily, SurfaceFormat, Extent);
}

App_Swapchain::App_Swapchain(vk::raii::PhysicalDevice& PhysicalDevice_,
	vk::raii::SurfaceKHR& Surface_,
	App_Window& Wnd_,
	vk::raii::Device& Device_,
	App_QueueFamily& qFamily_ ) : 
	PhysicalDevice(PhysicalDevice_),
	Surface(Surface_),
	Wnd(Wnd_),
	Device(Device_),
	qFamily(qFamily_)
{
	update_Swapchain();
	dbgs << "SwapChain Created!\n";
}