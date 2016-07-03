// logfile.cpp

#include "logfile.h"

LogFile::LogFile() {

}

LogFile::~LogFile() {

}

bool LogFile::open(const std::string &_fileName) {
    outfile.close();
    if(_fileName.empty()) return false;
    outfile.open(_fileName, std::ios::app);
    if(!outfile.is_open()) return false;
    return true;
}

bool LogFile::close() {
    if(!outfile.is_open()) return false;
    outfile.close();
    return true;
}

void LogFile::logMessage(const std::string &_message) {
    if(!outfile.is_open()) return;
    outfile << "[" << std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1) << "] " << _message << std::endl;
}
