#ifndef _HASH_H
#define _HASH_H

#include <vector>
#include <string>
#include <iostream>

class Hash{
  public:
    int collions = 0;

    Hash();
    void insert(std::string fileName, std::string key);
    // int findCollisions(std::vector<std::string> fileName, std::vector<std::string> key, std::vector<std::string> fileName2);
  private:
   typedef struct HashTable
    {
       std::string fileName;
       HashTable *next;
    }HashTable;

    int hashFunction(std::string s);

    static const int PRIME = 1;
    static const int SIZE = 12289;
    HashTable* array[SIZE];
    int power (int val, int exp);

};

#endif
