project "Gl3w"
    kind "StaticLib"
    language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

 	files
	{
        "include/gl/gl3w.h",
        "include/gl/glcorearb.h",
        "include/KHR/khrplatform.h",
        "src/gl3w.c"
    }

	includedirs
	{
		"include"
	}

 	filter "system:windows" 
        systemversion "latest"
        staticruntime "On"
