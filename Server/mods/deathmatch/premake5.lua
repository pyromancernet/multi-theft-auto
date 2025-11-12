project "Deathmatch"
	language "C++"
	kind "SharedLib"
	targetname "deathmatch"
	targetdir(buildpath("server/mods/deathmatch"))

	pchheader "StdInc.h"
	pchsource "StdInc.cpp"

	filter "system:windows"
		includedirs { path.join(VENDORS_DIR, "sparsehash/src/windows") }

	filter {}
		includedirs {
			MTASA_SDK_SHARED,
			MTASA_SDK_SERVER,
			path.join(VENDORS_DIR, "bochs"),
			path.join(VENDORS_DIR, "pme"),
			path.join(VENDORS_DIR, "zip"),
			path.join(VENDORS_DIR, "glob/include"),
			path.join(VENDORS_DIR, "zlib"),
			path.join(VENDORS_DIR, "pcre"),
			path.join(VENDORS_DIR, "json-c"),
			path.join(VENDORS_DIR, "lua/src"),
			"../../../Shared/gta",
			"../../../Shared/mods/deathmatch/logic",
			"../../../Shared/animation",
			"../../../Shared/publicsdk/include",
			path.join(VENDORS_DIR, "sparsehash/src/"),
			"logic",
			"utils",
			"."
		}

	defines { "SDK_WITH_BCRYPT" }
	links {
		"Lua_Server", "sqlite", "ehs", "cryptopp", "pme", "pcre", "json-c", "zip", "glob", "zlib", "blowfish_bcrypt",
	}

	vpaths {
		["Headers/*"] = {"**.h", "../../../Shared/mods/deathmatch/**.h", "../../**.h"},
		["Sources/*"] = {"**.cpp", "../../../Shared/mods/deathmatch/**.cpp", "../../../Shared/**.cpp", path.join(VENDORS_DIR, "**.cpp"), "../../**.cpp"},
		["*"] = "premake5.lua"
	}

	files {
		"premake5.lua",
		"**.h",
		"**.cpp",
		"../../../Shared/mods/deathmatch/logic/**.cpp",
		"../../../Shared/mods/deathmatch/logic/**.h",
		"../../../Shared/animation/CEasingCurve.cpp",
		"../../../Shared/animation/CPositionRotationAnimation.cpp",
		-- Todo: Replace these two by using the CryptoPP functions instead
		path.join(VENDORS_DIR, "bochs/bochs_internal/bochs_crc32.cpp"),
	}

	filter "system:windows"
		includedirs { path.join(VENDORS_DIR, "pthreads/include") }
		buildoptions { "-Zm130" }
		links { "ws2_32", "pthread" }

	filter "system:not windows"
		buildoptions { "-Wno-narrowing" } -- We should fix the warnings at some point
		buildoptions { "-pthread" }
		linkoptions { "-pthread" }

	filter "system:linux"
		links { "rt" }

	filter "platforms:x64"
		targetdir(buildpath("server/x64"))

	filter "platforms:arm"
		targetdir(buildpath("server/arm"))

	filter "platforms:arm64"
		targetdir(buildpath("server/arm64"))
