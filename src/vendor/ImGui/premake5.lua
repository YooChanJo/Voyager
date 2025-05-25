project "ImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"imconfig.h",
		"imgui_demo.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_tables.cpp",
		"imgui_widgets.cpp",
		"imgui.cpp",
		"imgui.h",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
		-- "backends/imgui_impl_opengl3.h",
		-- "backends/imgui_impl_opengl3.cpp",
		-- "backends/imgui_impl_glfw.h",
		-- "backends/imgui_impl_glfw.cpp",
	}

	-- includedirs {
	-- 	".",
	-- 	"../GLFW/include"
	-- }
	
	-- defines {
	-- 	"IMGUI_IMPL_OPENGL_LOADER_GLAD"
	-- }

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

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