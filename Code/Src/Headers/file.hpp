#ifndef file_hpp
#define file_hpp
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

class File
{
  private:
    string filename;
    char separator;
    vector<vector<string>> values;

  public:
    File(string name, char separator);
    void readfile();
    void print_list();
    void print_lines();
};
#endif
