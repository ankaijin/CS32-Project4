//
//  router.cpp
//  BruinTour
//
//  Created by Ankai Jin on 3/6/24.
//
#include <vector>
#include <queue>
#include <algorithm>   // for reverse
#include <unordered_set>

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
    
    HashMap<double> gScore;
    HashMap<double> fScore;
    HashMap<GeoPoint> locationOfPrevious;
    
    compareCosts comp(fScore);    // comparison object
    
    priority_queue<GeoPoint, vector<GeoPoint>, compareCosts> minHeap(comp);
    unordered_set<string> minHeapContents;
    minHeap.push(pt1);  // initially, only contains start point
    minHeapContents.insert(pt1.to_string());
    gScore.insert(pt1.to_string(), 0);  // g of start point is 0
    fScore.insert(pt1.to_string(), distance_earth_miles(pt1, pt2));

    while (!minHeap.empty())
    {
        GeoPoint lowest = minHeap.top();    // Extract the GeoPoint with lowest fScore
        minHeap.pop();
        minHeapContents.erase(lowest.to_string());

        if (lowest.to_string() == pt2.to_string())  // found end
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
        
        vector<GeoPoint> neighbors = myDatabase.get_connected_points(lowest);
        for (int i = 0; i < neighbors.size(); i++)
        {
            double tentativeG = gScore[lowest.to_string()] + distance_earth_miles(lowest, neighbors[i]);
            if (gScore.find(neighbors[i].to_string()) == nullptr || tentativeG < gScore[neighbors[i].to_string()])
            // not found before or better route found
            {
                locationOfPrevious[neighbors[i].to_string()] = lowest;
                gScore[neighbors[i].to_string()] = tentativeG;
                fScore[neighbors[i].to_string()] = tentativeG + distance_earth_miles(neighbors[i], pt2);
                if (minHeapContents.find(neighbors[i].to_string()) == minHeapContents.end())
                    // to avoid duplicate GeoPoints in the minheap
                {
                    minHeap.push(neighbors[i]);
                    minHeapContents.insert(neighbors[i].to_string());
                }
            }
        }
    }
    
    return path;    // no solution
}
