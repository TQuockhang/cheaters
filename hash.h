#ifndef _HASH_H
#define _HASH_H

#include <vector>
#include <string>
#include <iostream>

class Hash{
  public:
    int collions = 0;

    Hash();
    void insert(int index,const std::string & key);
    void findCollisions(std::vector<std::string>const & fileName, int tolerance);

  private:
   typedef struct HashTable
    {
       int fIndex;
       HashTable *next;
    }HashTable;

    unsigned int hashFunction( const std::string& s);

    static const int SIZE = 24593;
    HashTable* array[SIZE];
    void remove(int index);


};

#endif
