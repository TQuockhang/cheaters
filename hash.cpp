
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include "hash.h"
#include <cmath>

using namespace std;

Hash::Hash(){
  for(int i = 0 ; i < SIZE; i++){
    array[i] = NULL;
  }
}

void Hash::insert(int index, const std::string& key){
  unsigned int location = hashFunction(key);
  if(array[(int)location]  == NULL){
    Hash::HashTable *temp = new Hash::HashTable;
    temp->fIndex = index;
    temp->next = NULL;
    array[location] = temp;
  }
  else{
    if((array[location]->fIndex) != index){
      Hash::HashTable *temp = new Hash::HashTable;
      temp->fIndex = index;
      temp->next = array[location];
      array[location] = temp;
    }
  }
}


unsigned int Hash::hashFunction(const std::string& key){
  unsigned int hash = 0;
  for(int i = 0; i < key.length(); i++){
    hash +=( ((key[key.length() - i - 1]) * pow(3,i)));
  }
  hash = hash%SIZE;
  return hash;
}

void Hash::findCollisions(vector<string>const & fileName, int tolerance){
  int matrix[fileName.size()][fileName.size()];
   for ( int i = 0 ; i < fileName.size() ; i++ ){
     for ( int j = 0 ; j < fileName.size() ; j++ ){
        matrix[i][j] = 0;
      }
    }
Hash::HashTable* ptr1;
  for(int i = 0; i < SIZE; i++){
    ptr1 = array[i];

    if(array[i] != NULL){
      // ptr1 = ptr1->next;
        while(array[i]->next != NULL){
          while(ptr1 != NULL){
            matrix[array[i]->fIndex][ptr1->fIndex]++;
            ptr1 = ptr1->next;
          }
          remove(i);
          ptr1 = array[i];
        }

    }

  }
  for(int i = 0; i < fileName.size(); i++){
    for(int j = i+ 1; j < fileName.size(); j++){
      if(matrix[j][i] >= tolerance){
        cout <<  matrix[j][i] << " " << fileName[i] << ", " << fileName[j] << endl;
      }
    }
  }

}

void Hash::remove(int index){
  HashTable* temp = array[index];
  array[index] = array[index]->next;
  delete temp;
}
