#pragma once

// === Default Libraries ===
#include <algorithm>
#include <assert.h>
#include <array>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// === External Libraries ===
#include <DirectXMath.h>
#include <dxgi.h>
#include <dxgiformat.h>
#include <d3dcompiler.h>
#include <d3d11.h>

// === Personal Libraries ===
#include "Types.h"

// D3D11 Toolkit API
#pragma warning(push)
#pragma warning(disable : 4005)
	#include <stdint.h>
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable : 4005)
	#include <wincodec.h>
#pragma warning(pop)

// === Windows API ===
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
	#include <windows.h>
	#include <windowsx.h>
#endif // !WIN32_MEAN_AND_LEAN
