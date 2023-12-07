#ifndef OWL_PCH
#define OWL_PCH

// Standard libraries
#include <array>
#include <chrono>
#include <iostream>

// External libraries
#include <GL/glew.h>

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4098)
		#include "GLFW/glfw3.h"
	#pragma warning(pop)
#else
	#include "GLFW/glfw3.h"
#endif

// Primitive typedefs
#include "Source/Kind/Header/Basic.h"

// DLL exporter
#ifdef WL_PLATFORM_WIN
	#ifdef WL_DLL
		#define OWL_API __declspec(dllexport)
	#else
		#define OWL_API __declspec(dllimport)
	#endif
#else
	#error Owl engine does not support Unix platforms!
#endif

#endif // !OWL_PCH
