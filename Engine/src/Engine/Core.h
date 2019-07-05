#pragma once

#ifdef ENGINE_WINDOWS
#ifdef ENGINE_BUILD_DLL
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif // ENGINE_BUILD_DLL
#else
#error ONLY WINDOWS IS SUPPORTED
#endif

#ifdef ENGINE_ENABLE_ASSERT
#define ENGINE_ASSERT(x, ...) { if(!(x)) { ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#define CLIENT_ASSERT(x, ...) { if(!(x)) { CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
#define ENGINE_ASSERT(x, ...)
#define CLIENT_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)