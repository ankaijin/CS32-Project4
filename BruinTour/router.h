//
//  router.hpp
//  BruinTour
//
//  Created by Ankai Jin on 3/6/24.
//

#ifndef router_hpp
#define router_hpp

#include "base_classes.h"
#include "geopoint.h"
#include "HashMap.h"

class Router: public RouterBase
{
  public:
    Router(const GeoDatabaseBase& geo_db);
    virtual ~Router();
    virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
  private:
    struct compareCosts // used as comparison operator for priority queue
    {
      public:
        compareCosts(const HashMap<double>& fValues)
         : fValueMap(fValues) {}
        bool operator()(const GeoPoint& a, const GeoPoint& b) const
        {
            // set either side to default max value if not found? Shouldn't be possible right?
            if (fValueMap.find(a.to_string()) == nullptr)
                return true;
            if (fValueMap.find(b.to_string()) == nullptr)
                return false;
            return *(fValueMap.find(a.to_string())) > *(fValueMap.find(b.to_string()));
        }
      private:
        const HashMap<double>& fValueMap;
    };
    const GeoDatabaseBase& myDatabase;
};

#endif /* router_hpp */
