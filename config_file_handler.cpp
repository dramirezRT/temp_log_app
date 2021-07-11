#include "config_file_handler.h"

shared_ptr<System> ConfigFileHandler::parse_config_file () {
    ifstream configFile;
    vector<shared_ptr<Sensor>> sensors;
    int loggingPeriod;
    try
    {
        configFile.open(_filename, ios::in);
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
    
    return result;
}

void ConfigFileHandler::edit_threshold_high(int sensorId, int newThreshold){
    edit_temp_threshold(sensorId, newThreshold, "H");
}

void ConfigFileHandler::edit_threshold_low(int sensorId, int newThreshold){
    edit_temp_threshold(sensorId, newThreshold, "L");
}

void ConfigFileHandler::edit_logging_period(int newPeriod){
    fstream configFile;
    string file;
    try
    {
        configFile.open(_filename, ios::in | ios::out);
        if (!configFile.is_open())
        {
            throw runtime_error("Could not open the config.conf file!");
        } else {
            string line;
            int sensor = 0;
            while (getline(configFile, line))
            {
                int eraseFrom = line.find("#");
                if (eraseFrom == 0) // It's a comment
                {
                    // cout << line << endl;
                    file.append(line.append("\n"));
                    continue;
                }
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
                    if (line.find(",") != string::npos) // It's a sensor config line
                    {
                        // cout << line << endl;
                        file.append(line.append("\n"));
                        continue;
                    }
                    // Try to remove from the first space found
                    eraseFrom = line.find(" ");
                    if (eraseFrom != string::npos)
                    {
                        line.erase(eraseFrom);
                    }
                    int equalsSign = line.find("=");
                    equalsSign++;
                    line.replace(equalsSign, line.size()-equalsSign, to_string(newPeriod));
                }
                // cout << line << endl;
                file.append(line.append("\n"));
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    configFile.close();
    configFile.open(_filename, ios::out | ios::trunc);
    configFile << file;
    configFile.close();
}

void ConfigFileHandler::add_script_high_temp(int sensorId, string cmd){
    addConfFileCommand(sensorId, cmd, ",H");
}

void ConfigFileHandler::remove_script_high_temp(int sensorId, int cmdId){
    removeConfFileCommand(sensorId, cmdId, ",H");
}

void ConfigFileHandler::add_script_low_temp(int sensorId, string cmd){
    addConfFileCommand(sensorId, cmd, ",L");
}

void ConfigFileHandler::remove_script_low_temp(int sensorId, int cmdId){
    removeConfFileCommand(sensorId, cmdId, ",L");
}

void ConfigFileHandler::addConfFileCommand(int sensorId, string cmd, string highLow) {
    fstream configFile;
    string file;
    try
    {
        configFile.open(_filename, ios::in | ios::out);
        if (!configFile.is_open())
        {
            throw runtime_error("Could not open the config.conf file!");
        } else {
            string line;
            int sensor = 0;
            while (getline(configFile, line))
            {
                if (line.find("#") == string::npos &&
                    line.find(",") != string::npos)
                {
                    if (sensorId == sensor)
                    {
                        line.append(highLow.append(cmd));
                        // cout << line << endl;
                    }
                    sensor++;
                }
                // cout << line << endl;
                file.append(line.append("\n"));
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    configFile.clear();
    configFile.seekg(0);
    configFile << file;
    configFile.close();
}

void ConfigFileHandler::removeConfFileCommand(int sensorId, int cmdId, string highLow) {
    fstream configFile;
    string file;
    try
    {
        configFile.open(_filename, ios::in | ios::out);
        if (!configFile.is_open())
        {
            throw runtime_error("Could not open the config.conf file!");
        } else {
            string line;
            int sensor = 0;
            while (getline(configFile, line))
            {
                if (line.find("#") == string::npos &&
                    line.find(",") != string::npos)
                {
                    if (sensorId == sensor)
                    {
                        int leftIndex = line.find(highLow);
                        int rightIndex = 0;
                        int count = 0;
                        while (leftIndex != string::npos)
                        {
                            rightIndex = line.find(",", leftIndex+1);
                            if (rightIndex == string::npos) // Last item in line
                            {
                                rightIndex = line.size()-1;
                            }
                            
                            if (count == cmdId)
                            {
                                // Erase from leftIndex to rightIndex
                                line.erase(leftIndex, rightIndex - leftIndex);
                                // cout << "found -> " << leftIndex << " : " << rightIndex << endl;
                                break;
                            }
                            count++;
                            leftIndex = line.find(highLow, rightIndex);
                        }
                    }
                    sensor++;
                }
                // cout << line << endl;
                file.append(line.append("\n"));
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    configFile.close();
    configFile.open(_filename, ios::out | ios::trunc);
    configFile << file;
    configFile.close();
}

void ConfigFileHandler::edit_temp_threshold(int sensorId, int newThreshold, string highLow) {
    fstream configFile;
    string file;
    try
    {
        configFile.open(_filename, ios::in | ios::out);
        if (!configFile.is_open())
        {
            throw runtime_error("Could not open the config.conf file!");
        } else {
            string line;
            int sensor = 0;
            while (getline(configFile, line))
            {
                int commaPos = line.find(",");
                if (line.find("#") == string::npos &&
                    commaPos != string::npos)
                {
                    if (sensorId == sensor)
                    {
                        commaPos++;
                        if (highLow == "H")
                        {
                            int secondCommaPos = line.find(",", commaPos);
                            line.replace(commaPos, secondCommaPos-commaPos,to_string(newThreshold));
                        } else {    // Assume Low threshold
                            commaPos = line.find(",", commaPos)+1;
                            int secondCommaPos = line.find(",", commaPos);
                            line.replace(commaPos, secondCommaPos-commaPos,to_string(newThreshold));
                        }
                    }
                    sensor++;
                }
                // cout << line << endl;
                file.append(line.append("\n"));
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    configFile.close();
    configFile.open(_filename, ios::out | ios::trunc);
    configFile << file;
    configFile.close();
}

void ConfigFileHandler::prettyPrintConfig(shared_ptr<System> mySystem){
    cout << "\nSummary from the config.conf file!" << endl;

    int sensorId = 0;
    for (shared_ptr<Sensor> sensor : mySystem->getSensorsConfig())
    {
        cout << "Sensor" << sensorId << ": " << sensor->getSensor() << 
        " \n\tHighTempThresh: " << sensor->getHighTempThresh();
        int cmdId = 0;
        for(string cmd : sensor->getHighTempThreshCmd()){
            cout << "\n\t\t" << cmdId << ")\t" << cmd;
            cmdId++;
        }
        cout << "\n\tLowTempThresh: " << sensor->getLowTempThresh();
        cmdId = 0;
        for(string cmd : sensor->getLowTempThreshCmd()){
            cout << "\n\t\t" << cmdId << ")\t" << cmd;
            cmdId++;
        }
        cout << endl;
        sensorId++;
    }
    
    cout << "loggingPeriod: " << mySystem->getLoggingPeriod() << endl << endl;
}
