#ifndef App_VK
#define App_VK

#ifndef ANALYZE
#define ANALYZE 1
#endif

#include "../Window/Window.hpp"
#include <random>

constexpr int MAX_FRAMES_IN_FLIGHT = 2;

void run_vk(App_Window& Wnd);
void error_callback(int, const char* err_str);

#endif