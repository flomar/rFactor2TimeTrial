// TimeTrial.hpp

#ifndef _TIMETRIAL_H_
#define _TIMETRIAL_H_

// include plugin base class header
#include "InternalsPlugin.hpp"

// include common headers
#include "../Common/client.h"
#include "../Common/clientserverprotocol.h"
#include "../Common/configurationfile.h"
#include "../Common/logfile.h"

// include STL headers
#include <limits>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

#define RF2TIMETRIAL_CONFIGURATION_FILE_NAME "rF2TimeTrial.cfg"

class TimeTrialPlugin : public InternalsPluginV07 {
public:
	TimeTrialPlugin();
	~TimeTrialPlugin();
public:
	virtual void Startup(long _version);
	virtual void Shutdown();
	virtual void Load();
	virtual void Unload();
	virtual void EnterRealtime();
	virtual void ExitRealtime();
public:
	virtual long WantsTelemetryUpdates();
	virtual void UpdateTelemetry(const TelemInfoV01 &_info);
private:
	void startGame();
	void finishGame();
	void startSession();
	void finishSession();
	void startRun();
	void finishRun();
private:
	// this function is called periodically during a session and transmits 
	// telemetry updates to the server
	void updateTimeTrialTelemetry(const TelemInfoV01 &_info);
private:
	ConfigurationFile configurationFile;
	LogFile logFile;
	Client client;
};

#endif
