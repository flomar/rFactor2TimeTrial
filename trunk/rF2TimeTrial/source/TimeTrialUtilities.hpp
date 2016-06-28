// TimeTrialUtilities.hpp

#ifndef _TIMETRIALUTILITIES_H_
#define _TIMETRIALUTILITIES_H_

// include Windows headers
#include <windows.h>

// include STL headers
#include <limits>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <chrono>

// set this to zero to disable logging for performance reasons
#define TIME_TRIAL_LOGGING 0
// change this to set the log file name
#define TIME_TRIAL_LOG_FILE_NAME "TimeTrialLog.txt"

class Utilities {
protected:
	Utilities();
	virtual ~Utilities();
public:
	static Utilities &instance();
public:
	// this function adds an entry to the log
	void logMessage(const std::string &_message);
};

#endif
