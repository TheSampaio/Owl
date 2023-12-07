workspace "Owl"
    configurations { "Debug", "Release" }

    language "C++"
    cppdialect "C++20"
    architecture "x64"

    filter "configurations:Debug"
        defines "WL_DEBUG"
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        defines "WL_RELEASE"
        symbols "Off"
        optimize "Speed"

    OutputDir = "%{cfg.buildcfg}/"

-- ========== Owl ========== --
project "Owl"
    location "Engine"
    kind "SharedLib"

    defines "WL_DLL"

    -- Output directories
    targetdir ("_Output/Bin/" .. OutputDir .. "%{prj.name}")
    objdir    ("_Output/Obj/" .. OutputDir .. "%{prj.name}")

    pchheader("Engine.h")
    pchsource("%{prj.location}/Engine.cpp")

    files {
        "%{prj.location}/**.h",
        "%{prj.location}/**.cpp",
        "%{prj.location}/**.glsl",
    }

    includedirs {
        "ComputerGraphicsSDK/Windows/OpenGL/Include",
        "%{prj.location}"
    }

    libdirs {
        "ComputerGraphicsSDK/Windows/OpenGL/Lib/x64",
    }

    links {
        "opengl32",
        "glew32",
        "glfw3",
    }

    postbuildcommands {
        "{COPY} %{cfg.buildtarget.relpath} ../_Output/Bin/" .. OutputDir .. "/Sandbox"
    }

    filter "system:windows"
        defines "WL_PLATFORM_WIN"
        systemversion "latest"

-- ========== Sandbox ========== --
project "Sandbox"
    location "Game"
    kind "ConsoleApp"

    -- Output directories
    targetdir ("_Output/Bin/" .. OutputDir .. "%{prj.name}")
    objdir    ("_Output/Obj/" .. OutputDir .. "%{prj.name}")

    files {
        "%{prj.location}/**.h",
        "%{prj.location}/**.cpp",
    }

    includedirs {
        "ComputerGraphicsSDK/Windows/OpenGL/Include",
        "Engine/Include",
    }

    libdirs {
        "ComputerGraphicsSDK/Windows/OpenGL/Lib/x64",
    }

    links {
        "Owl",
    }

    filter "system:windows"
        defines "WL_PLATFORM_WIN"
        systemversion "latest"
