#include "../Headers/server.hpp"
using namespace std;

Server::Server(){}
Server::Server(double mean_service)
{
    this->mean_service = mean_service;
    this->status = Server_Status::IDLE;
}
double Server::Generate_Service(double time)
{
    //double x=next_service();
    return time + exp_random(this->mean_service); //x;
}
bool Server::isBusy()
{
    return this->status == Server_Status::BUSY;
}
void Server::setStatus(Server_Status status)
{
    this->status = status;
}
