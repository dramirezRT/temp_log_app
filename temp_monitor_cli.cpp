#include <iostream>
#include <string>

#include "ascii_art.h"
#include "config_file_handler.h"
#include "systemd_misc.hpp"


using namespace std;

void showUsage(string programName){
    cerr << "Usage: " << programName << " [OPTION] [VALUE]...\n" <<
    "CLI tool to monitor the temperatures in the platform\n" <<
    "Options:\n" <<
    "\t-h, --help\t\t\t\tDisplays usage information\n" <<
    "\t-w, --display-welcome\t\t\tDisplays a cool welcome logo :)\n" <<
    "\t-d, --display-config\t\t\tShows current config\n" <<
    "\t-s, --start-monitor\t\t\tStart monitoring the CPU temperature\n" <<
    "\t--edit-temp-limit-high\t\t\tEdit what is considered a high temperature value for a sensor [SENSOR_ID] [TEMP]\n" <<
    "\t--edit-temp-limit-low\t\t\tEdit what is considered a low temperature value [SENSOR_ID] [TEMP]\n" <<
    "\t--edit-logging-period\t\t\tEdit the logging period for the sensors [PERIOD]\n" <<
    "\t--add-script-on-high-temp\t\tAdd a script to run when the temperature is exceeded [SENSOR_ID] [COMMAND]\n" <<
    "\t--remove-script-on-high-temp\t\tRemove a script from running when the temperature is exceeded\n" <<
    "\t--add-script-on-low-temp\t\tAdd a script to run when the temperature is below the threshold [SENSOR_ID] [COMMAND]\n" <<
    "\t--remove-script-on-low-temp\t\tRemove a script from running when the temperature is below the threshold" << endl;
}

int main (int argc, char* argv[]) {

    if (argc > 4 || argc == 1)
    {
        showUsage(argv[0]);
        return 1;
    }
    ConfigFileHandler cfh;
    string arg = argv[1];
    if (arg == "-h" || arg == "--help")
    {
        showUsage(argv[0]);
    } else if (arg == "-w" || arg == "--display-welcome")
    {
        cout << rimacWelcome << endl;
    } else if (arg == "-d" || arg == "--display-config")
    {
        shared_ptr<System> mySystem = cfh.parse_config_file();
        cfh.prettyPrintConfig(mySystem);
        SYSTEMD_MISC::status_service();
    } else if (arg == "-s" || arg == "--start-monitor")
    {
        SYSTEMD_MISC::start_service();
    } else if (arg == "--edit-temp-limit-high")
    {
        if (argc != 4)
        {
            showUsage(argv[0]);
            return 1;
        }
        int sensorId = stoi(argv[2]);
        int newThreshold = stoi(argv[3]);
        cfh.edit_threshold_high(sensorId, newThreshold);
        SYSTEMD_MISC::daemon_reload();
        SYSTEMD_MISC::restart_service();
    } else if (arg == "--edit-temp-limit-low")
    {
        if (argc != 4)
        {
            showUsage(argv[0]);
            return 1;
        }
        int sensorId = stoi(argv[2]);
        int newThreshold = stoi(argv[3]);
        cfh.edit_threshold_low(sensorId, newThreshold);
        SYSTEMD_MISC::daemon_reload();
        SYSTEMD_MISC::restart_service();
    }  else if (arg == "--edit-logging-period")
    {
        if (argc != 4)
        {
            showUsage(argv[0]);
            return 1;
        }
        int sensorId = stoi(argv[2]);
        int newPeriod = stoi(argv[3]);
        cfh.edit_logging_period(sensorId, newPeriod);
        SYSTEMD_MISC::daemon_reload();
        SYSTEMD_MISC::restart_service();
    }else if (arg == "--add-script-on-high-temp")
    {
        if (argc != 4)
        {
            showUsage(argv[0]);
            return 1;
        }
        int sensorId = stoi(argv[2]);
        string cmd = argv[3];
        cfh.add_script_high_temp(sensorId, cmd);
        SYSTEMD_MISC::daemon_reload();
        SYSTEMD_MISC::restart_service();
    } else if (arg == "--remove-script-on-high-temp")
    {
        /* code */
    } else if (arg == "--add-script-on-low-temp")
    {
        if (argc != 4)
        {
            showUsage(argv[0]);
            return 1;
        }
        int sensorId = stoi(argv[2]);
        string cmd = argv[3];
        cfh.add_script_low_temp(sensorId, cmd);
        SYSTEMD_MISC::daemon_reload();
        SYSTEMD_MISC::restart_service();
    } else if (arg == "--remove-script-on-low-temp")
    {
        /* code */
    } else 
    {
        showUsage(argv[0]);
        return 1;
    }
    
    return 0;
}