// logfile.h

#ifndef _LOGFILE_H_
#define _LOGFILE_H_

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <chrono>

class LogFile {
public:
    LogFile();
    virtual ~LogFile();
public:
    bool open(const std::string &_fileName);
    bool close();
public:
    void logMessage(const std::string &_message);
private:
    std::ofstream outfile;
};

#endif
