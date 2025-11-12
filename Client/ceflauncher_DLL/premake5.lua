project "CEFLauncher DLL"
	language "C++"
	kind "SharedLib"
	targetname "CEFLauncher_DLL"
	targetdir(buildpath("mta/cef"))

	includedirs { path.join(VENDORS_DIR, "cef3/cef"), MTASA_SDK_SHARED }
	libdirs { path.join(VENDORS_DIR, "cef3/cef/Release") }

	defines { "UNICODE", "PSAPI_VERSION=1" }

	vpaths {
		["Headers/*"] = "**.h",
		["Sources/*"] = "**.cpp",
		["*"] = "premake5.lua"
	}


	files {
		"premake5.lua",
		"*.h",
		"*.cpp",
		MTASA_SDK_SHARED .. "/SharedUtil.cpp"
	}

	links { "delayimp", "CEF", "libcef.lib", "Psapi.lib", "version.lib", "Winmm.lib", "Ws2_32.lib", "DbgHelp.lib" }
	linkoptions { "/DELAYLOAD:libcef.dll" }

	filter "architecture:not x86"
		flags { "ExcludeFromBuild" }

	filter "system:not windows"
		flags { "ExcludeFromBuild" }
