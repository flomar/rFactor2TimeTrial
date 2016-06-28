// clientserverprotocol.h

#ifndef _CLIENTSERVERPROTOCOL_H_
#define _CLIENTSERVERPROTOCOL_H_

#include <stdint.h>
#include <string.h>
#include <chrono>

enum ClientServerMessageType {
    CLIENT_SERVER_MESSAGE_TYPE_NULL,
    CLIENT_SERVER_MESSAGE_TYPE_START_SESSION,
    CLIENT_SERVER_MESSAGE_TYPE_FINISH_SESSION,
    CLIENT_SERVER_MESSAGE_TYPE_START_RUN,
    CLIENT_SERVER_MESSAGE_TYPE_FINISH_RUN,
    CLIENT_SERVER_MESSAGE_TYPE_UPDATE_TELEMETRY
};

struct ClientServerMessage {
    // construction
    ClientServerMessage();
    ClientServerMessage(const ClientServerMessageType _type);
    // operator functions
    ClientServerMessage &operator=(const ClientServerMessage &_message);
    // generic data
    int8_t m_type;
    int64_t m_time;
    // telemetry data
    char m_nameTrack[64];
    char m_nameCar[64];
    char m_nameFrontTireCompound[18];
    char m_nameRearTireCompound[18];
    int64_t m_elapsedTime;
    int64_t m_elapsedTimeLapStart;
    int64_t m_lapNumber;
    double m_fuelCurrent;
    double m_fuelMaximum;
    double m_brakeTemperature[4];
    double m_tireTemperature[4];
    double m_tireWear[4];
    bool m_tireFlat[4];
    double m_engineRPMCurrent;
    double m_engineRPMMaximum;
    double m_engineOilTemperature;
    double m_engineWaterTemperature;
    bool m_engineOverheating;
    int64_t m_gearCurrent;
    int64_t m_gearMaximum;
    double m_speed;
    bool m_speedLimiterActive;
};

#endif
