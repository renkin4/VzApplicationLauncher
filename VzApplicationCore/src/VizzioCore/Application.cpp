#include "Application.h"

#include <stdio.h>          // printf, fprintf
#include <stdlib.h>         // abort
 
#include "Gl/gl3w.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include <iostream>

static Vizzio::Application* s_Instance = nullptr;
extern bool g_ApplicationRunning;
static bool  g_SwapChainRebuild = false;

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
		Shutdown();

		s_Instance = nullptr;
	}

	Application& Application::Get()
	{
		return *s_Instance;
	}

	void Application::Run()
	{
		m_bRunning = true;

		// Our state
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(1.f, 0.f, 0.f, 1.00f);
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Main loop
		while (!glfwWindowShouldClose(m_WindowHandle) && m_bRunning)
		{
			// Poll and handle events (inputs, window resize, etc.)
			// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
			// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
			// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
			// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
			glfwPollEvents();

			for (auto& layer : m_LayerStack)
			{
				layer->OnUpdate(m_TimeStep);
			}

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

				// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
				// because it would be confusing to have two docking targets within each others.
				ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
				/*if (m_MenubarCallback)
					window_flags |= ImGuiWindowFlags_MenuBar;*/

				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->WorkPos);
				ImGui::SetNextWindowSize(viewport->WorkSize);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
				 
				// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
				// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
				// all active windows docked into it will lose their parent and become undocked.
				// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
				// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin("Vizzio Workspace", nullptr, window_flags);
				ImGui::PopStyleVar();

				ImGui::PopStyleVar(2);

				// Submit the DockSpace
				ImGuiIO& io = ImGui::GetIO();
				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
				{
					ImGuiID dockspace_id = ImGui::GetID("Vizzio Workspace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}

				for (auto& layer : m_LayerStack)
					layer->OnUIRender();

				ImGui::End();
			}

			//// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			//if (show_demo_window)
			//	ImGui::ShowDemoWindow(&show_demo_window);

			//// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
			//{
			//	static float f = 0.0f;
			//	static int counter = 0;

			//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			//	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			//	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			//	ImGui::Checkbox("Another Window", &show_another_window);

			//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			//	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			//		counter++;
			//	ImGui::SameLine();
			//	ImGui::Text("counter = %d", counter);

			//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			//	ImGui::End();
			//}
			//// 3. Show another simple window.
			//if (show_another_window)
			//{
			//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			//	ImGui::Text("Hello from another window!");
			//	if (ImGui::Button("Close Me"))
			//		show_another_window = false;
			//	ImGui::End();
			//}

			// Rendering
			ImGui::Render();

			int display_w, display_h;
			glfwGetFramebufferSize(m_WindowHandle, &display_w, &display_h); 

			glViewport(0, 0, display_w, display_h);
			glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			glfwSwapBuffers(m_WindowHandle);

			float time = GetTime();
			m_FrameTime = time - m_LastFrameTime;
			m_TimeStep = glm::min<float>(m_FrameTime, 0.0333f);
			m_LastFrameTime = time; 
		}
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

		// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
		const char* glsl_version = "#version 100";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
		const char* glsl_version = "#version 150";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); 
#endif

		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_WindowHandle = glfwCreateWindow(m_Specification.Width, m_Specification.Height, m_Specification.Name.c_str(), nullptr, nullptr);

		if (!m_WindowHandle)
		{
			Shutdown();
			return;
		}

		glfwMakeContextCurrent(m_WindowHandle);  
		if (gl3wInit()) {
			printf("failed to initialize OpenGL\n");
			return;
		}

		glfwSetInputMode(m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		glfwMakeContextCurrent(m_WindowHandle);

		glfwSwapInterval(1);
		/*	glfwSetMouseButtonCallback(m_WindowHandle, MouseClickCallback);
			glfwSetCharCallback(m_WindowHandle, CharCallback);
			glfwSetCursorPosCallback(m_WindowHandle, MouseMoveCallback);
			glfwSetErrorCallback(ErrorCallback);
			glfwSetJoystickCallback(JoystickCallback);
			glfwSetKeyCallback(m_WindowHandle, KeyCallback);
			glfwSetScrollCallback(m_WindowHandle, ScrollCallback);
			glfwSetWindowSizeCallback(m_WindowHandle, WinResizeCallback);
			glfwSetInputMode(m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);*/

		// Setup Dear ImGui context

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();
		// 
		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, true); 
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void Application::Shutdown()
	{
		for (auto& layer : m_LayerStack)
		{
			layer->OnDetach();
		}

		m_LayerStack.clear();

		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(m_WindowHandle);
		glfwTerminate();

		g_ApplicationRunning = false;
	}

	float Application::GetTime()
	{
		return (float)glfwGetTime();
	}

}

