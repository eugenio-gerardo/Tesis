#ifndef system_queue_hpp
#define system_queue_hpp

#include <queue>
#include "custumer.hpp"
#include "server.hpp"
#include "log.hpp"

using namespace std;

enum class Queue_Event : char
{
    ARRIVE = 'A',
    DEPART = 'D',
    INIT = 'I',
    END = 'E'
};
class Queue_System
{
  private:
    //state variables
    int event;
    double sim_clock_previous;
    double sim_clock;
    double d_sim_clock;
    Queue_Event q_event;
    int queue_size;
    double total_of_delays;
    double num_cust_delayed;
    Queue_Event next_q_event;
    //queue parameters
    double service_mean;
    double interarrival_mean;
    int limit_queue_size;
    //queue elements
    queue<Custumer> custumer_queue;
    Server server;
    //statical Counters
    double area_num_inq;
    double area_server_status;
    Log l;
    string control;

  public:
    Queue_System(double interarrival_mean, double service_mean, int limit_queue_size);
    bool simulation_stop();
    void update_counters();
    void update_sim_clock(double time);
    void arrive();
    void depart();
    void debug();
    vector<string> h_vector();
    vector<string> r_vector();
    void next_event();
    void simulate();
    void log();
    void report();
};
#endif
