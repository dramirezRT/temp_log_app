#include <iostream>
#include <string>

#include "ascii_art.h"


using namespace std;

void showUsage(string programName){
    cerr << "Usage: " << programName << "[OPTION] [VALUE]\n" <<
    "CLI tool to monitor the temperatures in the platform\n" <<
    "Options:\n" <<
    "\t-h, --help\t\t\t\tDisplays usage information\n" <<
    "\t-d, --display-welcome\t\t\tDisplays a cool welcome logo :)\n" <<
    "\t-s, --start-monitor\t\t\tStart monitoring the CPU temperature\n" <<
    "\t--edit-temp-limit-high\t\t\tEdit what is considered a high temperature value for a sensor\n" <<
    "\t--edit-temp-limit-low\t\t\tEdit what is considered a low temperature value\n" <<
    "\t--add-script-on-high-temp\t\tAdd a script to run when the temperature is exceeded\n" <<
    "\t--remove-script-on-high-temp\t\tRemove a script from running when the temperature is exceeded\n" <<
    "\t--add-script-on-low-temp\t\tAdd a script to run when the temperature is below the threshold\n" <<
    "\t--remove-script-on-low-temp\t\tRemove a script from running when the temperature is below the threshold" << endl;
}

int main (int argc, char* argv[]) {

    if (argc > 3 || argc == 1)
    {
        showUsage(argv[0]);
        return 1;
    }
    string arg = argv[1];
    if (arg == "-h" || arg == "--help")
    {
        showUsage(argv[0]);
    } else if (arg == "-d" || arg == "--display-welcome")
    {
        cout << rimacWelcome << endl;
    } else if (arg == "--edit-temp-limit-high")
    {
        /* code */
    } else if (arg == "--edit-temp-limit-low")
    {
        /* code */
    } else if (arg == "--add-script-on-high-temp")
    {
        /* code */
    } else if (arg == "--remove-script-on-high-temp")
    {
        /* code */
    } else if (arg == "--add-script-on-low-temp")
    {
        /* code */
    } else if (arg == "--remove-script-on-low-temp")
    {
        /* code */
    } else 
    {
        showUsage(argv[0]);
        return 1;
    }
    
    return 0;
}