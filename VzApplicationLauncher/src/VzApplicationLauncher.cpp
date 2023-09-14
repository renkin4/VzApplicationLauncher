#include "VizzioCore/Application.h"
#include "VizzioCore/EntryPoint.h"

class ExampleLayer : public Vizzio::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		ImGui::Begin("Hello", nullptr, window_flags);
		ImGui::Button("Button");
		 
		ImGui::End();

		//ImGui::ShowDemoWindow();
	}
};

Vizzio::Application* Vizzio::CreateApplication(int argc, char** argv)
{
	Vizzio::ApplicationSpecification spec;
	spec.Name = "Vizzio Example";

	Vizzio::Application* app = new Vizzio::Application(spec);
	app->PushLayer<ExampleLayer>(); 
	return app;
}