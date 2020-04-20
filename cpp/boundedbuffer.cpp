#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>
using namespace std;

mutex m;
condition_variable notfull;
condition_variable notempty;
int c = 0;
bool done = false;
queue<int> items;
int capacity = 5;
void producer(){
	while(true){
	unique_lock<mutex> lock(m);
	while(items.size() >capacity)
		notfull.wait(lock);
	int item = rand()%100;
	items.push(item);
	cout<<"Produced "<<item<<endl;
	notempty.notify_all();
	this_thread::sleep_for(chrono::seconds(1));
	}
}


void consumer(){
	while(true){
		unique_lock<mutex> lock(m);
		while(items.empty()){
			notempty.wait(lock);
		}
		int x = items.front();
		items.pop();
		cout<<"Consumed"<<x<<endl;
		notfull.notify_all();
	this_thread::sleep_for(chrono::seconds(1));

	}	
}
int main(){

vector<thread> ths;
ths.push_back(thread(&producer));
ths.push_back(thread(&consumer));

for(auto& th:ths){
	th.join();	
}
return 0;	
}



