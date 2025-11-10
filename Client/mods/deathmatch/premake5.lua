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
		path.join(MTASA_VENDORS_ROOT, "bass/lib/bass"),
		path.join(MTASA_VENDORS_ROOT, "bass/lib/bass_fx"),
		path.join(MTASA_VENDORS_ROOT, "bass/lib/bassmix"),
		path.join(MTASA_VENDORS_ROOT, "bass/lib/tags")
	}

	vpaths {
		["Headers/*"] = {"**.h", "../../../Shared/mods/deathmatch/**.h", "../../**.h"},
		["Sources/*"] = {"**.cpp", "../../../Shared/mods/deathmatch/**.cpp", "../../../Shared/**.cpp", path.join(MTASA_VENDORS_ROOT, "**/**.cpp")},
		["*"] = "premake5.lua"
	}

	filter "system:windows"
		includedirs { path.join(MTASA_VENDORS_ROOT, "sparsehash/src/windows") }
		linkoptions { "/SAFESEH:NO" }

	filter {}
		includedirs {
			MTASA_SDK_SHARED,
			".",
			"./logic",
			MTASA_SDK_CLIENT,
			path.join(MTASA_VENDORS_ROOT, "pthreads/include"),
			path.join(MTASA_VENDORS_ROOT, "bochs"),
			path.join(MTASA_VENDORS_ROOT, "bass"),
			path.join(MTASA_VENDORS_ROOT, "libspeex"),
			path.join(MTASA_VENDORS_ROOT, "zlib"),
			path.join(MTASA_VENDORS_ROOT, "pcre"),
			path.join(MTASA_VENDORS_ROOT, "json-c"),
			path.join(MTASA_VENDORS_ROOT, "lua/src"),
			"../../../Shared/mods/deathmatch/logic",
			"../../../Shared/animation",
			path.join(MTASA_VENDORS_ROOT, "sparsehash/src/"),
			path.join(MTASA_VENDORS_ROOT, "lunasvg/include")
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
		path.join(MTASA_VENDORS_ROOT, "bochs/bochs_internal/bochs_crc32.cpp")
	}

	filter "system:windows"
		buildoptions { "-Zm180" }

	filter "architecture:not x86"
		flags { "ExcludeFromBuild" }

	filter "system:not windows"
		flags { "ExcludeFromBuild" }
