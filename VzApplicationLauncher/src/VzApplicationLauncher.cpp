#include "VizzioCore/Application.h"
#include "VizzioCore/EntryPoint.h"


Vizzio::Application* Vizzio::CreateApplication(int argc, char** argv)
{
	Vizzio::ApplicationSpecification spec;
	spec.Name = "Vizzio Example";

	Vizzio::Application* app = new Vizzio::Application(spec);
	 
	return app;
}