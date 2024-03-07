//
//  support.cpp
//  BruinTour
//
//  Created by Ankai Jin on 3/6/24.
//

#include "support.h"

int mapFunction(const std::string &hashMe, const int& numBuckets) // hash function
{
    std::size_t hash_value = std::hash<std::string>()(hashMe);
    
    unsigned int bucketIndex = hash_value % numBuckets;   // replace with however many buckets there are
    return bucketIndex;
}
