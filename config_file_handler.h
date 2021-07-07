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
        static shared_ptr<System> parse_config_file ();
};


#endif