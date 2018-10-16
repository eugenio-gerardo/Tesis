#ifndef server_hpp
#define server_hpp
#include "random.hpp"

using namespace std;

enum class Server_Status
{
    IDLE,
    BUSY
};
class Server
{
  private:
    double mean_service;
    Server_Status status;

  public:
    Server();
    Server(double mean_service);
    double Generate_Service(double time);
    bool isBusy();
    void setStatus(Server_Status status);
};
#endif
