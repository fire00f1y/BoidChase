#include "precompiled.h"

#include "WindowsWindow.h"
#include "Engine/Log.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace Engine {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* message) {
		ENGINE_ERROR("GLFW Error [{0}]: {1}", error, message);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;

		ENGINE_INFO("Creating window '{0}' ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) 
		{
			int success = glfwInit();
			ENGINE_ASSERT(success, "Failed to initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

		if (!m_Window) 
		{
			ENGINE_CRITICAL("COULD NOT CREATE GLFW WINDOW");
		}

		glfwMakeContextCurrent(m_Window);
		if (!gladLoadGL())
		{
			ENGINE_CRITICAL("Failed to load GLAD");
		}

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Event callbacks
		// Mouse events
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			MouseScrolledEvent e((float)xOffset, (float)yOffset);
			data.EventCallback(e);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent e(button);
				data.EventCallback(e);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent e(button);
				data.EventCallback(e);
				break;
			}
			default: {
				ENGINE_WARN("Unknown Mouse button action inputted: {0}", action);
				break;
			}
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent e((float)xPos, (float)yPos);
			data.EventCallback(e);
		});

		// Keyboard events
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				KeyPressedEvent e(key, 0);
				data.EventCallback(e);

				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent e(key);
				data.EventCallback(e);

				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent e(key, 1);
				data.EventCallback(e);

				break;
			}
			default: {
				ENGINE_INFO("Unknown keyboard action inputted: {0}", action);
				break;
			}
			}
		});

		// Application and window callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.Width = width;
			data.Height = height;

			WindowResizeEvent e(width, height);
			data.EventCallback(e);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent e;
			data.EventCallback(e);
		});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int hasFocus) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (hasFocus) {
			case GLFW_TRUE: {
				WindowFocusEvent e;
				data.EventCallback(e);
				break;
			}
			case GLFW_FALSE: {
				WindowLostFocusEvent e;
				data.EventCallback(e);
				break;
			}
			}
		});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xPos, int yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowMoveEvent e(xPos, yPos);
			data.EventCallback(e);
		});
	}

	void WindowsWindow::OnUpdate()
	{
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}