#pragma once
enum LogLevel {
	LEVEL_ERROR,
	LEVEL_WARNING,
	LEVEL_INFO,
	LEVEL_DEBUG,
	LEVEL_TRACE
};

enum OutputDevice {
	DEVICE_CONSOLE,
	DEVICE_FILE,
	DEVICE_BOTH
};


struct Logger
{
private:
	static LogLevel s_level;
	static OutputDevice s_device;
	static const char* s_fileName;
	
public:
	static void Init();
	static void SetLogLevel(LogLevel level);
	static void SetOutputDevice(OutputDevice device);
	
	static void Error(const char* message);
	static void Warning(const char* message);
	static void Info(const char* message);
	static void Debug(const char* message);
	static void Trace(const char* message);
};

