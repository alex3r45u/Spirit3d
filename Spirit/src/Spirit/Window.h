#pragma once
#include "sppch.h"
#include "Spirit/Event/Event.h"

namespace Spirit {

	struct WindowProps {
		unsigned int width;
		unsigned int height;
		std::string name;

		WindowProps(const std::string& title = "Spirit Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: width(width), height(height), name(title) {}
	};


	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVsync(bool vsync = true) = 0;
		virtual bool IsVsync() const = 0;


		virtual void* GetNativeWindow() const = 0;



		static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
	};
}