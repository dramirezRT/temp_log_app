
#include "config_file_handler.h"
#include "temp_monitor.h"

using namespace std;

static shared_ptr<System> mySystem;

int main (int argc, char* argv[]) {
    ConfigFileHandler cfh;
    mySystem = cfh.parse_config_file();
    TempMonitor tm;
    tm.monitor();
    return 0;
}

