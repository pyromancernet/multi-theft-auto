workspace "utility"
    configurations { "Debug", "Release" }
    architecture "x86_64"
    preferredtoolarchitecture "x86_64"
    staticruntime "on"
    cppdialect "C++23"
    characterset "Unicode"
    flags "MultiProcessorCompile"
    warnings "Off"
    location "build"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj"

    -- Vendors path (moved to separate repository)
    VENDORS_DIR = path.getabsolute("../../../../multitheftauto-vendors")

    filter "configurations:Debug"
        defines { "MTA_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter "system:windows"
        defines { "WIN32", "_WIN32", "_WIN32_WINNT=0x601", "TGT_STANDALONE" }
        buildoptions { "/Zc:__cplusplus" }

    include(path.join(VENDORS_DIR, "tinygettext"))

project "gen_language_list"
    kind "ConsoleApp"
    language "C++"
    warnings "Extra"

    files {
        "gen_language_list.cpp",
    }

    links { "tinygettext" }
    includedirs { path.join(VENDORS_DIR, "tinygettext") }
