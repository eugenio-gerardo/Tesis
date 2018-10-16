#include "../Headers/queue_system.hpp"

using namespace std;

Queue_System::Queue_System(double interarrival_mean, double service_mean, int limit_queue_size)
{
    //state variables
    this->event = 0;
    this->sim_clock_previous = 0;
    this->sim_clock = 0;
    this->d_sim_clock = this->sim_clock;
    this->q_event = Queue_Event::INIT;
    this->queue_size = 0;
    this->total_of_delays = 0;
    this->num_cust_delayed = 0;
    this->next_q_event = Queue_Event::ARRIVE;
    //queue parameters
    this->interarrival_mean = interarrival_mean;
    this->service_mean = service_mean;
    this->limit_queue_size = limit_queue_size;
    //init queue elements
    this->custumer_queue.push(Custumer(this->interarrival_mean, this->sim_clock));
    this->server = Server(this->service_mean);
    //statical counters
    this->area_num_inq = 0;
    this->area_server_status = 0;

    this->l = Log("qlog.csv", ',', this->h_vector());
    this->control = "";
    this->q_event = Queue_Event::INIT;
    this->l.log_line(this->r_vector());
}
bool Queue_System::simulation_stop()
{
    return this->num_cust_delayed == this->limit_queue_size;
}
void Queue_System::update_counters()
{
    this->d_sim_clock = this->sim_clock - this->sim_clock_previous;
    this->sim_clock_previous = this->sim_clock;
    this->area_num_inq += (this->queue_size) * this->d_sim_clock;
    this->area_server_status += this->server.isBusy() * this->d_sim_clock;
}
void Queue_System::update_sim_clock(double time)
{
    this->sim_clock = time;
    this->update_counters();
}
void Queue_System::arrive()
{
    this->event++;
    this->q_event = Queue_Event::ARRIVE;
    update_sim_clock(this->custumer_queue.back().get_arrival_time());
    this->custumer_queue.push(Custumer(this->interarrival_mean, this->sim_clock));
    if (this->server.isBusy())
    {
        this->queue_size++;
    }
    else
    {
        this->total_of_delays += 0;
        this->num_cust_delayed++;
        this->server.setStatus(Server_Status::BUSY);
        this->custumer_queue.front().set_service_time(this->server.Generate_Service(this->sim_clock));
    }
}
void Queue_System::depart()
{
    this->event++;
    this->q_event = Queue_Event::DEPART;
    update_sim_clock(this->custumer_queue.front().get_service_time());
    if (this->queue_size == 0)
    {
        this->server.setStatus(Server_Status::IDLE);
        this->custumer_queue.pop();
    }
    else
    {
        this->queue_size--;
        this->num_cust_delayed++;
        this->custumer_queue.pop();
        this->custumer_queue.front().set_service_time(this->server.Generate_Service(this->sim_clock));
        this->custumer_queue.front().set_delay_time(this->sim_clock);
        this->total_of_delays += this->custumer_queue.front().get_delay_time();
    }
}
void Queue_System::debug()
{
    cout << "Event Number:" << this->event << endl;
    cout << "Simulation Time Previous:" << this->sim_clock_previous - this->d_sim_clock << endl;
    cout << "Simulation Time:" << this->sim_clock << endl;
    cout << "Delta Simulation Time:" << this->d_sim_clock << endl;
    cout << "Event:" << static_cast<char>(this->q_event) << endl;
    cout << "Server Status:" << server.isBusy() << endl;
    cout << "Queue  Size:" << this->queue_size << endl;
    auto custumer_queue_aux = this->custumer_queue;
    int i = 1;
    while (!custumer_queue_aux.empty())
    {
        cout << "\tClient:" << i << endl;
        cout << "\t\tArrival_Time:" << custumer_queue_aux.front().get_arrival_time() << endl;
        cout << "\t\tService_Time:" << custumer_queue_aux.front().get_service_time() << endl;
        cout << "\t\tDelay:" << custumer_queue_aux.front().get_delay_time() << endl;
        custumer_queue_aux.pop();
        i++;
    }
    cout << "Total Delay:" << this->total_of_delays << endl;
    cout << "Next Arrive:" << this->custumer_queue.back().get_arrival_time() << endl;
    cout << "Next Depart:" << this->custumer_queue.front().get_service_time() << endl;
    cout << "Next Event:";
    if (this->custumer_queue.back().get_arrival_time() < this->custumer_queue.front().get_service_time())
    {
        cout << "Arrive" << endl;
    }
    else
    {
        cout << "Depart" << endl;
    }
    cout << "Number Delayed:" << this->num_cust_delayed << endl;
    cout << "Total Delay:" << this->total_of_delays << endl;
    cout << "Area under Q(t):" << this->area_num_inq << endl;
    cout << "Area under B(t):" << this->area_server_status << endl;
    cout << "-----------------------------------------" << endl;
    cout << endl;
    //cin.get();
}
vector<string> Queue_System::h_vector()
{
    vector<string> header;
    header.push_back("Event Number");
    header.push_back("Simulation Time Previous");
    header.push_back("Simulation Time");
    header.push_back("Delta Simulation Time");
    header.push_back("Event");
    header.push_back("Server Status");
    header.push_back("Queue Size");
    header.push_back("Total Delay");
    header.push_back("Num Cust Delayed");
    header.push_back("Next Arrive");
    header.push_back("Next Depart");
    header.push_back("Next Event");
    return header;
}
vector<string> Queue_System::r_vector()
{
    vector<string> row;
    row.push_back(to_string(this->event));
    row.push_back(to_string(this->sim_clock_previous - this->d_sim_clock));
    row.push_back(to_string(this->sim_clock));
    row.push_back(to_string(this->d_sim_clock));
    row.push_back((static_cast<char>(this->q_event) == 'A') ? "ARRIVE" : "DEPART");
    row.push_back(to_string(this->server.isBusy()));
    row.push_back(to_string(this->queue_size));
    row.push_back(to_string(this->total_of_delays));
    row.push_back(to_string(this->num_cust_delayed));
    row.push_back(to_string(this->custumer_queue.back().get_arrival_time()));
    row.push_back(to_string(this->custumer_queue.front().get_service_time()));
    row.push_back((static_cast<char>(this->next_q_event) == 'A') ? "ARRIVE" : "DEPART");
    return row;
}
void Queue_System::next_event()
{
    if (this->custumer_queue.back().get_arrival_time() < this->custumer_queue.front().get_service_time())
    {
        this->next_q_event = Queue_Event::ARRIVE;
    }
    else
    {
        this->next_q_event = Queue_Event::DEPART;
    }
}
void Queue_System::simulate()
{
    while (!simulation_stop())
    {
        if (this->next_q_event == Queue_Event::ARRIVE)
        {
            this->arrive();
        }
        else
        {
            this->depart();
        }
        this->next_event();
        this->log();
    }
    this->report();
}
void Queue_System::log()
{
    if (this->l.check())
    {
        this->control += "x";
        this->l = Log("qlog" + control + ".csv", ',', this->h_vector());
        this->l.log_line(this->r_vector());
    }
    else
    {
        this->l.log_line(this->r_vector());
    }
}
void Queue_System::report()
{
    cout << "Interarrival mean:" << this->interarrival_mean << endl;
    cout << "Service mean:" << this->service_mean << endl;
    cout << "Limit size:" << this->limit_queue_size << endl;
    cout << "Average Delay in Queue:" << this->total_of_delays / this->num_cust_delayed << endl;
    cout << "Average Number in Queue:" << this->area_num_inq / this->sim_clock << endl;
    cout << "Server  Utilization:" << this->area_server_status / this->sim_clock << endl;
}
