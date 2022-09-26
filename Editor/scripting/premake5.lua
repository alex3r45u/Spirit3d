workspace "Haloo"
	architecture "x64"
	configurations
	{
		"Release",
	}
	project "Haloo"
		kind "SharedLib"
		language "C#"
		files { "assets/**.cs"}
		links {"C:/Users/ap/source/repos/Spirit3d/Editor/SpiritScript.dll" }
		targetdir("")
