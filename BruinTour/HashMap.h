//
//  HashMap.h
//  BruinTour
//
//  Created by Ankai Jin on 3/6/24.
//

#ifndef HashMap_h
#define HashMap_h

#include <vector>
#include <list>
#include <functional>
#include <string>

#include "support.h"

template<typename T>
class HashMap
{
  public:
    HashMap(double maxLoad = 0.75) // hash table constructer with default parameter
     : numItems(0), numBuckets(10), max(maxLoad), vectorOfVectors(10) {}
    
    ~HashMap()
    {
        typename std::list<DataPair*>::iterator it = myAssociations.begin();
        while (it != myAssociations.end())
        {
            delete (*it);
            it = myAssociations.erase(it);
        }
    }
    
    int size() const
    {
        return numItems;
    }
    
    void insert(const std::string& key, const T& value)
    {
        // if key already exists, update the DataPair instead of inserting a new one
        T* alreadyExists = find(key);
        if (alreadyExists != nullptr)
        {
            *alreadyExists = value;
            return;
        }
        
        if ((static_cast<double>(numItems + 1) / numBuckets) > max)  // resize hash table
        {
            numBuckets *= 2;
            std::vector<std::vector<DataPair*>> newVectorOfVectors(numBuckets);
            
            typename std::list<DataPair*>::iterator it = myAssociations.begin();
            for ( ; it != myAssociations.end(); it++)   // O(N) time
            {
                int bucket = mapFunction((*it)->myKey, numBuckets);  // rehash
                newVectorOfVectors[bucket].push_back((*it));    // push into new vector
            }
            vectorOfVectors = std::move(newVectorOfVectors);    // transfer ownership efficiently
        }
        
        // insert item
        int bucket = mapFunction(key, numBuckets);
        DataPair* toInsert = new DataPair(key, value);
        vectorOfVectors[bucket].push_back(toInsert);
        myAssociations.push_back(toInsert);
        numItems++;
    }
    
    T* find(const std::string& key) const
    {
        int bucket = mapFunction(key, numBuckets);
        for (int i = 0; i < vectorOfVectors[bucket].size(); i++)    // iterate through the bucket
        {
            if (vectorOfVectors[bucket][i]->myKey == key)   // match found
                return &(vectorOfVectors[bucket][i]->myValue);  // return the address to the DataPair's value
        }
        return nullptr; // match not found
    }
    
    T& operator[](const std::string& key)
    {
        // if key exists in the HashMap, return a reference to the key's value
        // otherwise insert a new key, intialize it with default values
        T* alreadyExists = find(key);
        if (alreadyExists != nullptr)
            return *alreadyExists;
        
        T defaultValues{};  // does this work?
        insert(key, defaultValues);
        return *find(key);
    }

  private:
    struct DataPair
    {
        DataPair(const std::string& key, const T& value)
         : myKey(key), myValue(value) {}
        std::string myKey;
        T myValue;
    };
    int numItems;    // remember to avoid integer division
    int numBuckets;
    double max;
    std::vector<std::vector<DataPair*>> vectorOfVectors;
    std::list<DataPair*> myAssociations;    // push back newly created DataPairs to both the vector and list
};

// Logic:
// 1) 

#endif /* HashMap_h */
