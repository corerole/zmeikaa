#include "Buffers.hpp"

#if 0
namespace vk {
	namespace supp {
		template <typename T>
		std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> BufferCreater::get_buffer(
			vk::BufferUsageFlags usageflag,
			const std::vector<T>& all
		) {
			if(!is_prepeared) {
				throw std::runtime_error("BufferCreater::get_buffer | Can't be used without init");
			}
			vk::DeviceSize bufferSize = vectorsizeof(all);

			vk::BufferUsageFlags stagingUsage = vk::BufferUsageFlagBits::eTransferSrc;
			vk::MemoryPropertyFlags stagingProperties = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;

			vk::raii::Buffer stagingBuffer = create_Buffer(Device, bufferSize, stagingUsage);
			vk::raii::DeviceMemory stagingBufferMemory = create_BufferMemory(Device, PhysDevice, stagingBuffer, stagingProperties);

			vk::MemoryMapInfo memoryMapInfo{};
			memoryMapInfo.sType = vk::StructureType::eMemoryMapInfo;
			memoryMapInfo.flags = vk::MemoryMapFlags();
			memoryMapInfo.memory = *stagingBufferMemory;
			memoryMapInfo.offset = 0;
			memoryMapInfo.size = bufferSize;

			void* data;
			if (DeviceMapMemory2) {
				data = Device.mapMemory2(memoryMapInfo);
			}	else {
				VkResult res = vkMapMemory(*Device, *stagingBufferMemory, 0, bufferSize, 0, &data);
				VK_CHECK_RESULT(vk::Result(res));
			}

			std::copy(all.begin(), all.end(), static_cast<T*>(data));

			vk::MemoryUnmapInfo memoryUnmapInfo{};
			memoryUnmapInfo.sType = vk::StructureType::eMemoryUnmapInfo;
			memoryUnmapInfo.flags = vk::MemoryUnmapFlags();
			memoryUnmapInfo.memory = *stagingBufferMemory;

			if (DeviceMapMemory2) {
				Device.unmapMemory2(memoryUnmapInfo);
			}	else {
				vkUnmapMemory(*Device, *stagingBufferMemory);
			}

			vk::BufferUsageFlags bufUsage = vk::BufferUsageFlagBits::eTransferDst | usageflag;
			vk::MemoryPropertyFlags bufProperties = vk::MemoryPropertyFlagBits::eDeviceLocal;
			vk::raii::Buffer lBuffer = create_Buffer(Device, bufferSize, bufUsage);
			vk::raii::DeviceMemory lBufferMemory = create_BufferMemory(Device, PhysDevice, lBuffer, bufProperties);

			copyBuffer(stagingBuffer, lBuffer, bufferSize, Device, CommandPool, GraphicsQueue);

			return std::pair<vk::raii::Buffer, vk::raii::DeviceMemory>(std::move(lBuffer), std::move(lBufferMemory));
		}
	} // supp
} // vk
#endif
