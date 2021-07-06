#include <iostream>
#include <string>
#include <boost/program_options.hpp>

#include "ascii_art.h"


using namespace std;
namespace po = boost::program_options;



int main (int argc, char* argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("start-monitor", po::value<bool>()->default_value(true), "Start monitoring the CPU temperature")
        ("edit-temp-limit-high", po::value<bool>()->default_value(true), "Edit what is considered a high temperature value")
        ("edit-temp-limit-low", po::value<bool>()->default_value(true), "Edit what is considered a low temperature value")
        ("add-script-on-high-temp", po::value<bool>(), "Add a script to run when the temperature is exceeded")
        ("remove-script-on-high-temp", po::value<bool>(), "Remove a script from running when the temperature is exceeded")
        ("add-script-on-low-temp", po::value<bool>(), "Add a script to run when the temperature is below the threshold")
        ("remove-script-on-low-temp", po::value<bool>(), "Remove a script from running when the temperature is below the threshold")
    ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);



    cout << rimacWelcome << endl;


    return 0;
}