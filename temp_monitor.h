#ifndef TEMP_MONITOR
#define TEMP_MONITOR

// Defined at compile time with option -DIMX_VERSION=colibri-imx6 | -DIMX_VERSION=colibri-imx8 | -DIMX_VERSION=RPi4 (for testing)
#ifndef SYS_TYPE
#define SYS_TYPE "colibri-imx6" // Default to IMX6
#endif

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;


class Sensor {
    string _sensor;
    int _highTempThresh;
    int _lowTempThresh;
    vector<string> _highTempThreshCmds;
    vector<string> _lowTempThreshCmds;

    public:
        Sensor(string sensor, int highTempThresh, int lowTempThresh, 
            vector<string> highTempThreshCmds = vector<string>{},
            vector<string> lowTempThreshCmds = vector<string>{}) : 
            _sensor(sensor), _highTempThresh(highTempThresh), _lowTempThresh(lowTempThresh),
            _highTempThreshCmds(highTempThreshCmds),
            _lowTempThreshCmds(lowTempThreshCmds) {};
        string getSensor();
        vector<string> getHighTempThreshCmd();
        vector<string> getLowTempThreshCmd();
        void setHighTempThresh(int threshold);
        int getHighTempThresh();
        void setLowTempThresh(int threshold);
        int getLowTempThresh();
};

class System {
    vector<shared_ptr<Sensor>> _sensorsConfig;  // List of Sensors
    int _loggingPeriod;                         // In miliseconds
    public:
        System (vector<shared_ptr<Sensor>> sensorsConfig, int loggingPeriod = 5) :
            _sensorsConfig(sensorsConfig),
            _loggingPeriod(loggingPeriod) {};
        int getLoggingPeriod();
        vector<shared_ptr<Sensor>> getSensorsConfig();
};

class TempMonitor
{
    static shared_ptr<System> mySystem;
    public:
        void executeCmd(string cmd);
        void monitor();
};



#endif