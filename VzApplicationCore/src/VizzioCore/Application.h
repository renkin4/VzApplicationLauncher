#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

struct GLFWwindow;

namespace Vizzio {

	struct ApplicationSpecification
	{
		std::string Name = "Vizzio App";
		uint32_t Width = 1600;
		uint32_t Height = 900;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& applicationSpecification = ApplicationSpecification());
		~Application();

		static Application& Get();

		void Run(); 

	private:
		void Init();
		void Shutdown();

	private:
		ApplicationSpecification m_Specification;
		GLFWwindow* m_WindowHandle = nullptr;

		bool m_bRunning = false; 
		 
		float m_TimeStep = 0.0f;
		float m_FrameTime = 0.0f;
		float m_LastFrameTime = 0.0f;

	};

	// Implemented by CLIENT
	Application* CreateApplication(int argc, char** argv);
}