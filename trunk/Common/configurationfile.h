// configurationfile.h

#ifndef _CONFIGURATIONFILE_H_
#define _CONFIGURATIONFILE_H_

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <map>

class ConfigurationFile {
public:
    ConfigurationFile();
    virtual ~ConfigurationFile();
public:
    bool read(const std::string &_fileName);
public:
    std::string getVariable(const std::string _name);
private:
    std::map<std::string, std::string> mapVariables;
};

#endif
