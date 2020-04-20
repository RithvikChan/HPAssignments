#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <vector>
#include <chrono>
#include <sstream>
#include <memory>

using namespace std;
class Philosopher
{
public:
    Philosopher() : name("") {}
 
    Philosopher(string n, mutex* left, mutex* right) :
        name(n), leftFork(left), rightFork(right) {}
 
    void think()
    {
        doAction("think");
    }
 
    void eat()
    {
        if (leftFork && rightFork)
        {
            unique_lock<mutex> left(*leftFork, defer_lock);
            unique_lock<mutex> right(*rightFork, defer_lock);
            lock(left, right);
            doAction("eat");
            left.unlock();
            right.unlock();
        }
    }
 
    void doAction(string actionName)
    {
        cout << name << " starts action: " << actionName << endl;
        this_thread::sleep_for(chrono::milliseconds(2500));
        cout << name << " finished action: " << actionName << endl;
    }
   void run()
    {
        if (leftFork && rightFork)
        {
                think();
                eat();
        }
    }
 
private:
    string name;
    mutex* leftFork;
    mutex* rightFork;
};
 
int main()
{
    int count = 5;
 
    vector<shared_ptr<::mutex>> forks;
    for (int i = 0; i<count; i++) {
        forks.push_back(make_shared<mutex>());
    }
 
    vector<shared_ptr<Philosopher>>philosophers;
    for (int i = 0; i<count; i++) {
        string name = "Philosopher" + to_string(i);
        philosophers.push_back(make_shared<Philosopher>(name,forks[i].get(),forks[(i + 1) % count].get()));
    }
    vector<thread> th;
    for (int i = 0; i < count; ++i) {
        th.push_back(thread(&Philosopher::run, philosophers[i]));
    }
 
    for (auto &ths : th){
        ths.join();
    }
 
    return 0;
}
