project "VzApplicationLauncher"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   includedirs
   { 
      "../vendor/imgui",
      "../vendor/glfw/include",
      
      "../VzApplicationCore/src", 
      
      "%{IncludeDir.glm}",
   }

   links
   {
      "VzApplicationCore", 
   }

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "VZ_PLATFORM_WINDOWS" }

   filter "configurations:Debug"
      defines { "VZ_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "VZ_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      kind "WindowedApp"
      defines { "VZ_DIST"}
      runtime "Release"
      optimize "On"
      symbols "Off"

   filter "configurations:Debug_Dev"
      defines { "VZ_DEBUG", "VZ_DEV"  }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release_Dev"
      defines { "VZ_RELEASE", "VZ_DEV" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist_Dev"
      kind "WindowedApp"
      defines { "VZ_DIST", "VZ_DEV" }
      runtime "Release"
      optimize "On"
      symbols "Off"