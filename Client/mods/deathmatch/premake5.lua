project "Client Deathmatch"
	language "C++"
	kind "SharedLib"
	targetname "client"
	targetdir(buildpath("mods/deathmatch"))

	pchheader "StdInc.h"
	pchsource "StdInc.cpp"

	defines { "LUNASVG_BUILD", "LUA_USE_APICHECK", "SDK_WITH_BCRYPT" }
	links {
		"Lua_Client", "pcre", "json-c", "ws2_32", "portaudio", "zlib", "cryptopp", "libspeex", "blowfish_bcrypt", "lunasvg",
		path.join(VENDORS_DIR, "bass/lib/bass"),
		path.join(VENDORS_DIR, "bass/lib/bass_fx"),
		path.join(VENDORS_DIR, "bass/lib/bassmix"),
		path.join(VENDORS_DIR, "bass/lib/tags")
	}

	vpaths {
		["Headers/*"] = {"**.h", "../../../Shared/mods/deathmatch/**.h", "../../**.h"},
		["Sources/*"] = {"**.cpp", "../../../Shared/mods/deathmatch/**.cpp", "../../../Shared/**.cpp", path.join(VENDORS_DIR, "**.cpp")},
		["*"] = "premake5.lua"
	}

	filter "system:windows"
		includedirs { path.join(VENDORS_DIR, "sparsehash/src/windows") }
		linkoptions { "/SAFESEH:NO" }

	filter {}
		includedirs {
			MTASA_SDK_SHARED,
			".",
			"./logic",
			MTASA_SDK_CLIENT .. "/",
			path.join(VENDORS_DIR, "pthreads/include"),
			path.join(VENDORS_DIR, "bochs"),
			path.join(VENDORS_DIR, "bass"),
			path.join(VENDORS_DIR, "libspeex"),
			path.join(VENDORS_DIR, "zlib"),
			path.join(VENDORS_DIR, "pcre"),
			path.join(VENDORS_DIR, "json-c"),
			path.join(VENDORS_DIR, "lua/src"),
			"../../../Shared/mods/deathmatch/logic",
			"../../../Shared/animation",
			path.join(VENDORS_DIR, "sparsehash/src/"),
			path.join(VENDORS_DIR, "lunasvg/include")
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
		path.join(VENDORS_DIR, "bochs/bochs_internal/bochs_crc32.cpp")
	}

	filter "system:windows"
		buildoptions { "-Zm180" }

	filter "architecture:not x86"
		flags { "ExcludeFromBuild" }

	filter "system:not windows"
		flags { "ExcludeFromBuild" }
