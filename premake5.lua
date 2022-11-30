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
	IncludeDir["entt"] = "Spirit/vendor/entt/include"
	IncludeDir["mono"] = "Spirit/vendor/mono/include"
	IncludeDir["yaml"] = "Spirit/vendor/yaml-cpp/include"
    
    
    include "Spirit/vendor/glfw"
    include "Spirit/vendor/glad"
    include "Spirit/vendor/imgui"
	include "Spirit/vendor/yaml-cpp"
    
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
			"%{prj.name}/vendor/mono/**",
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
			"%{IncludeDir.entt}",
			"%{IncludeDir.mono}",
			"%{IncludeDir.yaml}",

    	}
    
    	links {
    		"GLFW",
    		"Glad",
    		"ImGui",
			"yaml",
			"assimp-vc143-mtd.lib",
			"mono-2.0-sgen.lib",
    	}

		

		defines {
			"YAML_CPP_STATIC_DEFINE",
    		"SP_ENGINE"
		}

    	filter "system:windows"
    		cppdialect "C++17"
    		staticruntime "On"
    		systemversion "latest"
    
    		defines
    		{
    			"SP_PLATFORM_WINDOWS",
    			
    		}

    
    		
    
    	filter "configurations:Debug"
    		defines "SP_DEBUG"
    		symbols "On"
			libdirs {
				"%{prj.name}/lib/Debug",
			}


    	filter "configurations:Release"
    		defines "SP_RELEASE"
    		optimize "On"
			libdirs {
				"%{prj.name}/lib/Release",
			}
    
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
			"%{IncludeDir.entt}",
			"%{IncludeDir.mono}",
		}
	
		links
		{
			"Spirit",
		}

		postbuildcommands
    	{
    		("{COPY} ../Spirit/vendor/mono/bin/mono-2.0-sgen.dll ../bin/" .. outputdir .. "/%{prj.name}"),
			("{COPY} ../Spirit/vendor/assimp/bin/assimp-vc143-mtd.dll ../bin/" .. outputdir .. "/%{prj.name}")
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



	




	project "GameScripts"
		location "GameScripts"
		kind "SharedLib"
		language "C#"

		files {
			"%{prj.name}/**",
		}

		links {
			"SpiritScript"
		}



		targetdir ("Editor/")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
		


	project "SpiritScript"
		location "SpiritScript"
		kind "SharedLib"
		language "C#"
		
		files {
			"%{prj.name}/**"
		}


		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	


	project "SpiritLauncher"
		location "SpiritLauncher"
  		language "C#"
  		kind "WindowedApp"
		architecture "x64"
		framework "net6.0-windows"
		flags { "WPF" }
  		--files{ "%{prj.name}/**" }   -- source files

		links ("Microsoft.Csharp")
		links ("PresentationCore")
		--links ("PresentationFramework")
		links ("System")
		links ("System.Core")
		links ("System.Data")
		links ("System.Data.DataSetExtensions")
		links ("System.Xmal")
		links ("System.Xml")
		links ("System.Xml.Linq")

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	




	

