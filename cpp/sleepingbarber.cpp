#include <thread>
#include <iostream>
#include <chrono>
#include <condition_variable>
#include <vector>
#include <queue>
using namespace std;

condition_variable barbercv;
mutex custmutex;
mutex cutting;
int customer_count = 0;
int done = 0;
int num_chairs = 10;
int total_customers = 100;

queue<int> chairs;

void customer(int cust){
    this_thread::sleep_for(chrono::milliseconds(2500));

    custmutex.lock();
    total_customers--;
    if (customer_count < num_chairs){
        cout << "Adding Customer " << cust << " to queue" << endl;
        customer_count++;
        chairs.push(cust);
        if (total_customers == 0){
            done=1;
        }
        barbercv.notify_one();
    }else{
     cout << "Cant service customer " << cust << endl;
    }
    custmutex.unlock();
    this_thread::sleep_for(chrono::milliseconds(2500));
	
}

void barber(){
    while (true){
        unique_lock<mutex> l1(cutting);
        barbercv.wait(l1);
        while(!chairs.empty()){
            custmutex.lock();
            customer_count--;
            cout << "Barber cut " << chairs.front() << endl;
            chairs.pop();
            custmutex.unlock();
        }
    }
}

int main(){
    vector<thread> threads;
	int numcust = total_customers; // As total customers will change
    for (int i = 0; i < numcust ;i++){
        threads.push_back(thread(&customer,i));
    }
    thread barberthread = thread(&barber);
    
    for(auto& ths:threads){
        ths.join();
    }
    barberthread.join();
    return 0;
}
