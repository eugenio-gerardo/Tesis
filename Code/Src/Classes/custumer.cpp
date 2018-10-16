#include "../Headers/custumer.hpp"

using namespace std;

Custumer::Custumer(double interarrival_mean, double time)
{
    this->arrival_time = time + exp_random(interarrival_mean); //next_arrive();//
    this->service_time = 10000000000000;
    this->delay_time = 0;
}
void Custumer::set_service_time(double service_time)
{
    this->service_time = service_time;
}
void Custumer::set_delay_time(double delay_time)
{
    this->delay_time = delay_time - this->arrival_time;
}
double Custumer::get_arrival_time()
{
    return this->arrival_time;
}
double Custumer::get_service_time()
{
    return this->service_time;
}
double Custumer::get_delay_time()
{
    return this->delay_time;
}
