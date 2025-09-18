#include "Window.hpp"

void App_Window::set_key_callback(kcb key_callback) {
	glfwSetKeyCallback(window_, key_callback);
}

// custom error handler class
struct glfw_error : public std::runtime_error {
	glfw_error(const char* s) : std::runtime_error(s) {}
};

void error_callback(int, const char* err_str) { throw glfw_error(err_str); }

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	auto App = reinterpret_cast<App_Window*>(glfwGetWindowUserPointer(window));
	App->set_frabuffer_resized();
}

void App_Window::set_frabuffer_resized() {
	FramebufferResized = true;
}

bool& App_Window::get_frabuffer_resized() {
	return FramebufferResized;
}

const bool& App_Window::get_frabuffer_resized() const {
	return FramebufferResized;
}

FramebufferSize App_Window::getFramebufferSize() {
	int w = 0, h = 0;
	glfwGetFramebufferSize(window_, &w, &h);
	return FramebufferSize(w, h);
}

const FramebufferSize App_Window::getFramebufferSize() const {
	int w = 0, h = 0;
	glfwGetFramebufferSize(window_, &w, &h);
	return FramebufferSize(w, h);
}

void WindowShouldCloseCallback(GLFWwindow* window) { /* who die first? */ }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE: {
				glfwSetWindowShouldClose(window, 1);
				break;
			}
			default: { }
		}
	}
}

static std::pair<int, int> getMonPhysSize(GLFWmonitor& monitor) {
	int width_mm, height_mm;
	glfwGetMonitorPhysicalSize(&monitor, &width_mm, &height_mm);
	return std::make_pair(width_mm, height_mm);
}


App_Window::App_Window() {
	glfwInit();
	glfwSetErrorCallback(error_callback);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	App_Window_Config cfg;

	const auto monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	// window_ = glfwCreateWindow(cfg.width, cfg.height, "Vulkan window", glfwGetPrimaryMonitor(), nullptr);
	window_ = glfwCreateWindow(1240, 720, "Vulkan window", nullptr, nullptr);

	glfwSetWindowUserPointer(window_, this);
	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
	glfwSetKeyCallback(window_, key_callback);
	glfwSetWindowCloseCallback(window_, WindowShouldCloseCallback);
	if (glfwRawMouseMotionSupported()) {
		glfwSetInputMode(window_, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	} else {
		glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

App_Window::~App_Window() {
	if (window_) {
		glfwDestroyWindow(window_);
	}
	glfwTerminate();
}

GLFWwindow* App_Window::get() {
		return window_;
}