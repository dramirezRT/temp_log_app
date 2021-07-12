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
        /**
         * \brief Constructor of the ConfigFileHandler.
         * \param path - Custom path of the config.conf configuration file
         */
        ConfigFileHandler() : _filename("/etc/temp-monitor/config.conf") {};
        ConfigFileHandler(string path) : _filename(path) {};
        /**
         * \brief Parses the contents of the config.conf file.
         * \return result - Shared pointer with the System object.
         */
        shared_ptr<System> parse_config_file ();
        /**
         * \brief Edits the upper threshold for a given sensorId.
         * \param sensorId - Sensor identification number
         * \param newThreshold - New desired threshold
         */
        void edit_threshold_high(int sensorId, int newThreshold);
        /**
         * \brief Edits the lower threshold for a given sensorId.
         * \param sensorId - Sensor identification number
         * \param newThreshold - New desired threshold
         */
        void edit_threshold_low(int sensorId, int newThreshold);
        /**
         * \brief Edits the logging period for the application.
         * \param newPeriod - New logging period
         */
        void edit_logging_period(int newPeriod);
        /**
         * \brief Adds a command to run when upper threshold is exceeded.
         * \param sensorId - Sensor identification number
         * \param cmd - Command to run
         */
        void add_script_high_temp(int sensorId, string cmd);
        /**
         * \brief Removes a command to run when upper threshold is exceeded.
         * \param sensorId - Sensor identification number
         * \param cmdId - Command identification number to remove
         */
        void remove_script_high_temp(int sensorId, int cmdId);
        /**
         * \brief Adds a command to run when lower threshold is surpassed.
         * \param sensorId - Sensor identification number
         * \param cmd - Command to run
         */
        void add_script_low_temp(int sensorId, string cmd);
        /**
         * \brief Removes a command to run when lower threshold is surpassed.
         * \param sensorId - Sensor identification number
         * \param cmdId - Command identification number to remove
         */
        void remove_script_low_temp(int sensorId, int cmdId);
        /**
         * \brief Prints the configuration of the System in a human readable format.
         * \param mySystem - System shared pointer
         */
        void pretty_print_config(shared_ptr<System> mySystem);
    private:
        string _filename;
        /**
         * \brief Adds a command to run in the config.conf file for high or low thresholds.
         * \param sensorId - Sensor identification number
         * \param cmd - Command to run
         * \param highLow - ",H" or ",L" string value as identifier for which threshold the command is to run
         */
        void add_conf_file_command(int sensorId, string cmd, string highLow);
        /**
         * \brief Removes a command to run from the config.conf file for high or low thresholds.
         * \param sensorId - Sensor identification number
         * \param cmdId - Command identification number to remove
         * \param highLow - ",H" or ",L" string value as identifier for which threshold the command is to be removed
         */
        void remove_conf_file_command(int sensorId, int cmdId, string highLow);
        /**
         * \brief Edits the temperature threshold for a given sensorId.
         * \param sensorId - Sensor identification number
         * \param newThreshold - New desired threshold
         * \param highLow - ",H" or ",L" string value as identifier for which threshold to modify
         */
        void edit_temp_threshold(int sensorId, int newThreshold, string highLow);

};


#endif