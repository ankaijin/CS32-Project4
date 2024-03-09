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
    struct GeoPointCost
    {
        GeoPointCost(GeoPoint p, const double& g, const double& h)
         : myPoint(p), gScore(g), hScore(h) {}
        GeoPoint myPoint;
        double gScore;
        double hScore;
    };
    struct compareCosts // see if there's another way to do this
    {
        bool operator()(const GeoPointCost& a, const GeoPointCost& b) const
        {
            // Define your custom comparison logic here
            // For example, return true if 'a' has lower priority than 'b'
            return (a.gScore) + (a.hScore) > (b.gScore) + (b.hScore);
        }
    };
    const GeoDatabaseBase& myDatabase;
};

#endif /* router_hpp */
