//
//  router.cpp
//  BruinTour
//
//  Created by Ankai Jin on 3/6/24.
//
#include <vector>
#include <queue>
#include <algorithm>   // for reverse

#include "router.h"
#include "geotools.h"

using namespace std;

Router::Router(const GeoDatabaseBase& geo_db)
 : myDatabase(geo_db) {}

Router::~Router() {}

vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const
{
    vector<GeoPoint> path(0);
    
    // if points aren't in the map, don't do anything
    if (myDatabase.get_connected_points(pt1).size() == 0 || myDatabase.get_connected_points(pt2).size() == 0)
        return path;
    
    std::priority_queue<GeoPointCost, std::vector<GeoPointCost>, compareCosts> minHeap;
    minHeap.push(GeoPointCost(pt1, 0, distance_earth_miles(pt1, pt2))); // g = 0, h is straight line distance
    // heuristic function is distance_earth_miles
    HashMap<GeoPoint> visited;
    HashMap<GeoPoint> locationOfPrevious;

    while (!minHeap.empty())
    {
        GeoPointCost lowest = minHeap.top();    // Extract the GeoPoint with lowest fScore
        visited[lowest.myPoint.to_string()] = lowest.myPoint;   // mark this point as visited

        if (lowest.myPoint.to_string() == pt2.to_string())  // found end
        {
            GeoPoint currentPoint = pt2;
            
            while (currentPoint.to_string() != pt1.to_string())
            {
                path.push_back(currentPoint);
                currentPoint = locationOfPrevious[currentPoint.to_string()];
            }
            path.push_back(pt1);
            reverse(path.begin(), path.end()); // reverse the vector
            return path;    // placeHolder
        }

        minHeap.pop(); // Remove current GeoPoint from minHeap
        
        vector<GeoPoint> neighbors = myDatabase.get_connected_points(lowest.myPoint);
        for (int i = 0; i < neighbors.size(); i++)
        {
            if (visited.find(neighbors[i].to_string()) == nullptr)  // if not already visited
            {
                locationOfPrevious[neighbors[i].to_string()] = lowest.myPoint;  // track where it came from
                double nextG = lowest.gScore + distance_earth_miles(lowest.myPoint, neighbors[i]);
                double nextH = distance_earth_miles(neighbors[i], pt2);
                minHeap.push(GeoPointCost(neighbors[i], nextG, nextH));
            }
        }
    }
    
    return path;    // no solution
}
