#include <iostream>
#include <string>
#include <queue>
#include "Headers/queue_system.hpp"

using namespace std;

queue<double> A;
queue<double> S;

void set_A()
{
    A.push(.4);
    A.push(1.2);
    A.push(.5);
    A.push(1.7);
    A.push(.2);
    A.push(1.6);
    A.push(.2);
    A.push(1.4);
    A.push(1.9);
}
void set_S()
{
    S.push(2.0);
    S.push(.7);
    S.push(.2);
    S.push(1.1);
    S.push(3.7);
    S.push(0.6);
    S.push(100.0);
}
double next_arrive()
{
    double x = A.front();
    A.pop();
    return x;
}
double next_service()
{
    double x = S.front();
    S.pop();
    return x;
}

int main()
{
    set_A();
    set_S();
    Queue_System q(1.0, .5, 1000000);
    q.simulate();
}
