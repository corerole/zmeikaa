#include "Buffers.hpp"

template <typename T>
static size_t vectorsizeof(const std::vector<T>& vec) {
	return sizeof(T) * vec.size();
}

#if 0
static unsigned findMemoryType(unsigned typeFilter, vk::MemoryPropertyFlags properties, vk::raii::PhysicalDevice& PhysDevice) {
	vk::PhysicalDeviceMemoryProperties2 memProperties = PhysDevice.getMemoryProperties2();
	dbgs << memProperties.memoryProperties.memoryTypeCount << " memory types found\n";
	for (unsigned i = 0; i < memProperties.memoryProperties.memoryTypeCount; ++i) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}
	throw std::runtime_error("failed to find suitable memory type!");
}
#endif

static unsigned findMemoryType(unsigned typeFilter, vk::MemoryPropertyFlags properties, vk::raii::PhysicalDevice& PhysDevice) {
	vk::PhysicalDeviceMemoryProperties memProperties = PhysDevice.getMemoryProperties();
	dbgs << memProperties.memoryTypeCount << " memory types found\n";
	for (unsigned i = 0; i < memProperties.memoryTypeCount; ++i) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}
	throw std::runtime_error("failed to find suitable memory type!");
}

static std::unique_ptr<vk::raii::Buffer> createBuffer(vk::raii::Device& Device,
	vk::DeviceSize& bufferSize,
	vk::BufferUsageFlags usage) {
	vk::BufferCreateInfo bufferInfo{};
	bufferInfo.sType = vk::StructureType::eBufferCreateInfo;
	bufferInfo.flags = vk::BufferCreateFlags();
	bufferInfo.size = bufferSize;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = vk::SharingMode::eExclusive;

	return std::make_unique<vk::raii::Buffer>(Device, bufferInfo);
}

static std::unique_ptr<vk::raii::DeviceMemory> createBufferMemory(vk::raii::Device& Device,
	vk::raii::PhysicalDevice& PhysDevice,
	vk::raii::Buffer& Buffer,
	vk::MemoryPropertyFlags properties)
{
	vk::MemoryRequirements memRequirements = Buffer.getMemoryRequirements();

	vk::MemoryAllocateInfo allocInfo{};
	allocInfo.sType = vk::StructureType::eMemoryAllocateInfo;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties, PhysDevice);

	vk::raii::DeviceMemory bufferMemory = Device.allocateMemory(allocInfo);

	vk::BindBufferMemoryInfo bindBufferMemoryInfo{};
	bindBufferMemoryInfo.sType = vk::StructureType::eBindBufferMemoryInfo;
	bindBufferMemoryInfo.buffer = Buffer;
	bindBufferMemoryInfo.memory = bufferMemory;
	bindBufferMemoryInfo.memoryOffset = 0;

	bool bindBufferMemory2 = false;
	if(bindBufferMemory2) {
		Device.bindBufferMemory2(bindBufferMemoryInfo);
		return std::make_unique<vk::raii::DeviceMemory>(std::move(bufferMemory));
	}	

	VkResult res = vkBindBufferMemory(*Device, *Buffer, *bufferMemory, 0);
	VK_CHECK_RESULT(vk::Result(res));

	return std::make_unique<vk::raii::DeviceMemory>(std::move(bufferMemory));
}

static void copyBuffer(vk::raii::Buffer& srcBuffer,
	vk::raii::Buffer& dstBuffer,
	vk::DeviceSize& size,
	vk::raii::Device& Device,
	vk::raii::CommandPool& CommandPool,
	vk::raii::Queue& GraphicsQueue)
{
	vk::CommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
	allocInfo.level = vk::CommandBufferLevel::ePrimary;
	allocInfo.commandPool = CommandPool;
	allocInfo.commandBufferCount = 1;

	std::vector<vk::raii::CommandBuffer> CommandBuffers = Device.allocateCommandBuffers(allocInfo);
	if(CommandBuffers.empty()) {
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

	bool bug = 0;
	if(!bug) {
		CommandBuffer.copyBuffer(srcBuffer, dstBuffer, copyRegion);
	} else {
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
	submitInfo.sType = vk::StructureType::eSubmitInfo; // VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = cb;

	GraphicsQueue.submit(submitInfo);
	GraphicsQueue.waitIdle();

	//vkFreeCommandBuffers((*LocalDevice), (*CommandPool), 1, &commandBuffer);
}
	
void App_Buffers::create_buffers() {
	{
		vk::DeviceSize bufferSize = vectorsizeof(Vertices);

		dbgs << "Vertex buffer size: " << bufferSize << std::endl;

		vk::BufferUsageFlags stagingUsage = vk::BufferUsageFlagBits::eTransferSrc;
		vk::MemoryPropertyFlags stagingProperties = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;

		std::unique_ptr<vk::raii::Buffer> stagingBuffer = createBuffer(Device, bufferSize, stagingUsage);
		std::unique_ptr<vk::raii::DeviceMemory> stagingBufferMemory = createBufferMemory(Device, PhysDevice, *stagingBuffer, stagingProperties);

		vk::MemoryMapInfo memoryMapInfo{};
		memoryMapInfo.sType = vk::StructureType::eMemoryMapInfo;
		memoryMapInfo.flags = vk::MemoryMapFlags();
		memoryMapInfo.memory = *stagingBufferMemory;
		memoryMapInfo.offset = 0;
		memoryMapInfo.size = bufferSize;

		void* data;
		if (DevicemapMemory2) {
			data = Device.mapMemory2(memoryMapInfo);
		}	else {
			VkResult res = vkMapMemory(*Device, *(*(stagingBufferMemory)), 0, bufferSize, 0, &data);
			VK_CHECK_RESULT(vk::Result(res));
		}

		std::copy(Vertices.begin(), Vertices.end(), static_cast<Vertex*>(data));

		vk::MemoryUnmapInfo memoryUnmapInfo{};
		memoryUnmapInfo.sType = vk::StructureType::eMemoryUnmapInfo;
		memoryUnmapInfo.flags = vk::MemoryUnmapFlags();
		memoryUnmapInfo.memory = *stagingBufferMemory;

		if (DevicemapMemory2) {
			Device.unmapMemory2(memoryUnmapInfo);
		}	else {
			vkUnmapMemory(*Device, **stagingBufferMemory);
		}

		vk::BufferUsageFlags vertexUsage = vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer;
		vk::MemoryPropertyFlags vertexProperties = vk::MemoryPropertyFlagBits::eDeviceLocal;
		VertexBuffer = createBuffer(Device, bufferSize, vertexUsage);
		VertexBufferMemory = createBufferMemory(Device, PhysDevice, *VertexBuffer, vertexProperties);

		copyBuffer(*stagingBuffer, *VertexBuffer,	bufferSize,	Device,	CommandPool, GraphicsQueue);

		stagingBuffer.reset();
		stagingBufferMemory.reset();
		// vkDestroyBuffer(Device, stagingBuffer, nullptr);
		// vkFreeMemory(Device, stagingBufferMemory, nullptr);
	}

	{
		vk::DeviceSize bufferSize = vectorsizeof(Indices);

		dbgs << "Indices buffer size: " << bufferSize << std::endl;

		vk::BufferUsageFlags stagingUsage = vk::BufferUsageFlagBits::eTransferSrc;
		vk::MemoryPropertyFlags stagingProperties = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
		std::unique_ptr<vk::raii::Buffer> stagingBuffer = createBuffer(Device, bufferSize, stagingUsage);
		std::unique_ptr<vk::raii::DeviceMemory> stagingBufferMemory = createBufferMemory(Device, PhysDevice, (*(stagingBuffer.get())), stagingProperties);

		vk::MemoryMapInfo memoryMapInfo{};
		memoryMapInfo.sType = vk::StructureType::eMemoryMapInfo;
		memoryMapInfo.flags = vk::MemoryMapFlags();
		memoryMapInfo.memory = (*(stagingBufferMemory.get()));
		memoryMapInfo.offset = 0;
		memoryMapInfo.size = bufferSize;

		void* data;
		if (DevicemapMemory2) {
			data = Device.mapMemory2(memoryMapInfo);
		}	else {
			VkResult res = vkMapMemory(*Device, *(*(stagingBufferMemory.get())), 0, bufferSize, 0, &data);
			VK_CHECK_RESULT(vk::Result(res));
		}

		std::copy(Indices.begin(), Indices.end(), static_cast<unsigned short*>(data));

		vk::MemoryUnmapInfo memoryUnmapInfo{};
		memoryUnmapInfo.sType = vk::StructureType::eMemoryUnmapInfo;
		memoryUnmapInfo.flags = vk::MemoryUnmapFlags();
		memoryUnmapInfo.memory = (*(stagingBufferMemory.get()));

		if (DevicemapMemory2) {
			Device.unmapMemory2(memoryUnmapInfo);
		} else {
			vkUnmapMemory(*Device, **stagingBufferMemory);
		}

		vk::BufferUsageFlags indicesUsage = vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer;
		vk::MemoryPropertyFlags indicesProperties = vk::MemoryPropertyFlagBits::eDeviceLocal;

		IndicesBuffer = createBuffer(Device, bufferSize, indicesUsage);
		IndicesBufferMemory = createBufferMemory(Device, PhysDevice, *IndicesBuffer, indicesProperties);

		copyBuffer(*stagingBuffer, *IndicesBuffer, bufferSize, Device, CommandPool, GraphicsQueue);

		stagingBuffer.reset();
		stagingBufferMemory.reset();
	}
}
