#pragma once

#ifdef SP_PLATFORM_WINDOWS

extern Spirit::Application* Spirit::CreateApplication();

int main(int argc, char** argv)
{
	Spirit::Log::Init();
	SP_CORE_WARN("Initialized Log!");

	auto app = Spirit::CreateApplication();
	app->Run();
	delete app;
}

#endif