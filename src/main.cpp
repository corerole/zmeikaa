#include "main.hpp"

Game* obj;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Game& snake = (*obj);
	if(key || action == GLFW_PRESS) {
		switch(key) {
			case (GLFW_KEY_W): 
				snake.go_up();
				break;
			case (GLFW_KEY_A): 
				snake.go_left();
				break;
			case (GLFW_KEY_S):
				snake.go_down();
				break;
			case (GLFW_KEY_D):
				snake.go_right();
				break;
			default:
		}
	}
}

int main() try {
		Game snake;
		obj = &snake;
		App_Window Window;
		Window.set_key_callback(&key_callback);
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