//
//  geodb.hpp
//  BruinTour
//
//  Created by Ankai Jin on 3/6/24.
//

#ifndef geodb_hpp
#define geodb_hpp

#include <string>
#include <vector>

#include "base_classes.h"
#include "geopoint.h"
#include "HashMap.h"

class GeoDatabase : public GeoDatabaseBase
{
  public:
    GeoDatabase() {}
    virtual ~GeoDatabase() {}
    
    bool load(const std::string& map_data_file);
    bool get_poi_location(const std::string& poi, GeoPoint& point) const;   // uses HashMap 2
    std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;   // uses HashMap 1
    std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;    // uses HashMap 1
    
  private:  // check if this works
    struct Ray
    {
        Ray(const std::string& street, const GeoPoint& point)
         : streetName(street), endpoint(point) {}
        std::string streetName;
        GeoPoint endpoint;
    };
    HashMap<std::vector<Ray>> GeoToGeo; // 1, larger
    HashMap<GeoPoint> POIToGeo; // 2, smaller
};

#endif /* geodb_hpp */
