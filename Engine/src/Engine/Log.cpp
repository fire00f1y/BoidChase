#include "precompiled.h"

#include "Log.h"
#include "spdlog\sinks\stdout_color_sinks.h"

namespace Engine {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() 
	{
		// {{correct color}}[timestamp] {{log name}}: {{messae}}{{endline}}
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("CoreLogger");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("ClientLogger");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}