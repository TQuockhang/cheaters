#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

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
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main(int argc, char *argv[])
{
    string dir = argv[1];
    vector<string> files = vector<string>();

    getdir(dir,files);

    for (vector<string>::iterator it = files.begin(); it != files.end(); ++it) {
        if (*it == "."){
          files.erase(it);
        }
        if(*it == ".."){
          files.erase(it);
        }
    }

    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << files[i] << endl;
    }

    return 0;
}
