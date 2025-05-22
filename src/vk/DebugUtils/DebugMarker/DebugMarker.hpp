#ifndef APP_DEBUGMARKER
#define APP_DEBUGMARKER

#include "../../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <typeinfo>
#include <typeindex>
#include <map>

struct DebugMarker {
	private:
		std::map<std::type_index, vk::ObjectType> objectMap;
	private:
		PFN_vkSetDebugUtilsObjectNameEXT setName_;
		PFN_vkSetDebugUtilsObjectTagEXT setTag_;
		PFN_vkCmdBeginDebugUtilsLabelEXT cmdBegin_;
		PFN_vkCmdEndDebugUtilsLabelEXT cmdEnd_;
		PFN_vkCmdInsertDebugUtilsLabelEXT cmdInsert_;
	private:
		const vk::raii::Device&	Device;
		void setObjectMap();
	public:
		// vk::ObjectType getObjectType(const std::type_info& type);
		template<typename T> vk::ObjectType getObjectType(const T& data);
		DebugMarker(const vk::raii::Device& Device);
		void setName(uint64_t object, vk::ObjectType objectType, const char* name);
		template<typename T> bool setName(T& vkObject, const std::string& name);
		template<typename T> bool setName(T& vkObject, const char* name);
		void setTag(uint64_t object, vk::ObjectType objectType);
		void cmdLabelBegin(vk::raii::CommandBuffer& cmd, const std::string& name, std::array<float, 4> color);
		// void cmdLabelBegin(vk::raii::CommandBuffer& cmd, const std::string& name, std::array<float, 4> color);
		void cmdLabelEnd(vk::raii::CommandBuffer& cmd);
		void cmdLabelInsert(vk::raii::CommandBuffer& cmd, const std::string& name, std::array<float, 4> color);
};


#endif