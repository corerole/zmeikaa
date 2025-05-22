#ifndef APP_SHADERS
#define APP_SHADERS

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include <fstream>
// #include <algorithm>
#include "../Vertex/Vertex.h"


#if 0                                   // x       y 
const std::vector<Vertex> Vertices = { {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                                      {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
                                      {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
                                      {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}} };
#else
#if 1
const std::vector<Vertex> Vertices = { {{-1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
                                      {{1.0f, -1.0f}, {0.0f, 1.0f, 1.0f}},
                                      {{1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
                                      {{-1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}}};
#else
#if 0
                                                                                     //     0           1           4
const std::vector<Vertex> Vertices = { {{-1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},         //  (-1 -1)    (0 -1)      (1 -1)      
                                       {{0.0f, -1.0f},  {0.0f, 1.0f, 1.0f}},         //     3           2           5
                                       {{0.0f, 1.0f},   {1.0f, 0.0f, 1.0f}},         //  (-1 1)     (0 1)       (1 1)
                                       {{-1.0f, 1.0f},  {1.0f, 1.0f, 0.0f}},
                                       {{1.0f, -1.0f},  {1.0f, 1.0f, 1.0f}},
                                       {{1.0f, 1.0f},  {1.0f, 1.0f, 1.0f}} };
#endif
#endif
#endif

#if 1
const std::vector<unsigned short> Indices = { 0, 1, 2, 2, 3, 0 };
#else
#if 0 
const std::vector<unsigned short> Indices = { 0, 1, 2, 2, 3, 0, 1, 4, 5, 5, 2, 1 };
#endif
#endif

std::unique_ptr<vk::raii::ShaderModule> installShader(std::vector<char> ShaderCode, vk::raii::Device& Device);
std::vector<char> readFile(const char* Path);

constexpr const char* VERTNAME = "C:\\Users\\CoreRole\\source\\repos\\Zmeika\\src\\vk\\Shaders\\simplest-v.vert.spv";
constexpr const char* FRAGNAME = "C:\\Users\\CoreRole\\source\\repos\\Zmeika\\src\\vk\\Shaders\\simplest-v.frag.spv";

#endif // !APP_SHADERS
