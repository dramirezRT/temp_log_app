#ifndef CONFIG_FILE_PARSER
#define CONFIG_FILE_PARSER

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "temp_monitor.h"

using namespace std;

static void parse_config_file () {
    ifstream configFile;
    try
    {
        configFile.open("./config.conf", ios::in);
        if (!configFile.is_open())
        {
            throw "Could not open the config.conf file!";
        } else {
            string line;
            while (getline(configFile, line))
            {
                // Cleanup the line
                // Remove comments
                int eraseFrom = line.find("#");
                if (eraseFrom != string::npos)
                {
                    line.erase(eraseFrom, line.end());
                }
                // Try to remove from the first space found
                eraseFrom = line.find(" ");
                if (eraseFrom != string::npos)
                {
                    line.erase(eraseFrom, line.end());
                }
                // Try to remove from the first tab key found
                eraseFrom = line.find("\t");
                if (eraseFrom != string::npos)
                {
                    line.erase(eraseFrom, line.end());
                }
                if (line.size() > 0)
                {
                    int equalsSign = line.find("=");
                    string var = line.substr(line.begin(), equalsSign-1);
                    string val = line.substr(equalsSign, line.end());
                    if (var == "highTempLimit")
                    {
                        TEMP_MONITOR::highTempLimit = stoi(val);
                    } else if (var == "lowTempLimit")
                    {
                        /* code */
                    } else if (var == "loggingPeriod")
                    {
                        /* code */
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
}

#endif