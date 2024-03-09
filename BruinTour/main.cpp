
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "geodb.h"
#include "router.h"
#include "stops.h"
#include "tour_generator.h"
// #include "HashMap.h"    // for testing purposes
// #include "geopoint.h"   // for testing purposes

using namespace std;

/*
 void print_tour(vector<TourCommand>& tcs)
 {
     double total_dist = 0;
     std::string direction;
     double street_distance = 0;

     cout << "Starting tour...\n";

     for (size_t i = 0; i < tcs.size(); ++i)
     {
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
             if (i+1 < tcs.size() && tcs[i+1].get_command_type() == TourCommand::proceed
                 && tcs[i+1].get_street() == tcs[i].get_street() && tcs[i].get_street() != "a path")
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
         cout << "usage: BruinTour mapdata.txt stops.txt\n";
         return 1;
     }

     GeoDatabase geodb;
     if (!geodb.load(argv[1]))
     {
         cout << "Unable to load map data: " << argv[1] << endl;
         return 1;
     }

     Router router(geodb);
     TourGenerator tg(geodb, router);

     Stops stops;
     if (!stops.load(argv[2]))
     {
         cout << "Unable to load tour data: " << argv[2] << endl;
         return 1;
     }

     std::cout << "Routing...\n\n";

     vector<TourCommand> tcs = tg.generate_tour(stops);
     if (tcs.empty())
         cout << "Unable to generate tour!\n";
     else
         print_tour(tcs);
 }
*/


int main()
{
    GeoDatabase g1;
    g1.load("/Users/ankaijin/Desktop/CS32 Xcode/BruinTour/CS32-Project4/BruinTour/mapdata.txt");
    
    Router test1(g1);
    GeoPoint point1("34.0625329", "-118.4470263");
    GeoPoint point2("34.0685657", "-118.4489289");
    g1.get_poi_location("Diddy Riese", point1);
    g1.get_poi_location("Ami Sushi", point2);
    vector<GeoPoint> please = test1.route(point1, point2);
    for (int i = 0; i < please.size(); i++)
    {
        cout << please[i].to_string() << endl;
    }
}

