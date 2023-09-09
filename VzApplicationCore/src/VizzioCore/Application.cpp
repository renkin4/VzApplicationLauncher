#include "Application.h"

#include <stdio.h>          // printf, fprintf
#include <stdlib.h>         // abort

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

static Vizzio::Application* s_Instance = nullptr;
extern bool g_ApplicationRunning;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

namespace Vizzio {

	Application::Application(const ApplicationSpecification& applicationSpecification /*= ApplicationSpecification()*/)
		: m_Specification(applicationSpecification)
	{
		s_Instance = this;

		Init();
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	Application& Application::Get()
	{
		return *s_Instance;
	}

	void Application::Run()
	{

	}

	void Application::Init()
	{
		// Setup GLFW window
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit())
		{
			std::cerr << "Could not initalize GLFW!\n";
			return;
		}
		 
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); 
		m_WindowHandle = glfwCreateWindow(m_Specification.Width, m_Specification.Height, m_Specification.Name.c_str(), nullptr, nullptr);

		if (!m_WindowHandle)
		{
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_WindowHandle); 
	}

	void Application::Shutdown()
	{ 
		glfwDestroyWindow(m_WindowHandle);
		glfwTerminate();

		g_ApplicationRunning = false;
	}

}

