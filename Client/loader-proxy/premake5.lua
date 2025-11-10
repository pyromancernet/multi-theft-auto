project "Loader Proxy"
	language "C++"
	kind "SharedLib"
	targetname "mtasa"
	targetdir(buildpath("mta"))
	targetsuffix ""

	vpaths {
		["Headers/*"] = "**.h",
		["Sources"] = { "*.cpp" },
		["Resources/*"] = "*.def",
		["*"] = "premake5.lua"
	}

	files {
		"premake5.lua",
		"exports.def",
		"main.cpp",
	}

	includedirs {
		MTASA_SDK_SHARED,
	}

	filter "architecture:not x86"
		flags { "ExcludeFromBuild" }

	filter "system:not windows"
		flags { "ExcludeFromBuild" }
