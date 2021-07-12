#ifndef TEMP_MONITOR
#define TEMP_MONITOR

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
        /**
         * \brief Getter for the _sensor variable.
         * \return _sensor - Sensor Linux path.
         */
        string get_sensor();
        /**
         * \brief Getter for the _highTempThreshCmds variable.
         * \return _highTempThreshCmds - Vector list of commands to run when the upper threshold is exceeded.
         */
        vector<string> get_high_temp_thresh_cmd();
        /**
         * \brief Getter for the _lowTempThreshCmds variable.
         * \return _lowTempThreshCmds - Vector list of commands to run when the lower threshold is surpassed.
         */
        vector<string> get_low_temp_thresh_cmd();
        /**
         * \brief Setter for the _highTempThresh variable.
         * \param threshold - Upper temperature threshold for the sensor.
         */
        void set_high_temp_thresh(int threshold);
        /**
         * \brief Getter for the _highTempThresh variable.
         * \return _highTempThresh - Upper temperature threshold for the sensor.
         */
        int get_high_temp_thresh();
        /**
         * \brief Setter for the _lowTempThresh variable.
         * \param threshold - Lower temperature threshold for the sensor.
         */
        void set_low_temp_thresh(int threshold);
        /**
         * \brief Getter for the _lowTempThresh variable.
         * \return _lowTempThresh - Lower temperature threshold for the sensor.
         */
        int get_low_temp_thresh();
};

class System {
    vector<shared_ptr<Sensor>> _sensorsConfig;  // List of Sensors
    int _loggingPeriod;                         // In miliseconds
    public:
        System (vector<shared_ptr<Sensor>> sensorsConfig, int loggingPeriod = 5) :
            _sensorsConfig(sensorsConfig),
            _loggingPeriod(loggingPeriod) {};
        /**
         * \brief Getter for the _loggingPeriod variable.
         * \return _loggingPeriod - Logging Period for the application.
         */
        int get_logging_period();
        /**
         * \brief Getter for the _sensorsConfig variable.
         * \return _sensorsConfig - Vector list of shared pointers to the System's sensors.
         */
        vector<shared_ptr<Sensor>> get_sensors_config();
};

class TempMonitor
{
    public:
        shared_ptr<System> mySystem;
        void execute_cmd(string cmd);
        void monitor();
};



#endif