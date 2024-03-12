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

GeoDatabase::GeoDatabase() {}
GeoDatabase::~GeoDatabase() {}

bool GeoDatabase::load(const string& map_data_file)
{
    ifstream infile(map_data_file);
    if (!infile)
    {
        cerr << "error cannot open!" << endl;
        return false;   // placeholder
    }
    cerr << "file load success" << endl;
    
    string coordinates;
    string streetName, latitude, longitude; // endLat, endLong
    // GeoPoint start, end;
    int poiNum;
    string poiAddress;
    while (getline(infile, streetName)) // we are assuming that the infile is always correctly formatted
    {   // already read in streetName

        getline(infile, coordinates);   // get the second line
        istringstream iss(coordinates);
        
        iss >> latitude >> longitude;
        GeoPoint geopoint1(latitude, longitude);

        iss >> latitude >> longitude;
        GeoPoint geopoint2(latitude, longitude);
        
        GeoToGeo[geopoint1.to_string()].push_back(Ray(streetName, geopoint2));
        GeoToGeo[geopoint2.to_string()].push_back(Ray(streetName, geopoint1));
        GeoToStreet[geopoint1.to_string() + geopoint2.to_string()] = streetName;
        // associate concatenation of the two geoPoints with the streetName
        
        // read in poiNum
        infile >> poiNum;
        infile.ignore(10000, '\n');
        
        // if poiNum > 0 determine midpoint using midpoint()
        if (poiNum > 0)
        {
            GeoPoint geopointMid = midpoint(geopoint1, geopoint2);
            // bi-directional association with first point
            GeoToGeo[geopoint1.to_string()].push_back(Ray(streetName, geopointMid));
            GeoToGeo[geopointMid.to_string()].push_back(Ray(streetName, geopoint1));
            GeoToStreet[geopoint1.to_string() + geopointMid.to_string()] = streetName;
            // associate concatenation of the two geoPoints with streetName
            
            // bi-directional association with second point
            GeoToGeo[geopoint2.to_string()].push_back(Ray(streetName, geopointMid));
            GeoToGeo[geopointMid.to_string()].push_back(Ray(streetName, geopoint2));
            GeoToStreet[geopoint2.to_string() + geopointMid.to_string()] = streetName;
            // associate concatenation of the two geoPoints with streetName
            
            for (int i = poiNum; i > 0; i--)
            {
                getline(infile, poiAddress, '|');   // gets the line up to the delimiter
                getline(infile, coordinates);   // gets the coordinates after the delimiter
                iss.clear();
                iss.str(coordinates);
                iss >> latitude >> longitude;
                GeoPoint geopointPOI(latitude, longitude);
                POIToGeo[poiAddress] = geopointPOI;   // associate POI name with its GeoPoint
                // bi-directional association with midpoint
                GeoToGeo[geopointPOI.to_string()].push_back(Ray("a path", geopointMid));
                GeoToGeo[geopointMid.to_string()].push_back(Ray("a path", geopointPOI));
                GeoToStreet[geopointPOI.to_string() + geopointMid.to_string()] = "a path";
            }
        }
    }
    return true;
}

bool GeoDatabase::get_poi_location(const string& poi, GeoPoint& point) const
{
    const GeoPoint* poiLocation = POIToGeo.find(poi);
    if (poiLocation == nullptr)
        return false;   // POI not found
    point = *poiLocation;
    return true;
}

vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const
{
    vector<GeoPoint> connectedPoints(0);
    vector<Ray> sourceVector(0);
    if (GeoToGeo.find(pt.to_string()) != nullptr)   // find does not return a nullptr
        sourceVector = *(GeoToGeo.find(pt.to_string()));
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
    /*
    vector<Ray> sourceVector(0);
    if (GeoToGeo.find(pt1.to_string()) != nullptr)   // find does not return a nullptr
        sourceVector = *(GeoToGeo.find(pt1.to_string()));
    for (int i = 0; i < sourceVector.size(); i++)
        if (sourceVector[i].endpoint.to_string() == pt2.to_string())
            return sourceVector[i].streetName;
    */
    const string* findStreet = GeoToStreet.find(pt1.to_string() + pt2.to_string());
    if (findStreet != nullptr)  // check for combination 1
        return *findStreet;
    findStreet = GeoToStreet.find(pt2.to_string() + pt1.to_string());
    if (findStreet != nullptr)  // check for combination 2
        return *findStreet;
    return "";  // no segment found
}
