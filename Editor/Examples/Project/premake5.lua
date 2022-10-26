workspace "Example"
	architecture "x64"
	configurations
	{
		"Release",
	}
	project "Example"
		kind "SharedLib"
		language "C#"
		files { "Examples/Project/assets/**.cs"}
		links {"C:/Users/ap/source/repos/Spirit3d/Editor/SpiritScript.dll" }
		targetdir("")
