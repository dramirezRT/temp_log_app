
#include "config_file_handler.h"
#include "temp_monitor.h"

using namespace std;


int main (int argc, char* argv[]) {
    ConfigFileHandler cfh;

    TempMonitor::mySystem = cfh.parse_config_file();
    TempMonitor tm;
    tm.monitor();
    return 0;
}

