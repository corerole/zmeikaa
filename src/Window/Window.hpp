#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <stdexcept>
#include <vulkan/vulkan_raii.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef void (*kcb)(GLFWwindow*, int, int, int, int);

struct App_Window_Config {
	size_t width = 1920;
	size_t height = 1080;
};

struct FramebufferSize {
	private:
		uint32_t width;
		uint32_t height;
	public:
		uint32_t getWidth() { return width; };
		uint32_t getHeight() { return height; };
		FramebufferSize(uint32_t width_, uint32_t height_) : width(width_), height(height_) {};
};

struct App_Window {
	private:
		GLFWwindow* window_;
		App_Window_Config config_;
		bool FramebufferResized = false;
	public:
		void set_key_callback(kcb callback);
		void main_loop();
		GLFWwindow* get();
		FramebufferSize getFramebufferSize();
		const FramebufferSize getFramebufferSize() const;
		void set_frabuffer_resized();
		bool& get_frabuffer_resized();
		const bool& get_frabuffer_resized() const;
		App_Window();
		~App_Window();
};

#endif
