#pragma once

#ifdef SP_PLATFORM_WINDOWS

extern Spirit::Application* Spirit::CreateApplication();

int main(int argc, char** argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Spirit::Log::Init();
	SP_CORE_WARN("Initialized Log!");

	auto app = Spirit::CreateApplication();
	app->Run();
	delete app;
}

#endif