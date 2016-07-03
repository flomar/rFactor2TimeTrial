// TimeTrial.cpp

#include "TimeTrial.hpp"

#include <math.h>
#include <stdio.h>

extern "C" __declspec(dllexport)
const char * __cdecl GetPluginName() { return("rF2TimeTrial Plugin (c) 2016 flomar"); }

extern "C" __declspec(dllexport)
PluginObjectType __cdecl GetPluginType() { return(PO_INTERNALS); }

extern "C" __declspec(dllexport)
int __cdecl GetPluginVersion() { return(7); }

extern "C" __declspec(dllexport)
PluginObject * __cdecl CreatePluginObject() { return((PluginObject*)(new TimeTrialPlugin)); }

extern "C" __declspec(dllexport)
void __cdecl DestroyPluginObject(PluginObject *obj) { delete((TimeTrialPlugin*)(obj)); }



TimeTrialPlugin::TimeTrialPlugin() {
	
}

TimeTrialPlugin::~TimeTrialPlugin() {

}

void TimeTrialPlugin::Startup(long _version) {
	startGame();
}

void TimeTrialPlugin::Shutdown() {
	finishGame();
}

void TimeTrialPlugin::Load() {
	startSession();
}

void TimeTrialPlugin::Unload() {
	finishSession();
}

void TimeTrialPlugin::EnterRealtime() {
	startRun();
}

void TimeTrialPlugin::ExitRealtime() {
	finishRun();
}

long TimeTrialPlugin::WantsTelemetryUpdates() {
	// we want telemetry updates for the player only
	return 1;
}

void TimeTrialPlugin::UpdateTelemetry(const TelemInfoV01 &_info) {
	updateTimeTrialTelemetry(_info);
}

void TimeTrialPlugin::startGame() {
	// try to read the configuration file
	if (!configurationFile.read(RF2TIMETRIAL_CONFIGURATION_FILE_NAME)) {
		return;
	}
	// try to open the log file
	const std::string logFileName = configurationFile.getVariable("RF2TIMETRIAL_LOG_FILE_NAME");
	if (!logFile.open(logFileName)) {
		return;
	}
	// dump log information
	logFile.logMessage("START GAME");
	// try to connect to server
	const std::string serverAddress = configurationFile.getVariable("RF2TIMETRIAL_SERVER_ADDRESS");
	const std::string serverPort = configurationFile.getVariable("RF2TIMETRIAL_SERVER_PORT");
	if (!client.connectToServer(serverAddress, serverPort)) {
		logFile.logMessage("could not connect to " + serverAddress + ":" + serverPort);
		return;
	}
}

void TimeTrialPlugin::finishGame() {
	logFile.logMessage("FINISH GAME");
	client.disconnectFromServer();
}

void TimeTrialPlugin::startSession() {
	logFile.logMessage("START SESSION");
	ClientServerMessage message(CLIENT_SERVER_MESSAGE_TYPE_START_SESSION);
	client.sendMessage(message);
}

void TimeTrialPlugin::finishSession() {
	logFile.logMessage("FINISH SESSION");
	ClientServerMessage message(CLIENT_SERVER_MESSAGE_TYPE_FINISH_SESSION);
	client.sendMessage(message);
}

void TimeTrialPlugin::startRun() {
	logFile.logMessage("START RUN");
	ClientServerMessage message(CLIENT_SERVER_MESSAGE_TYPE_START_RUN);
	client.sendMessage(message);
}

void TimeTrialPlugin::finishRun() {
	logFile.logMessage("FINISH RUN");
	ClientServerMessage message(CLIENT_SERVER_MESSAGE_TYPE_FINISH_RUN);
	client.sendMessage(message);
}

void TimeTrialPlugin::updateTimeTrialTelemetry(const TelemInfoV01 &_info) {
	// create new update message (and populate telemetry variables)
	ClientServerMessage message(CLIENT_SERVER_MESSAGE_TYPE_UPDATE_TELEMETRY);
	const size_t lengthNameTrack = strlen(_info.mTrackName) > sizeof(message.m_nameTrack) ? sizeof(message.m_nameTrack) : strlen(_info.mTrackName);
	const size_t lengthNameCar = strlen(_info.mVehicleName) > sizeof(message.m_nameCar) ? sizeof(message.m_nameCar) : strlen(_info.mVehicleName);
	const size_t lengthNameFrontTireCompound = strlen(_info.mFrontTireCompoundName) > sizeof(message.m_nameFrontTireCompound) ? sizeof(message.m_nameFrontTireCompound) : strlen(_info.mFrontTireCompoundName);
	const size_t lengthNameRearTireCompound = strlen(_info.mRearTireCompoundName) > sizeof(message.m_nameRearTireCompound) ? sizeof(message.m_nameRearTireCompound) : strlen(_info.mRearTireCompoundName);
	memcpy(message.m_nameTrack, _info.mTrackName, lengthNameTrack);
	memcpy(message.m_nameCar, _info.mVehicleName, lengthNameCar);
	memcpy(message.m_nameFrontTireCompound, _info.mFrontTireCompoundName, lengthNameFrontTireCompound);
	memcpy(message.m_nameRearTireCompound, _info.mRearTireCompoundName, lengthNameRearTireCompound);
	message.m_elapsedTime = (int64_t)(_info.mElapsedTime * 1000.0);
	message.m_elapsedTimeLapStart = (int64_t)(_info.mLapStartET * 1000.0);
	message.m_lapNumber = (int64_t)(_info.mLapNumber);
	message.m_fuelCurrent = _info.mFuel;
	message.m_fuelMaximum = _info.mFuelCapacity;
	for (int indexWheel = 0; indexWheel < 4; indexWheel++) {
		message.m_brakeTemperature[indexWheel] = _info.mWheel[indexWheel].mBrakeTemp - 273.15;
		message.m_tireTemperature[indexWheel] = (_info.mWheel[indexWheel].mTemperature[0] + _info.mWheel[indexWheel].mTemperature[1] + _info.mWheel[indexWheel].mTemperature[2]) / 3.0 - 273.15;
		message.m_tireWear[indexWheel] = _info.mWheel[indexWheel].mWear;
		message.m_tireFlat[indexWheel] = _info.mWheel[indexWheel].mFlat;
	}
	message.m_engineRPMCurrent = _info.mEngineRPM;
	message.m_engineRPMMaximum = _info.mEngineMaxRPM;
	message.m_engineOilTemperature = _info.mEngineOilTemp;
	message.m_engineWaterTemperature = _info.mEngineWaterTemp;
	message.m_engineOverheating = _info.mOverheating;
	message.m_gearCurrent = (int64_t)(_info.mGear);
	message.m_gearMaximum = (int64_t)(_info.mMaxGears);
	message.m_speed = (double)(sqrt(_info.mLocalVel[0] * _info.mLocalVel[0] + _info.mLocalVel[1] * _info.mLocalVel[1] + _info.mLocalVel[2] * _info.mLocalVel[2]));
	message.m_speedLimiterActive = (bool)(_info.mSpeedLimiter > 0);
	// send update message to the server
	client.sendMessage(message);
}
