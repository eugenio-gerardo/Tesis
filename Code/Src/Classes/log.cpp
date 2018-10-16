#include "../Headers/log.hpp"

using namespace std;

Log::Log(){};
Log::Log(string f_name, char separator, vector<string> header)
{
    this->f_name = f_name;
    this->l_file = ofstream(f_name);
    this->separator = separator;
    this->log_line(header);
    this->counter = 0;
    this->header = header;
}

void Log::log_line(vector<string> v_line)
{
    this->counter++;
    string s_line = "";
    for (auto x : v_line)
    {
        s_line += x;
        s_line += this->separator;
    }
    s_line.erase(s_line.end() - 1);
    l_file << s_line << endl;
}
bool Log::check()
{
    return this->counter == 500000;
}
