#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class Log
{
public:

	static std::shared_ptr<spdlog::logger> getLogger() { return logger; }
	static void Init();
private:
	inline static std::shared_ptr<spdlog::logger> logger;
};

