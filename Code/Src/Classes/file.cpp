#include "../Headers/file.hpp"
#include <vector>

using namespace std;

File::File(string name, char separator)
{
    this->filename = name;
    this->separator = separator;
}
void File::readfile()
{
    ifstream f(this->filename);
    string line;
    while (getline(f, line))
    {
        string line_value;
        vector<string> line_values;
        stringstream ss(line);
        while (getline(ss, line_value, this->separator))
        {
            line_values.push_back(line_value);
        }
        this->values.emplace_back(line_values);
    }
}
void File::print_list()
{
    for (auto x : this->values)
        for (auto y : x)
            cout << y << endl;
}
void File::print_lines()
{
    for (auto x : this->values)
    {
        string line = "";
        for (auto y : x)
        {
            y += this->separator;
            line += y;
        }
        cout << " " << line << endl;
    }
}
