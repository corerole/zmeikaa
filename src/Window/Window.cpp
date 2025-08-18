#include "Window.hpp"

void App_Window::set_key_callback(kcb key_callback) {
  glfwSetKeyCallback(window_, key_callback);
}

// custom error handler class
struct glfw_error : public std::runtime_error {
    glfw_error(const char* s) : std::runtime_error(s) {}
};

void error_callback(int, const char* err_str) { throw glfw_error(err_str); }

// make sure the viewport matches the new window dimensions
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

App_Window::App_Window() {
    glfwInit();
    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    App_Window_Config cfg;
    window_ = glfwCreateWindow(cfg.width, cfg.height, "Vulkan window", nullptr, nullptr);
    glfwSetWindowUserPointer(window_, this);
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
}


void App_Window::main_loop() {
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
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