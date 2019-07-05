#pragma once

#ifdef ENGINE_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();

	ENGINE_INFO("Engine started successfully");

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#else
#error ONLY WINDOWS IS SUPPORTED
#endif // ENGINE_WINDOWS
