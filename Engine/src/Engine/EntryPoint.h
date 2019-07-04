#pragma once

#ifdef ENGINE_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();

	ENGINE_ERROR("there was not really an error");
	int a = 5;
	CLIENT_INFO("Hello! Var={0}", a);

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#else
#error ONLY WINDOWS IS SUPPORTED
#endif // ENGINE_WINDOWS
