//
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  David Elder
//

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

// Windows headers
#include <windows.h>
#include <wrl.h>
#include <Shlwapi.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <ppl.h>
#include <ppltasks.h>
#include <comdef.h>

#pragma comment(lib, "shlwapi.lib")

#define USE_XINPUT
#include <XInput.h>
#pragma comment(lib, "xinput9_1_0.lib")

#define USE_KEYBOARD_MOUSE
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// DirectX 12 headers
#define FORCE_DX12_DEBUG_MARKUP 1
#define ENABLE_DX12_DEBUG_MARKUP (_DEBUG || _PROFILE || FORCE_DX12_DEBUG_MARKUP)
#include <d3d12.h>
#include <dxgi1_4.h>
#include <dxgi1_6.h>
#include <dxgiformat.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

// Vulkan headers
#define FORCE_VULKAN_VALIDATION 0
#define ENABLE_VULKAN_VALIDATION (_DEBUG || FORCE_VULKAN_VALIDATION)

#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES 1
#include <vulkan.h>
#pragma comment(lib, "vulkan-1.lib")

// Standard library headers
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <shared_mutex>
#include <span>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <variant>
#include <vector>

// Engine headers
#include "Core\BitmaskEnum.h"
#include "Core\CoreEnums.h"
#include "Core\DWParam.h"
#include "Core\IntrusivePtr.h"
#include "Core\IObject.h"
#include "Core\NonCopyable.h"
#include "Core\NonMovable.h"
#include "Core\Utility.h"
#include "Core\VectorMath.h"
#include "LogSystem.h"

// Engine info
#define KODIAK_MAKE_VERSION(major, minor, patch) \
    (((major) << 22) | ((minor) << 12) | (patch))
#define KODIAK_VERSION_MAJOR(version) ((uint32_t)(version) >> 22)
#define KODIAK_VERSION_MINOR(version) (((uint32_t)(version) >> 12) & 0x3ff)
#define KODIAK_VERSION_PATCH(version) ((uint32_t)(version) & 0xfff)

constexpr uint32_t s_engineMajorVersion = 6;
constexpr uint32_t s_engineMinorVersion = 0;
constexpr uint32_t s_enginePatchVersion = 0;

constexpr uint32_t s_engineVersion = KODIAK_MAKE_VERSION(s_engineMajorVersion, s_engineMinorVersion, s_enginePatchVersion);
static const std::string s_engineVersionStr
{
	std::to_string(s_engineMajorVersion) + "." + std::to_string(s_engineMinorVersion) + "." + std::to_string(s_enginePatchVersion)
};

static const std::string s_engineName{ "Kodiak" };