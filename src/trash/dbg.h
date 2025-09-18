#ifndef MY_DBG
#define MY_DBG

#include <iostream> // cout endl
#include <stdexcept> // runtime_error
#include <string> // string
#include <sstream> // ostringstream

#include <vulkan/vulkan_raii.hpp>

#define ANALYZE 1

#define dbgs          \
  if (!ANALYZE) {     \
  } else              \
    std::cout

struct vulkan_error : public std::runtime_error {
    vk::Result Res;
    vulkan_error(vk::Result R, std::string S) : std::runtime_error(S), Res(R) {}
};

#define VK_CHECK_RESULT(f) {                                                   \
    vk::Result Res = (f);                                                      \
    if (Res != vk::Result::eSuccess) {                                         \
        std::ostringstream Os;                                                 \
        Os << "Vulkan error at " << __FILE__ << ":" << __LINE__ << "\n";       \
        throw vulkan_error(Res, Os.str());                                     \
    }                                                                          \
}

#endif // !MY_DBG
