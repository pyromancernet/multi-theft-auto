project "Multiplayer SA"
	language "C++"
	kind "SharedLib"
	targetname "multiplayer_sa"
	targetdir(buildpath("mta"))

	-- DO NOT REMOVE OR TURN THIS OPTION ON
	-- See details in game_sa/premake5.lua
	editandcontinue "Off"

	filter "system:windows"
		includedirs { path.join(MTASA_VENDORS_ROOT, "sparsehash/src/windows") }

	filter {}
		includedirs {
			MTASA_SDK_SHARED,
			MTASA_SDK_CLIENT,
			path.join(MTASA_VENDORS_ROOT, "sparsehash/src/"),
		}

	pchheader "StdInc.h"
	pchsource "StdInc.cpp"

	vpaths {
		["Headers/*"] = "**.h",
		["Sources"] = "*.c",
		["*"] = "premake5.lua"
	}

	files {
		"premake5.lua",
		"*.h",
		"*.cpp"
	}

	postbuildcommands {
		"%[%{!wks.location}/../Utils/hookcheck.exe] -dll:%[$(TargetPath)] -ignore:\\vendor\\"
	}

	filter "architecture:not x86"
		flags { "ExcludeFromBuild" }

	filter "system:not windows"
		flags { "ExcludeFromBuild" }
