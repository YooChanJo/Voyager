project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"include/Glad/glad.h",
		"include/KRH/khrplatform.h",
		"src/glad.c"
	}

    includedirs {
        "include"
    }

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		filter "toolset:gcc"
        filter "configurations:Debug"
            buildoptions { "-g", "-static-libgcc", "-static-libstdc++" }
        
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
                "-static-libstdc++"      -- Link libstdc++ statically
            }
            