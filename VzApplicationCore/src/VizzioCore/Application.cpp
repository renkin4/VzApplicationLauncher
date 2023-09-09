#include "Application.h"

static Vizzio::Application* s_Instance = nullptr;

namespace Vizzio {

	Application::Application(const ApplicationSpecification& applicationSpecification /*= ApplicationSpecification()*/)
		: m_Specification(applicationSpecification)
	{
		s_Instance = this;
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
}

