#include <iostream>
#include <vector>
#include <cmath> // sin function and M_PI
#include <fstream>
//using namespace std;
#include "examples.h"



/*
// This function is to generate a vector of evenly spaced points
std::vector<double> time_vector(float startTime, float endTime, float Ts) {
  std::cout << "Time Vector Function!! \n";

  // Initialize variables used in function
  float temp_time = endTime - startTime;
  int index_end = temp_time / Ts;
  std::vector<double> time_vect(index_end+1,0);
  

  for (int i=0; i<index_end+1; i++) {
    time_vect[i] = startTime + i*Ts;
  }

  return time_vect;

}

*/


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


// This function is used to "simulate" the sine function over a given time vector
std::vector<double> simulate_sine(std::vector<double> time, int stopDex, float freq) {
  std::cout << "Simulate Sine Function!!" << "\n";

  std::vector<double> output(stopDex,0);


  for (int i = 0; i < stopDex; i++) {
    output[i] = sin(freq*time[i]);
    // std::cout << output[i] << "\n";
  }

  return output;

}


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


// Main Loop
void main_SimpleSim(void) {
  std::cout << "Hello World! \n";
  
  // Create the time vector
  float Ts = 0.01;
  float startTime = 0;
  float endTime = 10;
  int stopDex = (endTime - startTime)/Ts + 1;
  std::vector<double> time;
  time = time_vector(startTime,endTime,Ts);

  // Simulate the sine function over the time vector at a given frequency
  std::vector<double> outside;
  float per = 10;
  float freq = 2 * M_PI/per;
  outside = simulate_sine(time,stopDex,freq);



  
  // Save data to .csv file so we can look at it later!!
  std::ofstream output_file;
  output_file.open("simulation_data.csv");
  output_file << "Time, ";
  output_file << "State\n";
    for (int i = 0; i < stopDex; i++) {
      output_file << time[i] << ", " ;
      output_file << outside[i] << "\n";

    }
  output_file.close();
    

  
  return;
}
