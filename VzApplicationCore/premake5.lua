project "VzApplicationCore"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   includedirs
   {
      "src",

      -- "../vendor/imgui",
      "../vendor/glfw/include",
      -- "../vendor/stb_image",

      -- "%{IncludeDir.VulkanSDK}",
      "%{IncludeDir.glm}",
   }

   links
   {
      --  "ImGui",
       "GLFW",

      --  "%{Library.Vulkan}",
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
      defines { "VZ_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"

   filter "configurations:Release_Dev"
      defines { "VZ_RELEASE", "VZ_DEV" }
      runtime "Release"
      optimize "On"
      symbols "On"
 
   filter "configurations:Debug_Dev"
      defines { "VZ_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Dist_Dev"
      defines { "VZ_DIST", "VZ_DEV" }
      runtime "Release"
      optimize "On"
      symbols "Off"