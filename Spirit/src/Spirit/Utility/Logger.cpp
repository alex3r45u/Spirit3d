#include "sppch.h"
#include "Logger.h"
#include <chrono>
#include <string.h>
#include <filesystem>

static std::string uniqueName() {
	auto randchar = []() -> char
	{
		const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(4, 0);
	std::generate_n(str.begin(), 4, randchar);
	return str;
}

void Logger::Init() {
	std::filesystem::path dir(getenv("LOCALAPPDATA"));
	std::filesystem::path spirit("Spirit3d"); // Check if folder exists if not create it
	if (!std::filesystem::exists(spirit)) {
		std::filesystem::create_directory(spirit);
	}
	std::filesystem::path file(uniqueName() + "_LOG.log"); // Generate a unique name for the log file to avoid overriding existing files, logs can be sorted by date
	std::filesystem::path full_path = dir / spirit / file;
	s_fileName = full_path.string().c_str();
	s_device = DEVICE_BOTH;
	s_level = LEVEL_INFO;
}

void Logger::SetLogLevel(LogLevel level) { s_level = level; }

void Logger::SetOutputDevice(OutputDevice device) { s_device = device; }

void Logger::Error(const char* message) {
	// Check unnessesary, Error is the lowest level

	if (s_device == DEVICE_CONSOLE) {
		std::cout << "[ERROR] " << message << std::endl;
	}
	else if (s_device == DEVICE_FILE) {
		FILE* f = fopen(s_fileName, "a");
		fprintf(f, "[ERROR] %s\n", message);
		fclose(f);
	}
	else {
		std::cout << "[ERROR] " << message << std::endl;
		FILE* f = fopen(s_fileName, "a");
		fprintf(f, "[ERROR] %s\n", message);
		fclose(f);
	}
}

void Logger::Warning(const char* message) {
	
	if (s_level <= LEVEL_WARNING) {
		if (s_device == DEVICE_CONSOLE) {
			std::cout << "[WARNING] " << message << std::endl;
		}
		else if (s_device == DEVICE_FILE) {
			FILE* f = fopen(s_fileName, "a");
			fprintf(f, "[WARNING] %s\n", message);
			fclose(f);
		}
		else {
			std::cout << "[WARNING] " << message << std::endl;
			FILE* f = fopen(s_fileName, "a");
			fprintf(f, "[WARNING] %s\n", message);
			fclose(f);
		}
	}
}

void Logger::Info(const char* message) {
	if (s_level <= LEVEL_INFO) {
		if (s_device == DEVICE_CONSOLE) {
			std::cout << "[INFO] " << message << std::endl;
		}
		else if (s_device == DEVICE_FILE) {
			FILE* f = fopen(s_fileName, "a");
			fprintf(f, "[INFO] %s\n", message);
			fclose(f);
		}
		else {
			std::cout << "[INFO] " << message << std::endl;
			FILE* f = fopen(s_fileName, "a");
			fprintf(f, "[INFO] %s\n", message);
			fclose(f);
		}
	}
}

void Logger::Debug(const char* message) {
	if (s_level <= LEVEL_DEBUG) {
		if (s_device == DEVICE_CONSOLE) {
			std::cout << "[DEBUG] " << message << std::endl;
		}
		else if (s_device == DEVICE_FILE) {
			FILE* f = fopen(s_fileName, "a");
			fprintf(f, "[DEBUG] %s\n", message);
			fclose(f);
		}
		else {
			std::cout << "[DEBUG] " << message << std::endl;
			FILE* f = fopen(s_fileName, "a");
			fprintf(f, "[DEBUG] %s\n", message);
			fclose(f);
		}
	}
}

void Logger::Trace(const char* message) {
	if (s_level <= LEVEL_TRACE) {
		if (s_device == DEVICE_CONSOLE) {
			std::cout << "[TRACE] " << message << std::endl;
		}
		else if (s_device == DEVICE_FILE) {
			FILE* f = fopen(s_fileName, "a");
			fprintf(f, "[TRACE] %s\n", message);
			fclose(f);
		}
		else {
			std::cout << "[TRACE] " << message << std::endl;
			FILE* f = fopen(s_fileName, "a");
			fprintf(f, "[TRACE] %s\n", message);
			fclose(f);
		}
	}
}