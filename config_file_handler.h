#ifndef CONFIG_FILE_HANDLER
#define CONFIG_FILE_HANDLER

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <memory>

#include "temp_monitor.h"

using namespace std;

class ConfigFileHandler {

    public:
        ConfigFileHandler() : _filename("./config.conf") {};
        shared_ptr<System> parse_config_file ();
        void edit_threshold_high(int sensorId, int newThreshold);
        void edit_threshold_low(int sensorId, int newThreshold);
        void add_script_high_temp(int sensorId, string cmd);
        void remove_script_high_temp(int sensorId, int cmdId);
        void add_script_low_temp(int sensorId, string cmd);
        void remove_script_low_temp(int sensorId, int cmdId);
        void prettyPrintConfig(shared_ptr<System> mySystem);
    private:
        string _filename;
        void addConfFileCommand(int sensorId, string cmd, string highLow);
        void edit_temp_threshold(int sensorId, int newThreshold, string highLow);

};


#endif