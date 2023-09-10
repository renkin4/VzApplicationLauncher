#include "VizzioCore/Application.h"
#include "VizzioCore/EntryPoint.h"

class ExampleLayer : public Vizzio::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

Vizzio::Application* Vizzio::CreateApplication(int argc, char** argv)
{
	Vizzio::ApplicationSpecification spec;
	spec.Name = "Vizzio Example";

	Vizzio::Application* app = new Vizzio::Application(spec);
	 
	return app;
}