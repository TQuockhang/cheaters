
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include "hash.h"

using namespace std;

Hash::Hash(){
  for(int i = 0 ; i < SIZE; i++){
    array[i] = NULL;
  }
}

void Hash::insert(std::string fileName, std::string key){
  Hash::HashTable *temp = new Hash::HashTable;
  temp->fileName = fileName;
  temp->next = NULL;
  int location = hashFunction(key);
  if(array[location]  == NULL){
    array[location] = temp;
  }
  else{
    if(!(array[location]->fName == fileName)){
      temp->next = array [location];
      array[location] = temp;
    }
    else{
      cout << "so close yet so far" << endl;
      collions +=1;
      //exit(41);
    }
  }
}


int Hash::hashFunction(std::string key){
  int hash = 0;
  const char* letters = key.c_str();
  int c = 0;
  for(int i = 0; i < key.size() ; i++){
  //  cout << i << ". "<< letters[i] << endl;
    hash += ((letters[key.size() - i - 1]) - 65)* ( ( ( (power(5, i)/power( 3, i)) )  ) % SIZE )   ;
  }
  hash = hash % SIZE ;
  cout << hash << endl;

  if (hash > SIZE || hash < 0){
    cout << "error bounds" << endl;
    cout << key.size() << endl;
    exit(42);
  }
  // cout << hash << endl;
  return hash;
}
int Hash::power (int val, int exp){
  if(exp == 0){
    return 1;
  }
  return (val * power(val, exp-1)) ;
}
