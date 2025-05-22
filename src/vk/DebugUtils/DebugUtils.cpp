#include "DebugUtils.hpp"

static std::unique_ptr<vk::raii::DebugUtilsMessengerEXT> create_Messenger(vk::raii::Instance& instance, void* userdata) {

	auto callback = [](
		vk::DebugUtilsMessageSeverityFlagBitsEXT messegeSeverity,
		vk::DebugUtilsMessageTypeFlagsEXT messageType,
		const vk::DebugUtilsMessengerCallbackDataEXT *pCallBackData,
		void *pUserData) -> VkBool32
	{
		VkBool32 res = true;
		const vk::DebugUtilsMessengerCallbackDataEXT	&data = *pCallBackData;
#if 0
		data.flags;
		data.pObjects;
		data.objectCount;
		data.pCmdBufLabels;
		data.cmdBufLabelCount;
		data.pQueueLabels;
		data.queueLabelCount;
#endif
		dbgs << "___________________________________________";
		dbgs << "ID: " << data.messageIdNumber << " \n";
		dbgs << "MESSEGE: " << data.pMessage << " \n";
		dbgs << "-------------------------------------------";
		return res;
	};

	vk::DebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = vk::StructureType::eDebugUtilsMessengerCreateInfoEXT;
	createInfo.flags = vk::DebugUtilsMessengerCreateFlagBitsEXT();
	createInfo.pNext = nullptr;
	createInfo.pfnUserCallback = callback;
	createInfo.messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose;
	createInfo.messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation;
	createInfo.pUserData = userdata;

#if 0
	VkDebugUtilsMessengerEXT messenger_;
	VkInstance instance_ = static_cast<VkInstance>(*instance);
	const VkDebugUtilsMessengerCreateInfoEXT* c = reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(&createInfo);
	VkResult res = vkCreateDebugUtilsMessengerEXT(instance_, c, nullptr, &messenger_);
	VK_CHECK_RESULT(vk::Result(res));
	return std::make_unique<vk::raii::DebugUtilsMessengerEXT>(instance, messenger_);// createInfo);
#else
	return std::make_unique<vk::raii::DebugUtilsMessengerEXT>(instance, createInfo);
#endif
}

static DebugUserData create_Userdata() {
	DebugUserData res;
	return res;
}

App_DebugUtils::App_DebugUtils(vk::raii::Instance& Instance_) : Instance(Instance_) {
	userdata = create_Userdata();
	messenger = create_Messenger(Instance_, &userdata);
}
