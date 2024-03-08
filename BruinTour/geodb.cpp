//
//  geodb.cpp
//  BruinTour
//
//  Created by Ankai Jin on 3/6/24.
//
#include <iostream> // needed for any I/O
#include <fstream>  // needed in addition to <iostream> for file I/O
#include <sstream>  // needed in addition to <iostream> for string stream I/O
#include <string>

#include "geodb.h"
// #include "geopoint.h"

using namespace std;

bool GeoDatabase::load(const string& map_data_file)
{
    ifstream infile(map_data_file);
    if (!infile)
    {
        cerr << "error cannot open!" << endl;
        return false;   // placeholder
    }
    cerr << "file load success" << endl;
    
    string currentLine;
    string streetName, latitude, longitude; // endLat, endLong
    // GeoPoint start, end;
    int poiNum;
    string poiAddress;
    while (getline(infile, currentLine)) // we are assuming that the infile is always correctly formatted
    {   // already read in streetName
        streetName = currentLine;

        getline(infile, currentLine);   // get the second line
        istringstream iss(currentLine);
        
        iss >> latitude >> longitude;
        GeoPoint geopoint1(latitude, longitude);
        
        iss >> latitude >> longitude;
        GeoPoint geopoint2(latitude, longitude);
        
        GeoToGeo[geopoint1.to_string()].push_back(Ray(streetName, geopoint2));
        GeoToGeo[geopoint2.to_string()].push_back(Ray(streetName, geopoint1));
        
        // read in poiNum
        infile >> poiNum;
        infile.ignore(10000, '\n');
        
        // if poiNum > 0 determine midpoint using midpoint()
        // connect midpoint to both endpoints using the segment's street name!
        // connect poi to midpoint using "a path" as the street name
        // for (int i = poiNum; i > 0; i--),
        // insert that POI into HashMap 2
        // remember to throw away the extra character '|'
    }
    return true;
}

bool GeoDatabase::get_poi_location(const string& poi, GeoPoint& point) const
{
    return false;   // placeholder
}

vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const
{
    vector<GeoPoint> connectedPoints(0);
    vector<Ray> sourceVector = *(GeoToGeo.find(pt.to_string()));
    if (sourceVector.size() == 0)  // find returns a vector pointer
        return connectedPoints; // return empty vector
    for (int i = 0; i < sourceVector.size(); i++)
    {
        connectedPoints.push_back(sourceVector[i].endpoint);
    }
    return connectedPoints;
}

string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const
{
    return "";  // placeholder
}
