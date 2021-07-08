#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>

#include "config_file_handler.h"
#include "temp_monitor.h"

using namespace std;

static shared_ptr<System> mySystem;

string Sensor::getSensor() { return _sensor; }
vector<string> Sensor::getHighTempThreshCmd(){ return _highTempThreshCmds; }
vector<string> Sensor::getLowTempThreshCmd(){ return _lowTempThreshCmds; }
int Sensor::getHighTempThresh(){ return _highTempThresh; }
int Sensor::getLowTempThresh(){ return _lowTempThresh; }
void Sensor::setHighTempThresh(int threshold){ _highTempThresh = threshold; }
void Sensor::setLowTempThresh(int threshold) { _lowTempThresh = threshold; }
// void Sensor::addHighTempThreshCmd(string cmd){ _highTempThreshCmds.push_back(cmd); }
// void Sensor::removeHighTempThreshCmd(int index){}
// void Sensor::addLowTempThreshCmd(string cmd){ _lowTempThreshCmds.push_back(cmd); }
// void Sensor::removeLowTempThreshCmd(int index){}

int System::getLoggingPeriod(){ return _loggingPeriod; }
vector<shared_ptr<Sensor>> System::getSensorsConfig(){return _sensorsConfig; }


void executeCmd(string cmd){
    system(cmd.c_str());
}

void monitor() {
    while (true)
    {
        for(shared_ptr<Sensor> sensor: mySystem->getSensorsConfig()){
            ifstream sensorFile;
            string temp;
            try
            {
                sensorFile.open(sensor->getSensor(), ios::in);
                if (!sensorFile.is_open())
                {
                    throw runtime_error("Could not open the sensor file!");
                } else {
                    getline(sensorFile, temp);
                    stringstream ss;
                    ss << fixed << setprecision(2) << stof(temp)/1000;
                    float currentTemp = stof(ss.str());
                    if (currentTemp > sensor->getHighTempThresh())
                    {
                        cerr << "High temperature alert for sensor: " << sensor->getSensor() << " is: " << currentTemp << "°C" << endl;
                        for(string cmd : sensor->getHighTempThreshCmd()){
                            executeCmd(cmd);
                        }
                    } else if (currentTemp < sensor->getLowTempThresh())
                    {
                        cerr << "Low temperature alert for sensor: " << sensor->getSensor() << " is: " << currentTemp << "°C" << endl;
                        for(string cmd : sensor->getLowTempThreshCmd()){
                            executeCmd(cmd);
                        }
                    }
                    cout << "Current temperature for sensor: " << sensor->getSensor() << " is: " << currentTemp << "°C" << endl;
                    
                }
                sensorFile.close();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return;
            }
        }
        this_thread::sleep_for(chrono::seconds(mySystem->getLoggingPeriod()));
    }
    
}

// int main (int argc, char* argv[]) {
//     ConfigFileHandler cfh;
//     mySystem = cfh.parse_config_file();
//     monitor();
//     return 0;
// }

