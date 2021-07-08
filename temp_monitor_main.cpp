
#include "config_file_handler.h"
#include "temp_monitor.h"

using namespace std;


int main (int argc, char* argv[]) {
    ConfigFileHandler cfh;

    TempMonitor tm;
    TempMonitor::mySystem = cfh.parse_config_file();
    tm.monitor();
    return 0;
}

