-- VzApplicationLauncher.lua

-- VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
-- IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["glm"] = "../vendor/glm" 
IncludeDir["gl3w"] = "../vendor/gl3w" 

LibraryDir = {}
-- LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
-- LibraryDir["gl3w"] = "../vendor/glew/lib/Release/x64"

Library = {}
-- Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
-- Library["glew"] = "%{LibraryDir.VulkanSDK}/glew.lib"

group "Dependencies"
   include "vendor/imgui"
   include "vendor/glfw"
   include "vendor/gl3w"
group ""

group "Core"
   include "VzApplicationCore"
group ""