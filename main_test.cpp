#include "config_file_handler.h"
#include "systemd_misc.hpp"

int main (int argc, char* argv[]) {
    //parse_config_file();

    ConfigFileHandler cfh("./config.conf");
    // cfh.add_script_high_temp(0, "echo 'high'");
    // cfh.add_script_high_temp(2, "echo 'high'");
    // cfh.add_script_low_temp(0, "echo 'low'");
    // cfh.remove_script_high_temp(0, 0);
    // cfh.remove_script_high_temp(0, 1);
    // cfh.remove_script_high_temp(0, 2);
    // cfh.remove_script_high_temp(1, 0);
    // cfh.remove_script_high_temp(1, 1);
    // cfh.edit_threshold_high(0, 100);
    // cfh.edit_threshold_high(0, 1);
    // cfh.edit_threshold_high(3, 70);
    // cfh.edit_threshold_high(3, 100);
    // cfh.edit_threshold_high(3, 0);
    // cfh.edit_threshold_high(5, 100);
    // cfh.edit_threshold_high(5, 1);
    // cfh.edit_threshold_low(0, 100);
    // cfh.edit_threshold_low(0, 40);
    // cfh.edit_threshold_low(0, 5);
    // cfh.edit_threshold_low(2, 5);
    // cfh.edit_threshold_low(2, 100);
    // cfh.edit_threshold_low(2, 2);
    // cfh.edit_threshold_low(5, 100);
    cfh.edit_threshold_low(5, 1);
    // cfh.edit_logging_period(100);
    // cfh.edit_logging_period(10);
    // cfh.edit_logging_period(1);
    // SYSTEMD_MISC::daemon_reload();
    // SYSTEMD_MISC::restart_service();

    return 0;
}