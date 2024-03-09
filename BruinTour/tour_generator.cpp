//
//  tour_generator.cpp
//  BruinTour
//
//  Created by Ankai Jin on 3/6/24.
//

#include <vector>

#include "tour_generator.h"
#include "geotools.h"

using namespace std;

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router)
 : myDatabase(geodb), myRouter(router) {}

TourGenerator::~TourGenerator() {}

string TourGenerator::determineDirection(double angle) const
{
    if (angle >= 0 && angle < 22.5)
        return "east";
    else if (angle >= 22.5 && angle < 67.5)
        return "northeast";
    else if (angle >= 67.5 && angle < 112.5)
        return "north";
    else if (angle >= 112.5 && angle < 157.5)
        return "northwest";
    else if (angle >= 157.5 && angle < 202.5)
        return "west";
    else if (angle >= 202.5 && angle < 247.5)
        return "southwest";
    else if (angle >= 247.5 && angle < 292.5)
        return "south";
    else if (angle >= 292.5 && angle < 337.5)
        return "southeast";
    else
        return "east";
}

vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const
{
    vector<TourCommand> commands(0);
    string POI, prevPOI;
    string commentary, prevCommentary;
    
    if (stops.size() >= 0)
    {
        stops.get_poi_data(0, POI, commentary);
        TourCommand commentaryCommand;
        commentaryCommand.init_commentary(POI, commentary);
        commands.push_back(commentaryCommand);
    }
    
    for (int i = 1; i < stops.size(); i++)  // loops through POIs
    {
        prevPOI = POI;
        prevCommentary = commentary;
        stops.get_poi_data(i, POI, commentary);
        GeoPoint prevPoint, currPoint;
        myDatabase.get_poi_location(prevPOI, prevPoint);
        myDatabase.get_poi_location(POI, currPoint);
        vector<GeoPoint> navigation = myRouter.route(prevPoint, currPoint);
        for (int j = 1; j < navigation.size(); j++) // loops through GeoPoints
        {
            string dir, street, prevStreet;
            GeoPoint prevPoint2;
            double dist, turnAngle;
            if (j == 1)
            {
                TourCommand proceedCommand;
                prevPoint = navigation[j-1];
                currPoint = navigation[j];
                dir = determineDirection(angle_of_line(prevPoint, currPoint));
                street = myDatabase.get_street_name(prevPoint, currPoint);
                dist = distance_earth_miles(prevPoint, currPoint);
                proceedCommand.init_proceed(dir, street, dist, prevPoint, currPoint);
                commands.push_back(proceedCommand);
                continue;   // rest of code does not apply
            }
            // determine whether to add a turn command
            prevPoint2 = navigation[j-2];
            prevPoint = navigation[j-1];
            currPoint = navigation[j];
            prevStreet = myDatabase.get_street_name(prevPoint2, prevPoint);
            street = myDatabase.get_street_name(prevPoint, currPoint);
            turnAngle = angle_of_turn(prevPoint2, prevPoint, currPoint);
            if ((prevStreet != street) && (turnAngle > -1 && turnAngle < 1))
            {
                if (turnAngle >= 1 && turnAngle < 180)
                    dir = "left";
                else
                    dir = "right";
                TourCommand turnCommand;
                turnCommand.init_turn(dir, street);
                commands.push_back(turnCommand);
            }
            // always add a proceed command
            TourCommand proceedCommand;
            dir = determineDirection(angle_of_line(prevPoint, currPoint));
            dist = distance_earth_miles(prevPoint, currPoint);
            proceedCommand.init_proceed(dir, street, dist, prevPoint, currPoint);
            commands.push_back(proceedCommand);
        }
        
        TourCommand commentaryCommand;
        commentaryCommand.init_commentary(POI, commentary);
        commands.push_back(commentaryCommand);
    }
    
    return commands;
}
