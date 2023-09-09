#pragma once

#ifdef VZ_PLATFORM_WINDOWS
 
extern Vizzio::Application* Vizzio::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;
