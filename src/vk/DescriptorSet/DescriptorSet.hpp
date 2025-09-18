#pragma once
#ifndef APP_DESCRIPTOR_SET
#define APP_DESCRIPTOR_SET

#include <vulkan/vulkan_raii.hpp>

#if 1

namespace vk {
	namespace supp {
		struct DescritorPoolCreator {
			private:
				const vk::raii::Device& Device;
				uint32_t maxSets = 1;
			public:
				DescritorPoolCreator(const vk::raii::Device& Device) : Device(Device) {}; 

				vk::raii::DescriptorPool create_DescriptorPool(vk::DescriptorPoolCreateFlags flags, const std::vector<vk::DescriptorPoolSize>& poolsizes) {
					vk::DescriptorPoolCreateInfo descPoolCreateInfo(flags, maxSets, poolsizes);
					return vk::raii::DescriptorPool(Device, descPoolCreateInfo);
				}

				std::vector<vk::raii::DescriptorSet> allocate_DescriptorSets(
					const vk::raii::DescriptorPool& descriptorPool,
					const vk::ArrayProxyNoTemporaries<const vk::DescriptorSetLayout>& descLayouts
				) {
					vk::DescriptorSetAllocateInfo descAllocInfo(descriptorPool, descLayouts);
					return Device.allocateDescriptorSets(descAllocInfo);
				}

				void update_DescriptorSet(const vk::ArrayProxy<const vk::WriteDescriptorSet> wds, const vk::ArrayProxy<const vk::CopyDescriptorSet>& cds) {
					Device.updateDescriptorSets(wds, cds);
				}
		};

		using DescSetLayoutGetter = vk::raii::DescriptorSetLayout (*)(const vk::raii::Device& device);
		struct DescriptorSetLayoutCreater {
			private:
				const vk::raii::Device& Device;
			public:
				DescriptorSetLayoutCreater(const vk::raii::Device& Device) : Device(Device) {};

				vk::raii::DescriptorSetLayout create_DescriptorSetLayout(DescSetLayoutGetter getter) {
					return getter(Device);
				}

		};
	}
}

#endif

#endif // !APP_DESCRIPTOR_SET
