// clientserverprotocol.cpp

#include "clientserverprotocol.h"

ClientServerMessage::ClientServerMessage() {
    // initialize type and time
    m_type = CLIENT_SERVER_MESSAGE_TYPE_NULL;
    m_time = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
    // initialize all other variables
	memset(m_nameTrack, 0, sizeof(m_nameTrack));
	memset(m_nameCar, 0, sizeof(m_nameCar));
	memset(m_nameFrontTireCompound, 0, sizeof(m_nameFrontTireCompound));
	memset(m_nameRearTireCompound, 0, sizeof(m_nameRearTireCompound));
    m_elapsedTime = 0;
    m_elapsedTimeLapStart = 0;
    m_lapNumber = 0;
    m_fuelCurrent = 0;
	m_fuelMaximum = 0;
	m_brakeTemperature[0] = 0;
	m_brakeTemperature[1] = 0;
	m_brakeTemperature[2] = 0;
	m_brakeTemperature[3] = 0;
	m_tireTemperature[0] = 0;
	m_tireTemperature[1] = 0;
	m_tireTemperature[2] = 0;
	m_tireTemperature[3] = 0;
	m_tireWear[0] = 0;
	m_tireWear[1] = 0;
	m_tireWear[2] = 0;
	m_tireWear[3] = 0;
	m_tireFlat[0] = false;
	m_tireFlat[1] = false;
	m_tireFlat[2] = false;
	m_tireFlat[3] = false;
	m_engineRPMCurrent = 0;
	m_engineRPMMaximum = 0;
	m_engineOilTemperature = 0;
	m_engineWaterTemperature = 0;
	m_engineOverheating = false;
	m_gearCurrent = 0;
	m_gearMaximum = 0;
	m_speed = 0;
	m_speedLimiterActive = false;
}

ClientServerMessage::ClientServerMessage(const ClientServerMessageType _type) {
    // initialize type and time
    m_type = _type;
    m_time = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
    // initialize all other variables
	memset(m_nameTrack, 0, sizeof(m_nameTrack));
	memset(m_nameCar, 0, sizeof(m_nameCar));
	memset(m_nameFrontTireCompound, 0, sizeof(m_nameFrontTireCompound));
	memset(m_nameRearTireCompound, 0, sizeof(m_nameRearTireCompound));
    m_elapsedTime = 0;
    m_elapsedTimeLapStart = 0;
    m_lapNumber = 0;
    m_fuelCurrent = 0;
	m_fuelMaximum = 0;
	m_brakeTemperature[0] = 0;
	m_brakeTemperature[1] = 0;
	m_brakeTemperature[2] = 0;
	m_brakeTemperature[3] = 0;
	m_tireTemperature[0] = 0;
	m_tireTemperature[1] = 0;
	m_tireTemperature[2] = 0;
	m_tireTemperature[3] = 0;
	m_tireWear[0] = 0;
	m_tireWear[1] = 0;
	m_tireWear[2] = 0;
	m_tireWear[3] = 0;
	m_tireFlat[0] = false;
	m_tireFlat[1] = false;
	m_tireFlat[2] = false;
	m_tireFlat[3] = false;
	m_engineRPMCurrent = 0;
	m_engineRPMMaximum = 0;
	m_engineOilTemperature = 0;
	m_engineWaterTemperature = 0;
	m_engineOverheating = false;
	m_gearCurrent = 0;
	m_gearMaximum = 0;
	m_speed = 0;
	m_speedLimiterActive = false;
}

ClientServerMessage &ClientServerMessage::operator=(const ClientServerMessage &_message) {
	// copy data
	m_type = _message.m_type;
    m_time = _message.m_time;
    memcpy(m_nameTrack, _message.m_nameTrack, sizeof(m_nameTrack));
	memcpy(m_nameCar, _message.m_nameCar, sizeof(m_nameCar));
	memcpy(m_nameFrontTireCompound, _message.m_nameFrontTireCompound, sizeof(m_nameFrontTireCompound));
	memcpy(m_nameRearTireCompound, _message.m_nameRearTireCompound, sizeof(m_nameRearTireCompound));
    m_elapsedTime = _message.m_elapsedTime;
    m_elapsedTimeLapStart = _message.m_elapsedTimeLapStart;
    m_lapNumber = _message.m_lapNumber;
    m_fuelCurrent = _message.m_fuelCurrent;
	m_fuelMaximum = _message.m_fuelMaximum;
	m_brakeTemperature[0] = _message.m_brakeTemperature[0];
	m_brakeTemperature[1] = _message.m_brakeTemperature[1];
	m_brakeTemperature[2] = _message.m_brakeTemperature[2];
	m_brakeTemperature[3] = _message.m_brakeTemperature[3];
	m_tireTemperature[0] = _message.m_tireTemperature[0];
	m_tireTemperature[1] = _message.m_tireTemperature[1];
	m_tireTemperature[2] = _message.m_tireTemperature[2];
	m_tireTemperature[3] = _message.m_tireTemperature[3];
	m_tireWear[0] = _message.m_tireWear[0];
	m_tireWear[1] = _message.m_tireWear[1];
	m_tireWear[2] = _message.m_tireWear[2];
	m_tireWear[3] = _message.m_tireWear[3];
	m_tireFlat[0] = _message.m_tireFlat[0];
	m_tireFlat[1] = _message.m_tireFlat[1];
	m_tireFlat[2] = _message.m_tireFlat[2];
	m_tireFlat[3] = _message.m_tireFlat[3];
	m_engineRPMCurrent = _message.m_engineRPMCurrent;
	m_engineRPMMaximum = _message.m_engineRPMMaximum;
	m_engineOilTemperature = _message.m_engineOilTemperature;
	m_engineWaterTemperature = _message.m_engineWaterTemperature;
	m_engineOverheating = _message.m_engineOverheating;
	m_gearCurrent = _message.m_gearCurrent;
	m_gearMaximum = _message.m_gearMaximum;
	m_speed = _message.m_speed;
	m_speedLimiterActive = _message.m_speedLimiterActive;
    return *this;
}
