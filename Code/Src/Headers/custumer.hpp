#ifndef custumer_hpp
#define custumer_hpp
#include "random.hpp"
using namespace std;

class Custumer
{
  private:
    double arrival_time;
    double service_time;
    double delay_time;

  public:
    Custumer(double interarrival_mean, double time);
    void set_service_time(double service_time);
    void set_delay_time(double delay_time);
    double get_arrival_time();
    double get_service_time();
    double get_delay_time();
};
#endif
