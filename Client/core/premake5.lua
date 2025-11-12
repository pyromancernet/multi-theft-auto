project "Client Core"
	language "C++"
	kind "SharedLib"
	targetname "core"
	targetdir(buildpath("mta"))

	filter "system:windows"
		includedirs { path.join(VENDORS_DIR, "sparsehash/src/windows") }
		buildoptions { "-Zm130" }

	filter {}
		includedirs {
			MTASA_SDK_SHARED,
			".",
			MTASA_SDK_CLIENT,
			path.join(VENDORS_DIR, "cegui-0.4.0-custom/include"),
			path.join(VENDORS_DIR, "tinygettext"),
			path.join(VENDORS_DIR, "zlib"),
			path.join(VENDORS_DIR, "jpeg-9f"),
			path.join(VENDORS_DIR, "pthreads/include"),
			path.join(VENDORS_DIR, "sparsehash/src/"),
			path.join(VENDORS_DIR, "detours/4.0.1/src"),
			path.join(VENDORS_DIR, "discord-rpc/discord/include"),
		}

	pchheader "StdInc.h"
	pchsource "StdInc.cpp"

	vpaths {
		["Headers/*"] = {"**.h", "**.hpp"},
		["Sources/*"] = "**.cpp",
		["Resources/*"] = {"**.rc", "../launch/resource/mtaicon.ico"},
		["*"] = "premake5.lua"
	}

	links { "detours" }

	files {
		"premake5.lua",
		"../launch/resource/mtaicon.ico",
		"core.rc",
		"**.h",
		"**.hpp",
		"**.cpp"
	}

	links {
		"ws2_32", "d3dx9", "Userenv", "DbgHelp", "xinput", "Imagehlp", "dxguid", "dinput8",
		"strmiids",	"odbc32", "odbccp32", "shlwapi", "winmm", "gdi32", "Imm32", "Psapi", "dwmapi",
		"pthread", "libpng", "jpeg", "zlib", "tinygettext", "discord-rpc", "wintrust", "crypt32",
	}

	defines {
		"INITGUID",
		"PNG_SETJMP_NOT_SUPPORTED",
	}

	prebuildcommands {
		"%[%{!wks.location}/../utils/gen_language_list.exe] %[%{!wks.location}/../Shared/data/MTA San Andreas/MTA/locale] %[languages.generated.h]"
	}

	filter "architecture:not x86"
		flags { "ExcludeFromBuild" }

	filter "system:not windows"
		flags { "ExcludeFromBuild" }
