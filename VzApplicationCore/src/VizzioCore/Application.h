#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "Layer.h"

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

		float GetTime();

		template<typename T>
		void PushLayer()
		{
			static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer!");
			m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
		}

		void PushLayer(const std::shared_ptr<Layer>& layer) { m_LayerStack.emplace_back(layer); layer->OnAttach(); }

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


		std::vector<std::shared_ptr<Layer>> m_LayerStack;
	};

	// Implemented by CLIENT
	Application* CreateApplication(int argc, char** argv);
}