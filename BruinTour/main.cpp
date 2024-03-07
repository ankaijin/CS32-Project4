
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "geodb.h"
#include "router.h"
#include "stops.h"
#include "tour_generator.h"
#include "HashMap.h"    // for testing purposes

using namespace std;

/*
void print_tour(vector<TourCommand> &tcs)
{
    double total_dist = 0;
    std::string direction;
    double street_distance = 0;

    cout << "Starting tour...\n";

    for (size_t i = 0; i < tcs.size(); ++i)
    {
        // cout << tcs[i] << endl;
        if (tcs[i].get_command_type() == TourCommand::commentary)
        {
            cout << "Welcome to " << tcs[i].get_poi() << "!\n";
            cout << tcs[i].get_commentary() << "\n";
        }
        else if (tcs[i].get_command_type() == TourCommand::turn)
        {
            cout << "Take a " << tcs[i].get_direction() << " turn on " << tcs[i].get_street() << endl;
        }
        else if (tcs[i].get_command_type() == TourCommand::proceed)
        {
            total_dist += tcs[i].get_distance();
            if (direction.empty())
                direction = tcs[i].get_direction();
            street_distance += tcs[i].get_distance();
            if (i < tcs.size() - 1 && tcs[i + 1].get_command_type() == TourCommand::proceed
                && tcs[i + 1].get_street() == tcs[i].get_street() && tcs[i].get_street() != GeoDatabase::kPathString)
            {
                continue;
            }

            cout << "Proceed " << std::fixed << std::setprecision(3) << street_distance << " miles " << direction << " on " << tcs[i].get_street() << endl;
            street_distance = 0;
            direction.clear();
        }
    }

    cout << "Your tour has finished!\n";
    cout << "Total tour distance: " << std::fixed << std::setprecision(3) << total_dist << " miles\n";
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "usage: BruinNav mapdata.txt stops.txt\n";
        return -1;
    }

    GeoDatabase geodb;
    if (!geodb.load(argv[1]))
    {
        cout << "Unable to load map data: " << argv[1] << endl;
        return -1;
    }

    Router router(geodb);
    TourGenerator tg(geodb, router);

    Stops stops;
    if (!stops.load(argv[2]))
    {
        cout << "Unable to load tour data: " << argv[2] << endl;
        return -1;
    }

    std::cout << "\nRouting...\n\n";

    string error;
    vector<TourCommand> tcs = tg.generate_tour(stops);
    if (tcs.empty())
        cout << "Unable to generate tour!\n";
    else
        print_tour(tcs);
}
*/

int main()
{
    /*
    HashMap<double> test(0.3); // when breakpoint is set to here, a problem occurs
    test.insert("Ankai", 4.5);
    test.insert("Salaba", 5.0);
    test.insert("Doodlers", 10.0);
    test.insert("Resize", 8);
    test.insert("Resize Again", 80);
    test.insert("Resize Again", 80.8);
    if (*(test.find("Resize Again")) == 80.8)
        cout << test.size() << endl;
    if (test.find("Nathan") == nullptr)
        cout << "looks like it works" << endl << endl;
    
    // new test cases
    double* DoodlersGPA = test.find("Doodlers");
    if (DoodlersGPA != nullptr)
        *DoodlersGPA = 4.6;
    cout << test["Doodlers"] << endl;
    test["Annie"] = 3.85;
    test["Annie"] = 3.95;
    cout << test["Linda"] << endl;
    */
    
    HashMap<string> test(0.3); // when breakpoint is set to here, a problem occurs
    test.insert("Ankai", "My name is Thomas");
    test.insert("Salaba", "Nathan Salaba");
    test.insert("Doodlers", "ankidoodle");
    test.insert("Resize Again", "time consuming");
    test.insert("Resize Again", "super time consuming");
    if (*(test.find("Resize Again")) == "super time consuming")
        cout << test.size() << endl;
    if (test.find("Nathan") == nullptr)
        cout << "looks like it works" << endl << endl;
    
    // new test cases
    string* DoodlersSays = test.find("Doodlers");
    if (DoodlersSays != nullptr)
        *DoodlersSays = "IAKNA";
    cout << test["Doodlers"] << endl;
    test["Annie"] = "Hi";
    test["Annie"] = "Hello peoplesrepublicofchina";
    if (test["Linda"] == "")
    cout << "This printed the empty string" << endl;
}
