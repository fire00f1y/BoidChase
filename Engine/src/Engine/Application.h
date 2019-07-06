#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Window.h"

namespace Engine {

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		void Run();

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool HandleKeyDown(KeyPressedEvent& e);
		bool HandleKeyUp(KeyReleasedEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in the client, via EntryPoint.h
	Application* CreateApplication();

}