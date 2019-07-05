workspace "BoidyChase"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"

include "Engine/vendor/GLFW"

project "Engine"
	location "Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "precompiled.h"
	pchsource "%{prj.name}/src/precompiled.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	
	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ENGINE_BUILD_DLL",
			"ENGINE_WINDOWS",
			"ENGINE_ENABLE_ASSERT"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/BoidGame")
		}

	filter "configurations:Debug"
		optimize "Off"

		defines
		{
			"ENGINE_DEBUG"
		}

	filter "configurations:Release"
		optimize "On"

		defines
		{
			"ENGINE_RELEASE"
		}

	filter "configurations:Dist"
		optimize "On"

		defines
		{
			"ENGINE_DIST"
		}

project "BoidGame"
	location "BoidGame"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Engine/vendor/spdlog/include",
		"Engine/src"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ENGINE_WINDOWS"
		}

	filter "configurations:Debug"
		optimize "Off"

		defines
		{
			"ENGINE_DEBUG"
		}

	filter "configurations:Release"
		optimize "On"

		defines
		{
			"ENGINE_RELEASE"
		}

	filter "configurations:Dist"
		optimize "On"

		defines
		{
			"ENGINE_DIST"
		}