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

/*
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
*/


///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////

std::mutex vect_lock;
std::vector<unsigned int> prime_vect;


void FindPrimes(unsigned int start, unsigned int end)
{
  for(unsigned int x = start; x <= end; x += 2)
    {
      for(unsigned int y = 2; y < x; y++ )
	{
	  if((x % y) == 0)
	    {
	      break;
	    } else if((y+1) == x)
	    {
	      vect_lock.lock();
	      prime_vect.push_back(x);
	      vect_lock.unlock();
	    }
	}
    }
}

void PrimeThreads(unsigned int start, unsigned int end, unsigned int num_threads)
{
  std::vector<std::thread> threads;
  unsigned int thread_spread = end / num_threads;
  unsigned int new_end = start + thread_spread - 1;
  for (unsigned int x = 0; x < num_threads; x++)
    {
      threads.emplace_back(FindPrimes, start, new_end);
      start += thread_spread;
      new_end += thread_spread;
    }

  for (auto& t: threads)
    {
      t.join();
    }
  
}




///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////



// Account Balance Example
/*
double acct_balance = 100; //global variable throughout this function
std::mutex acct_lock; //prevents thread from accessing variables at the same time

void GetMoney(int id, float withdrawal)
{
  std::lock_guard<std::mutex> lock(acct_lock);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << id << " tries to withdrawal $" << withdrawal << " on " << GetTime() << endl;

  if ((acct_balance - withdrawal) >= 0)
    {
      acct_balance -= withdrawal;
      std::cout << "New Account Balance: $" << acct_balance << endl;
    } else
    {
      std::cout << "Insufficient Funds! Current Account Balance: $" << acct_balance << endl;
    }
  
}

*/


///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////


// Playing around with time example
/*
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

*/

///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////


void main_MultiThread(void)
{

  std::cout << "\n\n" << "-------------------------\n" << " Multi-Threading Example\n" << "-------------------------\n" << "\n\n";




  // Prime method with threads
  int start_time = clock();

  PrimeThreads(1,100000, 3);

  int end_time = clock();
  for(auto i: prime_vect)
    std::cout << i << endl;
  std::cout << "Execution Time: " << (end_time - start_time)/double(CLOCKS_PER_SEC) << endl;


  
  // Prime method without threads
  /*
  std::vector<unsigned int> prime_vect;
  int start_time = clock();

  FindPrimes(1, 100000, prime_vect);
  for(auto i: prime_vect)
      std::cout << i << endl;
  int end_time = clock();

  std::cout << "Execution Time: " << (end_time - start_time)/double(CLOCKS_PER_SEC) << " seconds." <<  endl;
  */
  




  
  
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
  

  // Account Balance Example
  /*
  std::thread threads[10];
  for (int i = 0; i<10; ++i)
    {
      threads[i] = std::thread(GetMoney, i, 15);
    }



   for (int i = 0; i<10; ++i)
    {
      threads[i].join();
    }
   */



  
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////

  
  
// Playing around with time example
/*
  std::thread th1 (thread_fcn, 1);

  th1.join();

  std::thread th2 (thread_fcn, 2);

  th2.join();
  
*/




  
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////

  // Timer with end_time defined before compilations

  
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
