//
//  tour_generator.hpp
//  BruinTour
//
//  Created by Ankai Jin on 3/6/24.
//

#ifndef tour_generator_hpp
#define tour_generator_hpp

#include "base_classes.h"

class TourGenerator: public TourGeneratorBase
{
  public:
    TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
    virtual ~TourGenerator();
    virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
  private:
    const GeoDatabaseBase& myDatabase;
    const RouterBase& myRouter;
    std::string determineDirection(double angle) const;
};

#endif /* tour_generator_hpp */
