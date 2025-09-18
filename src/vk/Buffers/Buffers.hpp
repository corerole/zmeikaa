#ifndef APP_BUFFERS
#define APP_BUFFERS

// #include "../Shaders/Shaders.h"

#include <vulkan/vulkan_raii.hpp>
#include "../../trash/dbg.h"
#include "../Vertex/Vertex.h"
#include <memory>

#if 0
namespace vk {
	namespace supp {
		template <typename T>
		std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_buffer(
			vk::BufferUsageFlags usageflag,
			const vk::raii::Device& Device,
			const std::vector<T>& Vertices,
			const vk::raii::PhysicalDevice& PhysDevice,
			bool DeviceMapMemory2,
			vk::raii::CommandPool& CommandPool,
			const vk::raii::Queue& GraphicsQueue
		);
	} // supp
} // vk
#else
namespace {
	template <typename T>
	static inline size_t vectorsizeof(const std::vector<T>& vec) {
		return sizeof(T) * vec.size();
	}

	static inline unsigned findMemoryType(
		unsigned typeFilter,
		vk::MemoryPropertyFlags properties,
		const vk::raii::PhysicalDevice& PhysDevice
	) {
		vk::PhysicalDeviceMemoryProperties memProperties = PhysDevice.getMemoryProperties();
		dbgs << memProperties.memoryTypeCount << " memory types found\n";
		for (unsigned i = 0; i < memProperties.memoryTypeCount; ++i) {
			if ((typeFilter & (1 << i)) && ((memProperties.memoryTypes[i].propertyFlags & properties) == properties)) {
				return i;
			}
		}
		throw std::runtime_error("failed to find suitable memory type!");
	}

	static inline vk::raii::Buffer create_Buffer(
		const vk::raii::Device& Device,
		const vk::DeviceSize& bufferSize,
		const vk::BufferUsageFlags usage
	) {
		vk::BufferCreateInfo bufferInfo{};
		bufferInfo.sType = vk::StructureType::eBufferCreateInfo;
		bufferInfo.flags = vk::BufferCreateFlags();
		bufferInfo.size = bufferSize;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = vk::SharingMode::eExclusive;

		return vk::raii::Buffer(Device, bufferInfo);
	}

	static inline vk::raii::DeviceMemory create_BufferMemory(
		const vk::raii::Device& Device,
		const vk::raii::PhysicalDevice& PhysDevice,
		const vk::raii::Buffer& Buffer,
		const vk::MemoryPropertyFlags properties
	) {
		vk::MemoryRequirements memRequirements = Buffer.getMemoryRequirements();

		vk::MemoryAllocateInfo allocInfo{};
		allocInfo.sType = vk::StructureType::eMemoryAllocateInfo;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties, PhysDevice);

		vk::raii::DeviceMemory bufferMemory = Device.allocateMemory(allocInfo);

		bool bindBufferMemory2 = false;
		if (bindBufferMemory2) {
			vk::BindBufferMemoryInfo bindBufferMemoryInfo{};
			bindBufferMemoryInfo.sType = vk::StructureType::eBindBufferMemoryInfo;
			bindBufferMemoryInfo.buffer = Buffer;
			bindBufferMemoryInfo.memory = bufferMemory;
			bindBufferMemoryInfo.memoryOffset = 0;

			Device.bindBufferMemory2(bindBufferMemoryInfo);
			return bufferMemory;
		}

		VkResult res = vkBindBufferMemory(*Device, *Buffer, *bufferMemory, 0);
		VK_CHECK_RESULT(vk::Result(res));

		return bufferMemory;
	}

	static inline void copyBuffer(
		const vk::raii::Buffer& srcBuffer,
		const vk::raii::Buffer& dstBuffer,
		const vk::DeviceSize& size,
		const vk::raii::Device& Device,
		const vk::raii::CommandPool& CommandPool,
		const vk::raii::Queue& GraphicsQueue
	) {
		vk::CommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
		allocInfo.level = vk::CommandBufferLevel::ePrimary;
		allocInfo.commandPool = CommandPool;
		allocInfo.commandBufferCount = 1;

		auto CommandBuffers = Device.allocateCommandBuffers(allocInfo);
		if (CommandBuffers.empty()) {
			throw std::runtime_error("Buffer: cant allocate CommadBuffer's \n");
		}

		vk::raii::CommandBuffer& CommandBuffer = CommandBuffers[0];

		vk::CommandBufferBeginInfo beginInfo{};
		beginInfo.sType = vk::StructureType::eCommandBufferBeginInfo;
		beginInfo.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;

		CommandBuffer.begin(beginInfo);

		vk::BufferCopy copyRegion{};
		copyRegion.size = size;
		copyRegion.dstOffset = 0;
		copyRegion.srcOffset = 0;

		bool bug = 1;
		if (bug) {
			CommandBuffer.copyBuffer(srcBuffer, dstBuffer, copyRegion);
		}	else {
			uint32_t regionCount = 0;
			VkBufferCopy copyRegion2{};
			copyRegion2.size = size;
			copyRegion2.dstOffset = 0;
			copyRegion2.srcOffset = 0;
			vkCmdCopyBuffer(*CommandBuffer, *srcBuffer, *dstBuffer, regionCount, &copyRegion2);
		}

		CommandBuffer.end();

		vk::CommandBuffer cb[] = { CommandBuffer };
		vk::SubmitInfo submitInfo{};
		submitInfo.sType = vk::StructureType::eSubmitInfo;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = cb;

		GraphicsQueue.submit(submitInfo);
		GraphicsQueue.waitIdle();
	}
} // anon ns

#endif

namespace vk {
	namespace supp {
		struct BufferCreater {
			private:
				const vk::raii::Device& Device;
				const vk::raii::PhysicalDevice& PhysDevice;
				const vk::raii::CommandPool& CommandPool;
				const vk::raii::Queue& GraphicsQueue;
				bool DeviceMapMemory2 = false;
				bool is_prepeared = false;
			private:
				struct MemoryMapper {
					private:
						const vk::raii::Device& Device;
						const vk::raii::DeviceMemory& memory;
						void* data = nullptr;
					public:
						void* get_mapped() { return data; }
						MemoryMapper(
							const vk::raii::Device& Device,
							const vk::raii::DeviceMemory& memory,
							unsigned bufferSize
							) : 
							Device(Device),
							memory(memory)
						{
							VkResult res = vkMapMemory(*Device, *memory, 0, bufferSize, 0, &data);
							VK_CHECK_RESULT(vk::Result(res));
						}

						~MemoryMapper() {
							vkUnmapMemory(*Device, *memory);
						}
				};
			public:
				MemoryMapper get_MemoryMapper(const vk::raii::DeviceMemory& memory, unsigned bufferSize) {
					return MemoryMapper(Device, memory, bufferSize);
				}

			public:
				BufferCreater(
					const vk::raii::Device& Device,
					const vk::raii::PhysicalDevice& PhysDevice,
					const vk::raii::CommandPool& CommandPool,
					const vk::raii::Queue& GraphicsQueue,
					bool DeviceMapMemory2 = false
				) :
					Device(Device),
					PhysDevice(PhysDevice),
					CommandPool(CommandPool),
					GraphicsQueue(GraphicsQueue),
					DeviceMapMemory2(DeviceMapMemory2),
					is_prepeared(true)
				{
				}
#if 0
			public:
				template <typename T>
				std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_buffer(
					vk::BufferUsageFlags usageflag,
					const std::vector<T>& all
				) {
					if (!is_prepeared) {
						throw std::runtime_error("BufferCreater::get_buffer | Can't be used without init");
					}
					vk::DeviceSize bufferSize = vectorsizeof(all);

					vk::BufferUsageFlags stagingUsage = vk::BufferUsageFlagBits::eTransferSrc;
					vk::MemoryPropertyFlags stagingProperties = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;

					vk::raii::Buffer stagingBuffer = create_Buffer(Device, bufferSize, stagingUsage);
					vk::raii::DeviceMemory stagingBufferMemory = create_BufferMemory(Device, PhysDevice, stagingBuffer, stagingProperties);

					void* data = nullptr;
					{
						MemoryMapper mm(Device, stagingBufferMemory);
						void* data = mm.get_mapped();
						std::copy(all.begin(), all.end(), static_cast<T*>(data));
					}

					vk::BufferUsageFlags bufUsage = vk::BufferUsageFlagBits::eTransferDst | usageflag;
					vk::MemoryPropertyFlags bufProperties = vk::MemoryPropertyFlagBits::eDeviceLocal;
					vk::raii::Buffer lBuffer = create_Buffer(Device, bufferSize, bufUsage);
					vk::raii::DeviceMemory lBufferMemory = create_BufferMemory(Device, PhysDevice, lBuffer, bufProperties);

					copyBuffer(stagingBuffer, lBuffer, bufferSize, Device, CommandPool, GraphicsQueue);

					return std::pair<vk::raii::Buffer, vk::raii::DeviceMemory>(std::move(lBuffer), std::move(lBufferMemory));
				}
#endif 
			private:
				template <typename T>
				std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> createDeviceLocalBuffer(
					vk::BufferUsageFlags usageflag,
					const std::vector<T>& data
				) {
					if (!is_prepeared) {
						throw std::runtime_error("BufferCreater::createDeviceLocalBuffer | Can't be used without init");
					}
					vk::DeviceSize bufferSize = vectorsizeof(data);

					// Создаем staging buffer (host-visible)
					vk::BufferUsageFlags stagingUsage = vk::BufferUsageFlagBits::eTransferSrc;
					vk::MemoryPropertyFlags stagingProperties = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;

					vk::raii::Buffer stagingBuffer = create_Buffer(Device, bufferSize, stagingUsage);
					vk::raii::DeviceMemory stagingBufferMemory = create_BufferMemory(Device, PhysDevice, stagingBuffer, stagingProperties);

					{
						MemoryMapper mm(Device, stagingBufferMemory, static_cast<unsigned>(bufferSize));
						void* mappedData = mm.get_mapped();
						std::memcpy(mappedData, data.data(), bufferSize);
					}

					vk::BufferUsageFlags bufUsage = vk::BufferUsageFlagBits::eTransferDst | usageflag;
					vk::MemoryPropertyFlags bufProperties = vk::MemoryPropertyFlagBits::eDeviceLocal;
					vk::raii::Buffer deviceLocalBuffer = create_Buffer(Device, bufferSize, bufUsage);
					vk::raii::DeviceMemory deviceLocalMemory = create_BufferMemory(Device, PhysDevice, deviceLocalBuffer, bufProperties);

					copyBuffer(stagingBuffer, deviceLocalBuffer, bufferSize, Device, CommandPool, GraphicsQueue);

					return std::pair<vk::raii::Buffer, vk::raii::DeviceMemory>(std::move(deviceLocalBuffer), std::move(deviceLocalMemory));
				}

				template <typename T>
				std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> createHostVisibleBuffer(
					vk::BufferUsageFlags usageflag,
					const std::vector<T>& data,
					bool coherent = true
				) {
					if (!is_prepeared) {
						throw std::runtime_error("BufferCreater::createHostVisibleBuffer | Can't be used without init");
					}
					vk::DeviceSize bufferSize = vectorsizeof(data);
					vk::MemoryPropertyFlags properties = vk::MemoryPropertyFlagBits::eHostVisible;
					if (coherent) {
						properties |= vk::MemoryPropertyFlagBits::eHostCoherent;
					}	else {
						properties |= vk::MemoryPropertyFlagBits::eHostCached;
					}

					vk::raii::Buffer buffer = create_Buffer(Device, bufferSize, usageflag);
					vk::raii::DeviceMemory memory = create_BufferMemory(Device, PhysDevice, buffer, properties);

					if (!data.empty()) {
						MemoryMapper mm(Device, memory, static_cast<unsigned>(bufferSize));
						void* mappedData = mm.get_mapped();
						std::memcpy(mappedData, data.data(), bufferSize);

						if (!coherent) {
							vk::MappedMemoryRange range;
							range.memory = *memory;
							range.offset = 0;
							range.size = bufferSize;
							Device.flushMappedMemoryRanges(range);
						}
					}

					return std::pair<vk::raii::Buffer, vk::raii::DeviceMemory>(std::move(buffer), std::move(memory));
				}
			public:
				// 3. Staging Buffer (для передачи данных)
				template <typename T>
				std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> createStagingBuffer(
					const std::vector<T>& data
				) {
					if (!is_prepeared) {
						throw std::runtime_error("BufferCreater::createStagingBuffer | Can't be used without init");
					}
					vk::DeviceSize bufferSize = vectorsizeof(data);

					vk::BufferUsageFlags usage = vk::BufferUsageFlagBits::eTransferSrc;
					vk::MemoryPropertyFlags properties = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;

					vk::raii::Buffer buffer = create_Buffer(Device, bufferSize, usage);
					vk::raii::DeviceMemory memory = create_BufferMemory(Device, PhysDevice, buffer, properties);

					if (!data.empty()) {
						MemoryMapper mm(Device, memory, static_cast<unsigned>(bufferSize));
						void* mappedData = mm.get_mapped();
						std::memcpy(mappedData, data.data(), bufferSize);
					}

					return std::pair<vk::raii::Buffer, vk::raii::DeviceMemory>(std::move(buffer), std::move(memory));
				}

				// 4. Uniform Buffer (специализированный host-visible буфер)
				template <typename T>
				std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> createUniformBuffer(
					const std::vector<T>& data
				) {
					return createHostVisibleBuffer(
						vk::BufferUsageFlagBits::eUniformBuffer,
						data,
						true
					);
				}

				// 5. Storage Buffer (для шейдеров)
				template <typename T>
				std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> createStorageBuffer(
					const std::vector<T>& data,
					bool deviceLocal = true
				) {
					if (deviceLocal) {
						return createDeviceLocalBuffer(
							vk::BufferUsageFlagBits::eStorageBuffer | vk::BufferUsageFlagBits::eTransferDst,
							data
						);
					}	else {
						return createHostVisibleBuffer(
							vk::BufferUsageFlagBits::eStorageBuffer,
							data,
							true
						);
					}
				}

				// 6. Vertex Buffer (специализированный device-local буфер)
				template <typename T>
				std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> createVertexBuffer(
					const std::vector<T>& vertices
				) {
					return createDeviceLocalBuffer(
						vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst,
						vertices
					);
				}

				// 7. Index Buffer (специализированный device-local буфер)
				template <typename T>
				std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> createIndexBuffer(
					const std::vector<T>& indices
				) {
					return createDeviceLocalBuffer(
						vk::BufferUsageFlagBits::eIndexBuffer | vk::BufferUsageFlagBits::eTransferDst,
						indices
					);
				}

				// 8. Empty Buffer (без данных, только выделение)
				std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> createEmptyBuffer(
					vk::DeviceSize size,
					vk::BufferUsageFlags usage,
					vk::MemoryPropertyFlags properties
				) const {
					if (!is_prepeared) {
						throw std::runtime_error("BufferCreater::createEmptyBuffer | Can't be used without init");
					}

					vk::raii::Buffer buffer = create_Buffer(Device, size, usage);
					vk::raii::DeviceMemory memory = create_BufferMemory(Device, PhysDevice, buffer, properties);

					return std::pair<vk::raii::Buffer, vk::raii::DeviceMemory>(std::move(buffer), std::move(memory));
				}


		}; // BufferCreater
	} // supp
} // vk

#endif