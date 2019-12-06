#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "hash.h"

using namespace std;
int getdir (string dir, vector<string> &files);
void GetWords(const char *fName, vector<string>& queue);
void convertToKey( vector<string>& queue, vector<string>& output, int num);

int main(int argc, char *argv[])
{
    Hash h;
    string dir = argv[1];
    const int N_WORDS = atoi(argv[2]);
    const int FILTER = atoi(argv[3]);
    vector<string> files = vector<string>();
    vector<string> words;
    vector<string> key;

    getdir(dir,files);


    for(int i = 0; i < files.size(); i++){
      string path = dir + "/" + files[i];
      // cout << path << endl;

      GetWords(path.c_str(), words);
      convertToKey(words, key, N_WORDS);

      for(int c = 0; c < key.size(); c++){
        // cout << i;
         h.insert(i, key[c]);
      }

    }
    h.findCollisions(files, FILTER);



    return 0;
}

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
      if(!(string(dirp->d_name) == "." || string(dirp->d_name) == "..")){
        files.push_back(string(dirp->d_name));
      }

    }
    closedir(dp);
    return 0;
}


void GetWords(const char *fName, vector<string>& queue){
  string line;
  ifstream myfile (fName);
  if(myfile.is_open()){
    while(getline(myfile, line)){
      const char *letters = line.c_str();
      string s;
      for(int i = 0; letters[i] != '\0'; i++){
        if ( ' ' == letters[i]){
          queue.push_back(s);
          s = "";
        }
        if(('A' <= letters[i] && letters[i] <= 'Z')){
          s.push_back(letters[i]);

        }
        if('a' <= letters[i] && letters[i] <= 'z' ){
          s.push_back(letters[i] - 32);
        }
      }
    }
  }
}

void convertToKey(vector<string>& queue, vector<string>& output, int num){

  while (queue.size() >= num){
    string s;
    for(int i = 0; i < num; i++){
      s = s + queue[i];
    }
    queue.erase(queue.begin());
    output.push_back(s);
  }
}
