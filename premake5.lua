workspace "Spirit3d"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    
    IncludeDir = {}
    IncludeDir["glfw"] = "Spirit/vendor/glfw/include"
    IncludeDir["glad"] = "Spirit/vendor/glad/include"
    IncludeDir["imgui"] = "Spirit/vendor/imgui"
    IncludeDir["glm"] = "Spirit/vendor/glm"
    IncludeDir["stb"] = "Spirit/vendor/stb"
    IncludeDir["glm"] = "Spirit/vendor/glm"
    IncludeDir["assimp"] = "Spirit/vendor/assimp/"
    
    
    include "Spirit/vendor/glfw"
    include "Spirit/vendor/glad"
    include "Spirit/vendor/imgui"
    
    project "Spirit"
    	location "Spirit"
    	kind "StaticLib"
    	language "C++"
    
    	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    	pchheader "sppch.h"
    	pchsource "Spirit/src/sppch.cpp"
    
    	files
    	{
    		"%{prj.name}/src/**.h",
    		"%{prj.name}/src/**.cpp",
    		"%{prj.name}/vendor/stb/**.h",
    		"%{prj.name}/vendor/stb/**.cpp",
    		"%{prj.name}/vendor/glm/glm/**.hpp",
    		"%{prj.name}/vendor/glm/glm/**.inl",
			"%{prj.name}/vendor/assimp/**",
    	}
    
    	includedirs
    	{
    		"%{prj.name}/src",
    		"%{prj.name}/vendor/spdlog/include",
    		"%{IncludeDir.glfw}",
    		"%{IncludeDir.glad}",
    		"%{IncludeDir.imgui}",
    		"%{IncludeDir.glm}",
    		"%{IncludeDir.stb}",
    		"%{IncludeDir.assimp}",
    	}
    
    	links {
    		"GLFW",
    		"Glad",
    		"ImGui",
			"assimp-vc143-mtd.lib",
    	}

		libdirs {
			"%{prj.name}/lib"
		}
    
    	filter "system:windows"
    		cppdialect "C++17"
    		staticruntime "On"
    		systemversion "latest"
    
    		defines
    		{
    			"SP_PLATFORM_WINDOWS",
    			"SP_BUILD_DLL",
    			"SP_ENGINE"
    		}
    
    		postbuildcommands
    		{
    			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
    		}
    
    	filter "configurations:Debug"
    		defines "SP_DEBUG"
    		symbols "On"
    
    	filter "configurations:Release"
    		defines "SP_RELEASE"
    		optimize "On"
    
    	filter "configurations:Dist"
    		defines "SP_DIST"
    		optimize "On"
    
    project "Sandbox"
    	location "Sandbox"
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
    		"Spirit/vendor/spdlog/include",
    		"Spirit/src",
            "Spirit/vendor",
    		"%{IncludeDir.glm}",
			"%{IncludeDir.assimp}",
    	}
    
    	links
    	{
    		"Spirit",
    	}

    
    	filter "system:windows"
    		cppdialect "C++17"
    		staticruntime "On"
    		systemversion "latest"
    
    		defines
    		{
    			"SP_PLATFORM_WINDOWS"
    		}
    
    	filter "configurations:Debug"
    		defines "SP_DEBUG"
    		symbols "On"
    
    	filter "configurations:Release"
    		defines "SP_RELEASE"
    		optimize "On"
    
    	filter "configurations:Dist"
    		defines "SP_DIST"
    		optimize "On"




	project "Editor"
		location "Editor"
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
			"Spirit/vendor/spdlog/include",
			"Spirit/src",
			"Spirit/vendor",
			"%{IncludeDir.glm}",
			"%{IncludeDir.assimp}",
		}
	
		links
		{
			"Spirit",
		}

	
		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"
	
			defines
			{
				"SP_PLATFORM_WINDOWS"
			}
	
		filter "configurations:Debug"
			defines "SP_DEBUG"
			symbols "On"
	
		filter "configurations:Release"
			defines "SP_RELEASE"
			optimize "On"
	
		filter "configurations:Dist"
			defines "SP_DIST"
			optimize "On"







	

