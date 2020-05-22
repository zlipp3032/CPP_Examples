#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <mutex>


using namespace std;


///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////


uint64_t epoch_reltime_us()
{
  using namespace std::chrono;
  return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}



int get_random_int(int max)
{
  srand(time(NULL));
  return rand() % max;
}


std::string GetTime()
{
  auto now_time = chrono::system_clock::now();
  time_t sleep_time = chrono::system_clock::to_time_t(now_time);
  return  std::ctime(&sleep_time);
}



void thread_fcn(int id)
{

  auto now_time = chrono::system_clock::now();
  time_t sleep_time = chrono::system_clock::to_time_t(now_time);
  
  tm my_local_time = *localtime(&sleep_time);

  cout << "Thread " << id << " Sleep Time: " << ctime(&sleep_time) << endl;



  // Example of how to use local time
  cout << "Month: " << my_local_time.tm_mon << endl;
  cout << "Day:  " << my_local_time.tm_mday << endl;
  cout << "Year: " << my_local_time.tm_year + 1900 << endl;
  cout << "Hours: " << my_local_time.tm_hour << endl;
  cout << "Minutes:  " << my_local_time.tm_min << endl;
  cout << "Seconds: " << my_local_time.tm_sec << endl;




  

  this_thread::sleep_for(chrono::seconds(get_random_int(3)));
  now_time = chrono::system_clock::now();
  sleep_time = chrono::system_clock::to_time_t(now_time);
  cout << "Thread " << id << " Awake Time: " << ctime(&sleep_time) << endl;
  
}



///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////


void main_MultiThread(void)
{

  std::cout << "\n\n" << "-------------------------\n" << " Multi-Threading Example\n" << "-------------------------\n" << "\n\n";


  std::thread th1 (thread_fcn, 1);

  th1.join();

  std::thread th2 (thread_fcn, 2);

  th2.join();
  










  
  /*
  uint64_t t_stamp, t_start;
  float t_rel = 0;
  int end_time=25;


  printf("Press the 's' key to start %d s timer.\n", end_time);
  
  char inputChar;
  cout << "Input value: ";
  cin >> inputChar;
  
  switch (inputChar)
    {
    case 's':
      t_start = epoch_reltime_us();
      
      while(t_rel < end_time)
	{
	  t_stamp = epoch_reltime_us();
	  t_rel = ((float)(t_stamp - t_start))/1000000;
	  printf("Time since start: %.2f \n",t_rel);
	  usleep(10000);
	}
    default:
      printf("Timer aborted!");
      break;
    }

  */


 

  std::cout << "\n\n" << "-------------\n" << " End Example\n" << "-------------\n" << "\n\n";

  
  return;
}
