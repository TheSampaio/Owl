#ifndef OWL_PCH_H
#define OWL_PCH_H

// Default Librariws
#include <array>
#include <iostream>
#include <string>

// External Libraries
#include <dxgi.h>
#include <d3d11.h>

// Engine Types
#include "Types.h"

// Windows API
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
	#include <windows.h>
	#include <windowsx.h>
#endif // !WIN32_MEAN_AND_LEAN

#endif // !OWL_PCH_H
