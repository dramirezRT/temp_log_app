#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>

#include "config_file_handler.h"
#include "temp_monitor.h"

using namespace std;

string Sensor::get_sensor() { return _sensor; }
vector<string> Sensor::get_high_temp_thresh_cmd(){ return _highTempThreshCmds; }
vector<string> Sensor::get_low_temp_thresh_cmd(){ return _lowTempThreshCmds; }
int Sensor::get_high_temp_thresh(){ return _highTempThresh; }
int Sensor::get_low_temp_thresh(){ return _lowTempThresh; }
void Sensor::set_high_temp_thresh(int threshold){ _highTempThresh = threshold; }
void Sensor::set_low_temp_thresh(int threshold) { _lowTempThresh = threshold; }

int System::get_logging_period(){ return _loggingPeriod; }
vector<shared_ptr<Sensor>> System::get_sensors_config(){ return _sensorsConfig; }


void TempMonitor::execute_cmd(string cmd){
    system(cmd.c_str());
}

void TempMonitor::monitor() {
    while (true)
    {
        for(shared_ptr<Sensor> sensor: mySystem->get_sensors_config()){
            ifstream sensorFile;
            string temp;
            try
            {
                sensorFile.open(sensor->get_sensor(), ios::in);
                if (!sensorFile.is_open())
                {
                    throw runtime_error("Could not open the sensor file!");
                } else {
                    getline(sensorFile, temp);
                    stringstream ss;
                    ss << fixed << setprecision(2) << stof(temp)/1000;
                    float currentTemp = stof(ss.str());
                    auto now = std::chrono::system_clock::now();
                    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
                    if (currentTemp > sensor->get_high_temp_thresh())
                    {
                        cerr << ctime(&now_time) << "\tHigh temperature alert for sensor: " << sensor->get_sensor() << " is: " << currentTemp << "°C" << endl;
                        for(string cmd : sensor->get_high_temp_thresh_cmd()){
                            execute_cmd(cmd);
                        }
                    } else if (currentTemp < sensor->get_low_temp_thresh())
                    {
                        cerr << ctime(&now_time) << "\tLow temperature alert for sensor: " << sensor->get_sensor() << " is: " << currentTemp << "°C" << endl;
                        for(string cmd : sensor->get_low_temp_thresh_cmd()){
                            execute_cmd(cmd);
                        }
                    }
                    cout << ctime(&now_time) << "\tCurrent temperature for sensor: " << sensor->get_sensor() << " is: " << currentTemp << "°C" << endl;
                    
                }
                sensorFile.close();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return;
            }
        }
        this_thread::sleep_for(chrono::seconds(mySystem->get_logging_period()));
    }
    
}
