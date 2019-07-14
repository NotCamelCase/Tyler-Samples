#pragma once

#include <cstdint>
#include <cassert>
#include <vector>
#include <chrono>
#include <immintrin.h>

//#define GLM_FORCE_MESSAGES
//#define GLM_FORCE_INTRINSICS
#define GLM_FORCE_INLINE
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef _DEBUG
#pragma comment(lib, "SDL2maind.lib")
#pragma comment(lib, "SDL2d.lib")
#else
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")
#endif

#include <SDL.h>