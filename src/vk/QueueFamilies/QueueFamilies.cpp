#include "QueueFamilies.hpp"

#if 1

namespace vk {
	namespace supp {
		std::pair<uint32_t, uint32_t> get_QueueFamilies(
			const vk::raii::PhysicalDevice& PhysicalDevice,
			const vk::raii::SurfaceKHR& Surface)
		{
			std::pair<uint32_t, uint32_t> GaP;
			std::vector<vk::QueueFamilyProperties> queueFamilies = PhysicalDevice.getQueueFamilyProperties();
			dbgs << (queueFamilies.size()) << " queue families found";

			uint32_t i = 0;
			dbgs << "\nGQFi : ";
			std::vector<uint32_t> GraphicQueueFamilyIndices;
			for (const auto& queueFamily : queueFamilies) {
				if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
					GaP.first = i;
					GraphicQueueFamilyIndices.push_back(i);
					dbgs << i << ", ";
				}
				++i;
			}

			i = 0;
			dbgs << "\nPQFi : ";
			std::vector<uint32_t> PresentQueueFamilyIndices;
			for (const auto& queueFamily : queueFamilies) {
				if (PhysicalDevice.getSurfaceSupportKHR(i, Surface)) {
					GaP.second = i;
					PresentQueueFamilyIndices.push_back(i);
					dbgs << i << ", ";
				}
				++i;
			}

	
			for (const auto& x : PresentQueueFamilyIndices) {
				auto find_same_ixd = [x](const auto& it) {
					if(x == it) { return true; }
					return false;
				};

				auto iter = std::find_if(
					GraphicQueueFamilyIndices.begin(),
					GraphicQueueFamilyIndices.end(),
					find_same_ixd
				);

				if(iter != GraphicQueueFamilyIndices.end()) {
					GaP.first = *iter;
					GaP.second = GaP.first;
					break;
				}
			}

			dbgs << "\n";
			return GaP;
		}
	} // supp ns
} // vk ns


#endif