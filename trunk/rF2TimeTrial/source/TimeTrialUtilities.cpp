// TimeTrialUtilities.cpp

#include "TimeTrialUtilities.hpp"

Utilities::Utilities() {

}

Utilities::~Utilities() {

}

Utilities &Utilities::instance() {
	static Utilities utilities;
	return utilities;
}

void Utilities::logMessage(const std::string &_message) {
#if TIME_TRIAL_LOGGING
	FILE *fileLog = fopen(TIME_TRIAL_LOG_FILE_NAME, "a");
	if (!fileLog) return;
	fprintf(fileLog, "[%llu] %s\n", std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1), _message.c_str());
	fclose(fileLog);
#endif
}
