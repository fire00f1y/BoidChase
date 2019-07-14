#include <Engine.h>

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		CLIENT_INFO("[{0}] Update", GetName());
	}

	void OnEvent(Engine::Event& e) override
	{
		CLIENT_INFO("[{0}] Event : {1}", GetName(), e);
	}
};

class BoidGame : public Engine::Application 
{
public:
	BoidGame()
	{
		PushLayer(new ExampleLayer());
	}

	~BoidGame()
	{

	}
};

Engine::Application* Engine::CreateApplication()
{
	return new BoidGame();
}