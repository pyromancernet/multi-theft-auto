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

    filter "configurations:Debug"
        defines { "MTA_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter "system:windows"
        defines { "WIN32", "_WIN32", "_WIN32_WINNT=0x601", "TGT_STANDALONE" }
        buildoptions { "/Zc:__cplusplus" }

    -- Vendors paths
    MTASA_VENDORS_ROOT = path.getabsolute("../../../../mtasa-vendors")

    include(path.join(MTASA_VENDORS_ROOT, "tinygettext"))

project "gen_language_list"
    kind "ConsoleApp"
    language "C++"
    warnings "Extra"

    files {
        "gen_language_list.cpp",
    }

    links { "tinygettext" }
    includedirs { path.join(MTASA_VENDORS_ROOT, "tinygettext") }
