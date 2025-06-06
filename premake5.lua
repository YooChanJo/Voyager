-- Works for g++
-- Currently only supports Windows

workspace "Voyager"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["vendor"] = "src/vendor"
IncludeDir["GLFW"] = "src/vendor/GLFW/include"
IncludeDir["Glad"] = "src/vendor/Glad/include"
IncludeDir["spdlog"] = "src/vendor/spdlog/include"
IncludeDir["glm"] = "src/vendor/glm"
IncludeDir["ImGui"] = "src/vendor/ImGui"


LibDir = {}
LibDir["GLFW"] = "bin/" .. outputdir .. "/GLFW"
LibDir["Glad"] = "bin/" .. outputdir .. "/Glad"
LibDir["ImGui"] = "bin/" .. outputdir .. "/ImGui"

include "src/vendor/GLFW"
include "src/vendor/Glad"
include "src/vendor/ImGui"

project "Voyager"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    pchheader "pch.h"
    -- pchsource "src/pch.cpp"

    files {
        "src/Voyager/**.h",
        "src/Voyager/**.cpp",
        "src/Main.cpp"
    }
    -- Debug purpose needs removal
    -- removefiles {
    --     "src/API/OpenGL/Renderers/**.h",
    --     "src/API/OpenGL/Renderers/**.cpp",
    -- }

    includedirs {
        "src",
        "src/Voyager",
        "%{IncludeDir.vendor}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
    }

    libdirs {
        "%{LibDir.GLFW}",
        "%{LibDir.Glad}",
        "%{LibDir.ImGui}",
    }

    links {
        "gdi32",
        "opengl32",
        "GLFW",
        "Glad",
        "ImGui",
    }

    defines {
        "GLEW_STATIC",
        "STB_IMAGE_IMPLEMENTATION"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "GLFW_INCLUDE_NONE",
        }
    
    filter "toolset:gcc"
        filter "configurations:Debug"
            defines { "VG_ENABLE_ASSERTS" }
            -- buildoptions { "-g", "-static-libgcc", "-static-libstdc++" }
            buildoptions { "-O0", "-g", "-static-libgcc", "-static-libstdc++" }
        
        -- filter "configurations:Release"
        --     buildoptions { "-O2", "-static-libgcc", "-static-libstdc++" }
        filter "configurations:Release"
            buildoptions {
                "-O3",                   -- Maximum optimization
                -- "--flto",           -- Link Time Optimization
                "-finline-functions",    -- Force inlining
                "-ffast-math",           -- Relaxed floating-point rules (faster but less precise)
                "-march=native",         -- Optimize for your CPU
                "-static-libgcc",        -- Link libgcc statically
                "-static-libstdc++",      -- Link libstdc++ statically
                "-std=c++17",
            }
            