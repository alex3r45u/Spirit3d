#pragma once

#ifdef SP_PLATFORM_WINDOWS

extern Spirit::Application* Spirit::CreateApplication(int argc, char** argv);

int main(int argc, char** argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Spirit::Log::Init();
	auto app = Spirit::CreateApplication(argc, argv);
	app->Run();
	delete app;
}

#endif