-- premake5.lua
workspace "VzApplicationLauncher"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "VzApplicationLauncher"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "VzApplicationLauncherExternal.lua"
include "VzApplicationLauncher"