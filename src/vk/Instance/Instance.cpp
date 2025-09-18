#include "Instance.hpp"

namespace {

static vk::ApplicationInfo get_default_ApplicationInfo(const vk::raii::Context& ctx) {
	vk::ApplicationInfo appInfo{};
	appInfo.sType = vk::StructureType::eApplicationInfo;
	appInfo.pApplicationName = "Hello Clowns:)";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 1, 1);
	appInfo.pEngineName = "My app engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 1, 1);
	appInfo.apiVersion = ctx.enumerateInstanceVersion();
	return appInfo;
}

static vk::InstanceCreateInfo get_default_InstanceCreateInfo(
	const std::vector<const char*>& requiredExtensions,
	const std::vector<const char*>& enabledLayers,
	vk::ApplicationInfo *appInfo)
{
	vk::InstanceCreateInfo createInfo{};
	createInfo.sType = vk::StructureType::eInstanceCreateInfo;
	createInfo.pApplicationInfo = appInfo;
	createInfo.flags; //|= vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
	createInfo.ppEnabledLayerNames = enabledLayers.data();
	createInfo.enabledLayerCount = (uint32_t)enabledLayers.size();
	createInfo.ppEnabledExtensionNames = requiredExtensions.data();
	createInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
	return createInfo;
}

static std::vector<const char*> get_extension() {
	std::vector<const char*> requiredExtensions;
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	// requiredExtensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	// requiredExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	for (uint32_t i = 0; i < glfwExtensionCount; i++) {
		requiredExtensions.push_back(glfwExtensions[i]);
	}

	dbgs << "Used Extension: \n";
	for(auto& x : requiredExtensions) {
		dbgs << "  " << x << "\n";
	}
	dbgs << "\n";

	return requiredExtensions;
}

static std::vector<const char*> get_layers() {
	std::vector<const char*> layersNames = {
	//	"VK_LAYER_KHRONOS_validation\0"
	};

	dbgs << "Enabled Layers:\n";
	for(auto& x : layersNames) {
		dbgs << "  " << x << "\n";
	}
	dbgs << "\n";

	return layersNames;
}

} // annon ns

namespace vk {
	namespace supp {
		vk::raii::Instance get_Instance(const vk::raii::Context& context) {
			auto extensions = get_extension();
			auto layers = get_layers();
			auto appInfo = get_default_ApplicationInfo(context);
			auto createInfo = get_default_InstanceCreateInfo(extensions, layers, &appInfo);
			return vk::raii::Instance(context, createInfo);
		}
	}
}

#if 0
static std::unique_ptr<vk::raii::Instance> get_Instance(const vk::raii::Context& ctx) {
	auto l = ;
	auto e = ;
	auto a = ;
	auto i = get_default_InstanceCreateInfo(e, l, &a);
	return ;
}
#endif

#if 0

App_Instance::App_Instance(vk::raii::Context& context)
	:
	extensions(get_extension()),
	layers(get_layers()),
	appInfo(get_default_ApplicationInfo(context)),
	createInfo(get_default_InstanceCreateInfo(extensions, layers, &appInfo)),
	Instance(std::make_unique<vk::raii::Instance>(context, createInfo))
{
	dbgs << "Instance Created!\n";
}

vk::raii::Instance& App_Instance::get() { return *Instance; }

#endif