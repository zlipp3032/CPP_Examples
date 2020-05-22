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


/*
// Option 1 for threads - using a thread function
void thread_fcn(int & value, int v2)
{
  std::cout << "Value in the thread function: " << value++ << std::endl;
  std::cout << "V2 in the thread function: " << v2 << std::endl;
}
*/


   
int main()
{

   std::cout << "\n\n" << "-------------------------\n" << " Multi-Threading Example\n" << "-------------------------\n" << "\n\n";


   int local_value = 146;
   int v2 = 100;

   // Option 1 for threads - using a thread function
   //std::thread th1 = std::thread(thread_fcn, 6);

   //std::thread th1 {thread_fcn, std::ref(local_value), 100};



   // Option 2 for threads - using the lambda function?
   std::thread th1 {[&](){
		       std::cout << "Value in the thread function: " << local_value++ << std::endl;
		       //std::cout << "V2 in the thread function: " << v2 << std::endl;
		       v2++;
		     }};

   

   th1.join();
   std::cout << "Local Value: " << local_value << std::endl;
   std::cout << "V2 after thread has been applied: " << v2 << std::endl;


   std::cout << "\n\n" << "-------------\n" << " End Example\n" << "-------------\n" << "\n\n";


  return 0;
}
