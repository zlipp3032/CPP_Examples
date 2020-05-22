#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iomanip>
#include <chrono>
#include <cstdint>
#include <vector>

#include "examples.h"


int frequency_of_primes(int n){
  int i,j;
  int freq = n-1;
  for (i=2; i<=n; ++i)
    {
    for (j=sqrt(i);j>1;--j)
      {
	if (i%j==0)
	  {
	    --freq; break;
	  }
      }
    }
  return freq;
  
}



uint64_t timeSinceEpochMicrosec() {
  using namespace std::chrono;
  return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

  
}




void main_TimeStamp(void)
{

  std::cout << "\n\n" << "--------------------\n" << " Time Stamp Example\n" << "--------------------\n" << "\n\n";

  
  // Returns the processor time consumed by the program.
  //
  // Calling clock() returns number of clock ticks, which are units of time of a constant but system-specific length
  //                                  --> (with a relation of CLOCKS_PER_SEC clock ticks per second).
  //
  // The epoch used as reference by clock varies between systems, but it is related to the program execution (generally its launch).
  //To calculate the actual processing time of a program,
  //                                  1) the value returned by clock shall be compared to a value returned by a previous call to the same function.

  clock_t t;
  int f;
  float rel_time,relpoch_time;
  int loop_time;
  uint64_t time;


  

  uint64_t start_time = timeSinceEpochMicrosec(); // Using the chrono method
  t = clock(); // Start of Loop (# of clock ticks since the processor started running this program)
  //std::cout << t << "\n";
  printf ("Calculating...\n");
  f = frequency_of_primes(99999);
  printf ("The number of primes lower than 100,000 is: %d\n",f);
  time = timeSinceEpochMicrosec();
  t = clock() - t; // End of Loop (# of clock ticks since the start of loop)
  printf ("It took me %lu clicks (%4f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);



  // Calculate the realtive time from start-of-loop to end-of-loop
  rel_time = (float)t/CLOCKS_PER_SEC;
  loop_time = rel_time*1000000;
  //std::cout << loop_time << "\n";
  printf("Using the internal clock method, it took to run the loop: %.3f s \n",rel_time);
  //std::cout << std::fixed << std::setprecision(4) << rel_time << "\n";


  
  relpoch_time = ((float)(time - start_time))/1000000;
  printf("Using th Epoch method yields loop time: %.3f s \n",relpoch_time);
    


  
  std::cout << "\n\n" << "-------------\n" << " End Example\n" << "-------------\n" << "\n\n";
  


  

  return;
}
