#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

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


void getletters(const char *fName, vector<char>& letter, int num){
  string line;
  ifstream myfile (fName);
  vector<string> queue;
  if(myfile.is_open()){
    while(getline(myfile, line) && line != "<br><br><b>Bibliography</b><br><br>"){
      cout << line<< endl;
        const char *letters = line.c_str();
        for(int i = 0; letters[i] != '\0'; i++){
          if('A' <= letters[i] && letters[i] <= 'Z' ){
            letter.push_back(letters[i]);
          }
          if('a' <= letters[i] && letters[i] <= 'z' ){
            letter.push_back(letters[i] - 32);
          }
        }
        queue.push_back(line);
    }
  }
}


int main(int argc, char *argv[])
{
    string dir = argv[1];
    const int N_WORDS = atoi(argv[2]);
    vector<string> files = vector<string>();
    vector<char> letters;
    vector<string> words;

    getdir(dir,files);

    // for (unsigned int i = 0;i < files.size();i++) {
    //     cout << i <<". " << files[i] << endl;
    // }
    string path = dir + "/" + files[0];
    // cout << path<< endl;
    getletters(path.c_str(), letters, 6);

    // for (unsigned int i = 0;i < letters.size();i++) {
    //     cout << letters[i];
    // }
    // cout << endl;
    vector<char>::iterator it = letters.begin();
    while (letters.size() >= N_WORDS){
      string s;
      for(int i = 0; i < N_WORDS; i++){
        s = s + letters[i];
      }
      words.push_back(s);
      letters.erase(letters.begin());
    }
    for (unsigned int i = 0; i < words.size();i++) {
        cout << i <<". " << words[i] << endl;
    }


    return 0;
}
