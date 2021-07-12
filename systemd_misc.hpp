#ifndef SYSTEMD_MISC
#define SYSTEMD_MISC

#include <iostream>

#define SYSTEMD_DAEMON_RELOAD   "sudo systemctl daemon-reload"
#define SYSTEMD_RESTART_SVC     "sudo systemctl restart temp-monitor.service"
#define SYSTEMD_START_SVC       "sudo systemctl start temp-monitor.service"
#define SYSTEMD_STOP_SVC        "sudo systemctl stop temp-monitor.service"
#define SYSTEMD_ENABLE_SVC      "sudo systemctl enable temp-monitor.service"
#define SYSTEMD_STATUS_SVC      "sudo systemctl status temp-monitor.service"

using namespace std;
/**
 * \brief Reloads the systemd's services files.
 */
static void daemon_reload(){ system(SYSTEMD_DAEMON_RELOAD); }
/**
 * \brief Restarts the temp-monitor service.
 */
static void restart_service(){ system(SYSTEMD_RESTART_SVC); }
/**
 * \brief Starts the temp-monitor service.
 */
static void start_service(){ system(SYSTEMD_START_SVC); }
/**
 * \brief Stops the temp-monitor service.
 */
static void stop_service(){ system(SYSTEMD_STOP_SVC); }
/**
 * \brief Enables the temp-monitor service to autorun on target boot.
 */
static void enable_service(){ system(SYSTEMD_ENABLE_SVC); }
/**
 * \brief Displays the temp-monitor service current status.
 */
static void status_service(){ system(SYSTEMD_STATUS_SVC); }

#endif