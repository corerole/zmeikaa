#include "Instance.hpp"

static vk::ApplicationInfo get_default_ApplicationInfo() {
	vk::ApplicationInfo appInfo{};
	appInfo.sType = vk::StructureType::eApplicationInfo;
	appInfo.pApplicationName = "Hello Clowns:)";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "My app engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	return appInfo;
}

static vk::InstanceCreateInfo get_default_InstanceCreateInfo(
	std::vector<const char*>& requiredExtensions,
	std::vector<const char*>& enabledLayers,
	vk::ApplicationInfo *appInfo)
{
	vk::InstanceCreateInfo createInfo {};
	createInfo.sType = vk::StructureType::eInstanceCreateInfo;
	createInfo.pApplicationInfo = appInfo;
	createInfo.flags |= vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
	createInfo.ppEnabledLayerNames = enabledLayers.data();
	createInfo.enabledLayerCount = (uint32_t)enabledLayers.size();
	createInfo.ppEnabledExtensionNames = requiredExtensions.data();
	createInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
	return createInfo;
}

static std::vector<const char*> get_extention() {
	std::vector<const char*> requiredExtensions;
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	dbgs << "Enumerated: " << glfwExtensionCount + 1 << " glfw required extensions\n";

	for (uint32_t i = 0; i < glfwExtensionCount; i++) {
		dbgs << " " << (i+1) << " | " << glfwExtensions[i] << "\n";
		requiredExtensions.push_back(glfwExtensions[i]);
	}

	requiredExtensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	size_t beta = requiredExtensions.size() - 1;
	dbgs << " " << (beta+1) << " | " << requiredExtensions[beta] << "\n";
	return requiredExtensions;
}

static std::vector<const char*> get_layers() {
	std::vector<const char*> validationLayers;
	validationLayers.push_back("VK_LAYER_KHRONOS_validation");
	return validationLayers;
}

App_Instance::App_Instance(vk::raii::Context& context) {
	vk::ApplicationInfo appInfo = get_default_ApplicationInfo();
	std::vector<const char*> requiredExtensions = get_extention();

	std::vector<vk::LayerProperties> layerProperties = context.enumerateInstanceLayerProperties();
	uint32_t instanceVersion = context.enumerateInstanceVersion();
	std::vector<vk::ExtensionProperties> extensionProperties = context.enumerateInstanceExtensionProperties();

	std::vector<const char*> validationLayers = get_layers();

	vk::InstanceCreateInfo createInfo = get_default_InstanceCreateInfo(requiredExtensions, validationLayers, &appInfo);
	
	Instance = std::make_unique<vk::raii::Instance>(context, createInfo);
	dbgs << "Instance Created!\n";
}

vk::raii::Instance& App_Instance::get() { return *Instance; }