#include <iostream>
#include <string>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>

#include<vector>
using namespace std;

bool notified = true;

condition_variable cv1, cv2;
mutex m1, writer, m;
int value = 100;
int readcnt =0;
	
void reader(int reader){
	unique_lock<mutex> lk2(writer);
	m.lock();	
	readcnt++;
	if (readcnt!=1)
		cv2.wait(lk2);
	m.unlock();
	cout<<"Reader "<<reader<<" read value: "<<value<<endl;
	m.lock();
	readcnt--;
	if (readcnt == 0) 
		cv2.notify_all();
	m.unlock();

}

void writers(int writerx){
	unique_lock<mutex> lk2(writer);
	while(readcnt!=0)
		cv2.wait(lk2);
	value*=10;
	cout<<"Writer "<<writerx<<" modified value to: "<<value<<endl;
	notified = true;
	cv2.notify_all();
	this_thread::sleep_for(chrono::seconds(1));

}

int main(){

	vector<thread> ths;
	ths.push_back(thread(&reader, 1));
	ths.push_back(thread(&writers,1));
	ths.push_back(thread(&writers,2));
	ths.push_back(thread(&writers,3));
	ths.push_back(thread(&reader, 2));
	ths.push_back(thread(&writers, 4));
	ths.push_back(thread(&reader, 3));
	ths.push_back(thread(&writers, 5));
	ths.push_back(thread(&reader, 4));

	for(auto& th:ths){
		th.join();	
	}
	return 0;
}
