#include "Log.h"

void Log::Init() {
		auto stdOutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		stdOutSink->set_pattern("%D %T %^[%n:%t]%$ %v");
		logger = std::make_shared<spdlog::logger>("LOG", stdOutSink);
		logger->info("Logging initialized.");
}