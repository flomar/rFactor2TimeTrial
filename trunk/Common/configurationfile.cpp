// configurationfile.cpp

#include "configurationfile.h"

ConfigurationFile::ConfigurationFile() {

}

ConfigurationFile::~ConfigurationFile() {

}

bool ConfigurationFile::read(const std::string &_fileName) {
    mapVariables.clear();
    std::string line;
    std::ifstream infile;
    infile.open(_fileName, std::ios::in);
    if(!infile.is_open()) return false;
    while(std::getline(infile, line)) {
        std::regex rx("([A-Za-z0-9_]+)\\s+\"(.*)\"");
        std::smatch rxMatches;
        if(std::regex_match(line, rxMatches, rx)) {
            if(rxMatches.size() == 3) {
                const std::string variableName = rxMatches[1].str();
                const std::string variableValue = rxMatches[2].str();
                mapVariables[variableName] = variableValue;
            }
        }
    }
    return true;
}

std::string ConfigurationFile::getVariable(const std::string _name) {
    const std::string value = mapVariables[_name];
    return value;
}
