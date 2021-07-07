#ifndef CONFIG_FILE_PARSER
#define CONFIG_FILE_PARSER

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <memory>

#include "temp_monitor.h"

using namespace std;

static shared_ptr<System> parse_config_file () {
    ifstream configFile;
    vector<shared_ptr<Sensor>> sensors;
    int loggingPeriod;
    try
    {
        configFile.open("./config_imx6.conf", ios::in);
        if (!configFile.is_open())
        {
            throw runtime_error("Could not open the config.conf file!");
        } else {
            string line;
            while (getline(configFile, line))
            {
                // Cleanup the line
                // Remove comments
                int eraseFrom = line.find("#");
                if (eraseFrom != string::npos)
                {
                    line.erase(eraseFrom);
                }
                // Try to remove from the first tab key found
                eraseFrom = line.find("\t");
                if (eraseFrom != string::npos)
                {
                    line.erase(eraseFrom);
                }
                if (line.size() > 0)
                {
                    int equalsSign = line.find("=");
                    if (equalsSign == string::npos)
                    {
                        int comma = line.find(",");
                        if (comma == string::npos)
                        {
                            continue;
                        }
                        int i = 0;
                        string sensor;
                        int highTempThresh;
                        int lowTempThresh;
                        vector<string> highTempThreshCmds;
                        vector<string> lowTempThreshCmds;
                        string value = line.substr(0, comma);
                        while (value.length() > 0)
                        {
                            if (i == 0) // Sensor string
                            {
                                sensor = value;
                            } else if (i == 1) // High Temp Threshold
                            {
                                highTempThresh = stoi(value);
                            } else if (i == 2) // Low Temp Threshold
                            {
                                lowTempThresh = stoi(value);
                            } else // i >= 3
                            {
                                int highOrLow = line.find("H");
                                if (highOrLow == 0) // Command for High Threshold
                                {
                                    highTempThreshCmds.push_back(value.substr(1));
                                } else { // Assume Command for Low Threshold
                                    lowTempThreshCmds.push_back(value.substr(1));
                                }
                            }
                            if (comma == string::npos) break;
                            
                            i++;
                            line.erase(0, comma+1);
                            comma = line.find(",");
                            if (comma == string::npos)
                            {
                                value = line;
                            } else {
                                value = line.substr(0, comma);
                            }
                        }
                        sensors.push_back(make_shared<Sensor>(
                            sensor,
                            highTempThresh,
                            lowTempThresh,
                            highTempThreshCmds,
                            lowTempThreshCmds
                        ));
                    } else
                    {
                        // Try to remove from the first space found
                        eraseFrom = line.find(" ");
                        if (eraseFrom != string::npos)
                        {
                            line.erase(eraseFrom);
                        }
                        string var = line.substr(0, equalsSign);
                        string val = line.substr(equalsSign+1);
                        // cout << "Line: " << line << " var: " << var << " val: " << val << endl;
                        if (var == "loggingPeriod")
                        {
                            loggingPeriod = stoi(val);
                        }
                    }
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    configFile.close();
    shared_ptr<System> result = make_shared<System>(
        sensors,
        loggingPeriod > 0 ? loggingPeriod : 5
    );

    cout << "\nValues updated from the configuration file!" << endl;

    for (shared_ptr<Sensor> sensor : result->getSensorsConfig())
    {
        cout << "Sensor: " << sensor->getSensor() << 
        " \n\tHighTempThresh: " << sensor->getHighTempThresh();
        for(string cmd : sensor->getHighTempThreshCmd())
            cout << "\n\t\t" << cmd;
        
        cout << "\n\tLowTempThresh: " << sensor->getLowTempThresh();
        for(string cmd : sensor->getLowTempThreshCmd())
            cout << "\n\t\t" << cmd;
        cout << endl;
    }
    
    cout << "loggingPeriod: " << result->getLoggingPeriod() << endl << endl;
    return result;
}


#endif