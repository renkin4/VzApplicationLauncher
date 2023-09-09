#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

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
		ApplicationSpecification m_Specification;

	};

	// Implemented by CLIENT
	Application* CreateApplication(int argc, char** argv);
}