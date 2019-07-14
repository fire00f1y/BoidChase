#include "precompiled.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Log.h"

#include "GLFW/glfw3.h"

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}


	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e) 
	{
		ENGINE_INFO("Received event: {0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(HandleKeyDown));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(HandleKeyUp));
	}

	bool Application::HandleKeyDown(KeyPressedEvent& e)
	{
		// Escape key quits!
		if (e.GetKeyCode() == 256) {
			OnWindowClose(WindowCloseEvent());
		}

		return true;
	}

	bool Application::HandleKeyUp(KeyReleasedEvent& e)
	{
		return true;
	}

	void Application::Run() {
		while (m_Running) {
			//m_Window->Draw();
			m_Window->OnUpdate();
		}

		glfwTerminate();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}