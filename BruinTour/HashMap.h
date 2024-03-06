//
//  HashMap.h
//  BruinTour
//
//  Created by Ankai Jin on 3/6/24.
//

#ifndef HashMap_h
#define HashMap_h

#include <list>
#include <functional>
#include <string>

// hash function
unsigned int mapFunction(const std::string &hashMe)
{
    std::hash<std::string> str_hash;
    unsigned int hash_value = str_hash(hashMe);
    
    unsigned int bucketNum = hash_value % 10;   // replace with however many buckets there are
    return bucketNum;
}

template<typename ValueType>
class HashMap
{
  public:
    HashMap()
     : numItems(0), numBuckets(10), maxLoad(0.75) {}
    

  private:
    double numItems;
    int numBuckets;
    double maxLoad;
};

#endif /* HashMap_h */
