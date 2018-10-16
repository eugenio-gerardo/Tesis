#ifndef log_hpp
#define log_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Log
{
  private:
    ofstream l_file;
    char separator;
    string f_name;
    int counter;
    vector<string> header;

  public:
    Log();
    Log(string f_name, char separator, vector<string> header);
    void log_line(vector<string> v_line);
    bool check();
};
#endif
