Resources = {}

project "Resources"

	kind "StaticLib"
	flags { common_flags }

	builddeps { "Core" }
	
	pchheader "Resources/API.h"
	pchsource "../src/Resources/ResourceManager.cpp"
	
	files
	{
		"Resources.lua",
		"../inc/Resources/**.h",
		"../src/Resources/**.cpp",
		"../dep/picopng/lode*.cpp",
		"../dep/stb/stb_image.cpp",
	}
	
	vpaths
	{
		[""] = { "../../src/Resources/", "../../inc/Resources/" },
		["Animation"] = { "Animation*", "Attachment*", "Bone*", "Skeleton*" },
		["Database"] = "ResourceDatabase*",
		["Fonts"] = { "*Font*", "TTF*" },
		["Images"] = { "Image*" },
		["Images/STB"] = { "STB*", "stb_image*" },
		["Images/PNG"] = { "lodepng*", "picopng*", "PNG_Loader*" },
		["Indexer"] = "ResourceIndexer*",
		["Materials"] = "Material*",
		["Meshes"] = "Mesh*",
		["Scripts"] = { "Script*", "LuaLoader*" },
		["Shaders"] = "Shader*",
		["Sounds"] = { "Sound*", "ResourceSound*" },
		["Sounds/OGG"] = "OGG*",
		["Text"] = "Text*",
	}

	includedirs
	{
		"../inc/",
		"../dep/stb/",
		"../dep/picopng/",
		"../dep/ogg/include",
		"../dep/vorbis/include",
	}

	Resources.libdirs =
	{
		"../dep/png/lib/",
		"../dep/ogg/lib",
		"../dep/vorbis/lib",
	}
	
	Resources.links =
	{
	}

	Resources.links.Debug =
	{
		"pngd",
		"ogg_static_d",
		"vorbis_static_d",
		"vorbisfile_static_d"
	}

	Resources.links.Release =
	{
		"png",
		"ogg_static",
		"vorbis_static",
		"vorbisfile_static"
	}