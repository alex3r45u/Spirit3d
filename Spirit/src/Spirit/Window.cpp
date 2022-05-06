#include "sppch.h"
#include "Window.h"
#include "Spirit/Platform/Windows/WindowsWindow.h"

std::unique_ptr<Spirit::Window> Spirit::Window::Create(const WindowProps& props)
{

#ifdef SP_PLATFORM_WINDOWS
		return std::make_unique<Spirit::WindowsWindow>(props);
#else
		SP_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	
}
