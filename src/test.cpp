#include <iostream>
#include <vector>
//using namespace std;
#include "examples.h"




// This function is to generate a vector of evenly spaced points
std::vector<double> time_vector(float startTime, float endTime, float Ts) {
  std::cout << "Time Vector Function!! \n";

  float temp_time = endTime - startTime;
  int temp_titty = temp_time / Ts;

  std::cout << temp_titty << "\n";

  // Initialize the time vector
  std::vector<double> time_vect(temp_titty+1,0);

  for (int i=0; i<temp_titty+1; i++) {
    time_vect[i] = startTime + i*Ts;
  }


  return time_vect;

}







// Main Loop
void mainTest(void) {
  std::cout << "Hello World! \n";


 
  /*
  // This section is an exmaple of the 
  bool trust;
  float johnny = 3.4;

  std::cout << trust << "\n" << johnny << "\n";
  */



  /*
  // Creating a Vector of int or float (i.e., zeros or ones)
  int vect_length = 2;
  std::vector<int> vect(vect_length, 1);
  std::vector<double> vector2(vect_length, 0.0);

  for (int i = 0; i < vect_length; i++) {
    std::cout << vect[i] << "\n";
  }
  */



  // Create a linearly spaced vector for the input arguments we will call time for now!
  float Ts = 0.01;
  float startTime = 0;
  float endTime = 10;
  int stopDex = (endTime - startTime)/Ts + 1;
  std::vector<double> time;

  

  time = time_vector(startTime,endTime,Ts);
  
  
  for (int i = 0; i < stopDex; i++) {
    std::cout << time[i] << "\n";
  }
  






  
  
  return;
}
