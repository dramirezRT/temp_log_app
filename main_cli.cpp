#include <iostream>
#include <string>
#include <boost/program_options.hpp>

#include "ascii_art.h"


using namespace std;
namespace po = boost::program_options;



int main (int argc, char* argv[]) {
    string addScriptOnHighTemp, addScriptOnLowTemp = "";

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Displays usage information")
        ("display-info,d", po::value<bool>()->default_value(false), "Displays info from the running program")
        ("start-monitor,s", po::value<bool>()->default_value(false), "Start monitoring the CPU temperature")
        ("edit-temp-limit-high", po::value<int>(), "Edit what is considered a high temperature value")
        ("edit-temp-limit-low", po::value<int>(), "Edit what is considered a low temperature value")
        ("add-script-on-high-temp", po::value<string>(), "Add a script to run when the temperature is exceeded")
        ("remove-script-on-high-temp", po::value<int>(), "Remove a script from running when the temperature is exceeded")
        ("add-script-on-low-temp", po::value<string>(), "Add a script to run when the temperature is below the threshold")
        ("remove-script-on-low-temp", po::value<int>(), "Remove a script from running when the temperature is below the threshold")
        ("display-welcome,w", po::value<bool>()->default_value(false), "Displays a cool welcome logo :)")
    ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help,h"))
    {
        cout << desc << endl;
        return 0;
    }
    

    cout << rimacWelcome << endl;


    return 0;
}