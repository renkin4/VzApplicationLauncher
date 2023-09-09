#pragma once
#include "Application.h"

#ifdef VZ_PLATFORM_WINDOWS
 
extern Vizzio::Application* Vizzio::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;


namespace Vizzio {

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			Vizzio::Application* app = Vizzio::CreateApplication(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

#ifdef VZ_DIST

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Vizzio::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Vizzio::Main(argc, argv);
}

#endif // VZ_DIST


#endif // VZ_PLATFORM_WINDOWS