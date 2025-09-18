#include "main.hpp"

int main() try {
		// Game snake;
		App_Window Window;
		run_vk(Window);
		return 0;

} catch (vulkan_error& E) {
	std::cerr << "Vulkan error: " << E.Res << " " << E.what() << std::endl;
	switch (E.Res) {
		case vk::Result::eErrorOutOfHostMemory:
			std::cerr << "VK_ERROR_OUT_OF_HOST_MEMORY\n";
			break;
		case vk::Result::eErrorOutOfDeviceMemory:
			std::cerr << "VK_ERROR_OUT_OF_DEVICE_MEMORY\n";
			break;
		case vk::Result::eErrorDeviceLost:
			std::cerr << "VK_ERROR_DEVICE_LOST\n";
			break;
		default: { std::cerr << "VK error\n"; }
	}
} catch (std::exception& E) {
	std::cerr << "Standard error: " << E.what() << std::endl;
} catch (...) {
	std::cerr << "Unknown error\n";
}