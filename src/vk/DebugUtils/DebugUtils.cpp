#include "DebugUtils.hpp"

namespace {

static VkBool32 pnfUserCallback(
		vk::DebugUtilsMessageSeverityFlagBitsEXT messegeSeverity,
		vk::DebugUtilsMessageTypeFlagsEXT messageType,
		const vk::DebugUtilsMessengerCallbackDataEXT* pCallBackData,
		void* pUserData)
{
	const vk::DebugUtilsMessengerCallbackDataEXT& data = *pCallBackData;
#if 0
	data.flags;
	data.pObjects;
	data.objectCount;
	data.pCmdBufLabels;
	data.cmdBufLabelCount;
	data.pQueueLabels;
	data.queueLabelCount;
#endif
	VkBool32 res = true;
#if 1
	dbgs << "___________________________________________";
	dbgs << "ID: " << data.messageIdNumber << " \n";
	dbgs << "MESSEGE: " << data.pMessage << " \n";
	dbgs << "-------------------------------------------";
#endif
	return res;
}

static vk::raii::DebugUtilsMessengerEXT create_Messenger(const vk::raii::Instance& instance, void* userdata)
{
	vk::DebugUtilsMessengerCreateInfoEXT createInfo(
		vk::DebugUtilsMessengerCreateFlagBitsEXT(),
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose,
		vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
		pnfUserCallback,
		userdata,
		nullptr
	);

	vk::raii::DebugUtilsMessengerEXT dum(instance, createInfo);
	return dum;

/*
	auto rCreateInfo = reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(&createInfo);
	std::string name = "vkCreateDebugUtilsMessengerEXT";
	auto f_void = instance.getProcAddr(name);
	typedef VkResult (*vkCreateDebugUtilsMessenger_PFN)(VkInstance, const VkDebugUtilsMessengerCreateInfoEXT*, const VkAllocationCallbacks*, VkDebugUtilsMessengerEXT*);
	auto f = reinterpret_cast<vkCreateDebugUtilsMessenger_PFN>(f_void);
	VkDebugUtilsMessengerEXT messenger;
	VkResult res = f(*instance, rCreateInfo, nullptr, &messenger);
	if(res != VK_SUCCESS) { std::cout << "VK DEBUG MESSENGER CREATION FAILED!\n"; }
	vk::raii::DebugUtilsMessengerEXT new_messenger(instance, messenger);
	return new_messenger;
*/
}

} // annon ns

namespace vk {
	namespace supp {
		vk::raii::DebugUtilsMessengerEXT get_DebugUtils(const vk::raii::Instance& instance) {
			return create_Messenger(instance, nullptr);
		}
	}
}


#if 0
static DebugUserData create_Userdata() {
	DebugUserData res;
	return res;
}

App_DebugUtils::App_DebugUtils(vk::raii::Instance& Instance_)
	:
	Instance(Instance_),
	userdata(nullptr),
	messenger(create_Messenger(Instance_, &userdata))
{ }
#endif