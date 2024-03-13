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
#include "geotools.h"
#include "HashMap.h"

class GeoDatabase : public GeoDatabaseBase
{
  public:
    GeoDatabase();
    virtual ~GeoDatabase();
    
    virtual bool load(const std::string& map_data_file);
    virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const;   // uses HashMap 2
    virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;   // uses HashMap 1
    virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;    // uses HashMap 3
    
  private:  // check if this works
    HashMap<std::vector<GeoPoint>> GeoToGeo; // 1, larger
    HashMap<GeoPoint> POIToGeo; // 2, smaller
    HashMap<std::string> GeoToStreet; // 3
};

#endif /* geodb_hpp */
