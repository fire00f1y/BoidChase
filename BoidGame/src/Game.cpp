#include <Engine.h>

class BoidGame : public Engine::Application {
public:
	BoidGame()
	{
	}

	~BoidGame()
	{

	}
};

Engine::Application* Engine::CreateApplication()
{
	return new BoidGame();
}