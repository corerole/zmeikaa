#include "DebugMarker.hpp"

DebugMarker::DebugMarker(const vk::raii::Device& Device_)
	:
	Device(Device_),
	setName_(nullptr),
	setTag_(nullptr)
{
	setName_ = (PFN_vkSetDebugUtilsObjectNameEXT)(Device_.getProcAddr("vkSetDebugUtilsObjectNameEXT"));
	setTag_ = (PFN_vkSetDebugUtilsObjectTagEXT)(Device_.getProcAddr("vkSetDebugUtilsObjectTagEXT"));
	cmdBegin_ = (PFN_vkCmdBeginDebugUtilsLabelEXT)(Device_.getProcAddr("vkCmdBeginDebugUtilsLabelEXT"));
	cmdEnd_ = (PFN_vkCmdEndDebugUtilsLabelEXT)(Device_.getProcAddr("vkCmdEndDebugUtilsLabelEXT"));
	cmdInsert_ = (PFN_vkCmdInsertDebugUtilsLabelEXT)(Device_.getProcAddr("vkCmdInsertDebugUtilsLabelEXT"));
	setObjectMap();
}

void DebugMarker::setObjectMap() {
	std::map<std::type_index, vk::ObjectType> objectMap_ = {
		{ std::type_index(typeid(vk::raii::Instance)), vk::ObjectType::eInstance },
		{ std::type_index(typeid(vk::raii::PhysicalDevice)), vk::ObjectType::ePhysicalDevice },
		{ std::type_index(typeid(vk::raii::Device)), vk::ObjectType::eDevice },
		{ std::type_index(typeid(vk::raii::Queue)), vk::ObjectType::eQueue },
		{ std::type_index(typeid(vk::raii::Semaphore)), vk::ObjectType::eSemaphore },
		{ std::type_index(typeid(vk::raii::CommandBuffer)), vk::ObjectType::eCommandBuffer },
		{ std::type_index(typeid(vk::raii::Fence)), vk::ObjectType::eFence },
		{ std::type_index(typeid(vk::raii::DeviceMemory)), vk::ObjectType::eDeviceMemory },
		{ std::type_index(typeid(vk::raii::Buffer)), vk::ObjectType::eBuffer },
		{ std::type_index(typeid(vk::raii::Image)), vk::ObjectType::eImage },
		{ std::type_index(typeid(vk::raii::Event)), vk::ObjectType::eEvent },
		{ std::type_index(typeid(vk::raii::QueryPool)), vk::ObjectType::eQueryPool },
		{ std::type_index(typeid(vk::raii::BufferView)), vk::ObjectType::eBufferView },
		{ std::type_index(typeid(vk::raii::ImageView)), vk::ObjectType::eImageView },
		{ std::type_index(typeid(vk::raii::ShaderModule)), vk::ObjectType::eShaderModule },
		{ std::type_index(typeid(vk::raii::PipelineCache)), vk::ObjectType::ePipelineCache },
		{ std::type_index(typeid(vk::raii::PipelineLayout)), vk::ObjectType::ePipelineLayout },
		{ std::type_index(typeid(vk::raii::RenderPass)), vk::ObjectType::eRenderPass },
		{ std::type_index(typeid(vk::raii::Pipeline)), vk::ObjectType::ePipeline },
		{ std::type_index(typeid(vk::raii::DescriptorSetLayout)), vk::ObjectType::eDescriptorSetLayout },
		{ std::type_index(typeid(vk::raii::Sampler)), vk::ObjectType::eSampler },
		{ std::type_index(typeid(vk::raii::DescriptorPool)), vk::ObjectType::eDescriptorPool },
		{ std::type_index(typeid(vk::raii::DescriptorSet)), vk::ObjectType::eDescriptorSet },
		{ std::type_index(typeid(vk::raii::Framebuffer)), vk::ObjectType::eFramebuffer },
		{ std::type_index(typeid(vk::raii::CommandPool)), vk::ObjectType::eCommandPool },
		{ std::type_index(typeid(vk::raii::SurfaceKHR)), vk::ObjectType::eSurfaceKHR },
		{ std::type_index(typeid(vk::raii::SwapchainKHR)), vk::ObjectType::eSwapchainKHR },
	};
	objectMap = objectMap_;
}

template<typename T>
vk::ObjectType DebugMarker::getObjectType(const T& data) { // const std::type_info& typeInfo) {
	return objectMap[data];
};

#if 0
vk::ObjectType DebugMarker::getObjectType(const std::type_info& typeInfo) {
	if (typeid(vk::raii::Instance) == typeInfo) { return vk::ObjectType::eInstance; }
	if (typeid(vk::raii::PhysicalDevice) == typeInfo) {	return vk::ObjectType::ePhysicalDevice; }
	if (typeid(vk::raii::Device) == typeInfo) { return vk::ObjectType::eDevice; }
	if (typeid(vk::raii::Queue) == typeInfo) { return vk::ObjectType::eQueue; }
	if (typeid(vk::raii::Semaphore) == typeInfo) { return vk::ObjectType::eSemaphore; }
	if (typeid(vk::raii::CommandBuffer) == typeInfo) { return vk::ObjectType::eCommandBuffer; }
	if (typeid(vk::raii::Fence) == typeInfo) { return vk::ObjectType::eFence; }
	if (typeid(vk::raii::DeviceMemory) == typeInfo) { return vk::ObjectType::eDeviceMemory; }
	if (typeid(vk::raii::Buffer) == typeInfo) { return vk::ObjectType::eBuffer; }
	if (typeid(vk::raii::Image) == typeInfo) { return vk::ObjectType::eImage; }
	if (typeid(vk::raii::Event) == typeInfo) { return vk::ObjectType::eEvent; }
	if (typeid(vk::raii::QueryPool) == typeInfo) { return vk::ObjectType::eQueryPool; }
	if (typeid(vk::raii::BufferView) == typeInfo) { return vk::ObjectType::eBufferView; }
	if (typeid(vk::raii::ImageView) == typeInfo) { return vk::ObjectType::eImageView; }
	if (typeid(vk::raii::ShaderModule) == typeInfo) { return vk::ObjectType::eShaderModule; }
	if (typeid(vk::raii::PipelineCache) == typeInfo) { return vk::ObjectType::ePipelineCache; } 
	if (typeid(vk::raii::PipelineLayout) == typeInfo) { return vk::ObjectType::ePipelineLayout; }
	if (typeid(vk::raii::RenderPass) == typeInfo) { return vk::ObjectType::eRenderPass ; }
	if (typeid(vk::raii::Pipeline) == typeInfo) { return vk::ObjectType::ePipeline; }
	if (typeid(vk::raii::DescriptorSetLayout) == typeInfo) { return vk::ObjectType::eDescriptorSetLayout; }
	if (typeid(vk::raii::Sampler) == typeInfo) { return vk::ObjectType::eSampler; }
	if (typeid(vk::raii::DescriptorPool) == typeInfo) { return vk::ObjectType::eDescriptorPool; }
	if (typeid(vk::raii::DescriptorSet) == typeInfo) { return vk::ObjectType::eDescriptorSet; }
	if (typeid(vk::raii::Framebuffer) == typeInfo) { return vk::ObjectType::eFramebuffer; }
	if (typeid(vk::raii::CommandPool) == typeInfo) { return vk::ObjectType::eCommandPool; }
	if (typeid(vk::raii::SurfaceKHR) == typeInfo) { return vk::ObjectType::eSurfaceKHR; }
	if (typeid(vk::raii::SwapchainKHR) == typeInfo) { return vk::ObjectType::eSwapchainKHR; }

	return vk::ObjectType::eUnknown;
}
#endif 


template <typename T>	bool DebugMarker::setName(T& vkObject, const std::string& name) {
	return setName<T>(vkObject, name.c_str());
}

template <typename T>	bool DebugMarker::setName(T& vkObject, const char* name) {
	if (!setName_) { return false; }
	auto objectType = getObjectType(typeid(T));
	if (objectType == vk::ObjectType::eUnknown) { return false; }
	setName(reinterpret_cast<uint64_t>(vkObject), objectType, name);
	return true;
}

void DebugMarker::setName(uint64_t object, vk::ObjectType objectType, const char* name) {
	if (!setName_) { return; }
	vk::DebugUtilsObjectNameInfoEXT nameInfo{};
	nameInfo.sType = vk::StructureType::eDebugUtilsObjectNameInfoEXT;
	nameInfo.objectType = objectType;
	nameInfo.objectHandle = object;
	nameInfo.pObjectName = name;
	auto res = reinterpret_cast<VkDebugUtilsObjectNameInfoEXT*>((&nameInfo));
	setName_(*Device, res);
}

void DebugMarker::setTag(uint64_t object, vk::ObjectType objectType) {
	if (!setTag_) { return; }
	vk::DebugUtilsObjectTagInfoEXT tagInfo{};
	tagInfo.sType = vk::StructureType::eDebugUtilsObjectTagInfoEXT;
	tagInfo.objectType = objectType;
	tagInfo.objectHandle = object;
	auto res = reinterpret_cast<VkDebugUtilsObjectTagInfoEXT*>((&tagInfo));
	setTag_(*Device, res);
}

void DebugMarker::cmdLabelBegin(vk::raii::CommandBuffer& cmd, const std::string& name, std::array<float, 4> color) {
	if (!cmdBegin_) { return; }
	vk::DebugUtilsLabelEXT info{};
	info.sType = vk::StructureType::eDebugUtilsLabelEXT; // VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
	info.pLabelName = name.c_str();
	info.color = color; // { color[0], color[1], color[2], color[3] };
	auto res = reinterpret_cast<VkDebugUtilsLabelEXT*>((&info));
	cmdBegin_(*cmd, res);
}

void DebugMarker::cmdLabelEnd(vk::raii::CommandBuffer& cmd) {
	if (!cmdEnd_) { return; }
	cmdEnd_(*cmd);
}

void DebugMarker::cmdLabelInsert(vk::raii::CommandBuffer& cmd, const std::string& name, std::array<float, 4> color) {
	if (!cmdInsert_) { return; }
	vk::DebugUtilsLabelEXT info{};
	info.sType = vk::StructureType::eDebugUtilsLabelEXT;
	info.pLabelName = name.c_str();
	info.color = color;
	auto res = reinterpret_cast<VkDebugUtilsLabelEXT*>((&info));
	cmdInsert_(*cmd, res);
}