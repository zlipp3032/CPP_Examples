#include <iostream>
#include <vector>
#include <cmath> // sin function and M_PI
#include <fstream>
//using namespace std;
#include "examples.h"




////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////

// This is change in state, dy, over change in interval, dx
float dydx_simple(float x, float y) 
{
  float scooby, freq = 2*M_PI/10;
  scooby = -freq*sin(freq*x);
  
  return scooby; 
} 


// Finds value of y for a given x using step size h 
// and initial value y0 at x0. 
std::vector<double> rungeKutta_simple(float x0, float y0, float x, float h, int stopDex) 
{

  // Initiate state vector
  std::vector<double> state(stopDex,0);
  state[0] = y0;
  
  // Count number of iterations using step size or 
  // step height h 
  int n = (int)((x - x0) / h); 
  
  float k1, k2, k3, k4, k5; 
  
  // Iterate for number of iterations 
  float y = y0; 
  for (int i=1; i<=n; i++) 
    { 
      // Apply Runge Kutta Formulas to find 
      // next value of y 
      k1 = h*dydx_simple(x0, y); 
      k2 = h*dydx_simple(x0 + 0.5*h, y + 0.5*k1); 
      k3 = h*dydx_simple(x0 + 0.5*h, y + 0.5*k2); 
      k4 = h*dydx_simple(x0 + h, y + k3); 
  
      // Update next value of y 
      y = y + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);; 
  
      // Update next value of x 
      x0 = x0 + h;

      // Update state vector
      state[i] = y;
    } 
  
  return state; 
}


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


// Main Loop
void main_MedSim(void) {
  std::cout << "Hello World! \n";
  
  // Create the time vector
  float Ts = 0.01;
  float startTime = 0;
  float endTime = 20;
  int stopDex = (endTime - startTime)/Ts + 1;
  std::vector<double> time;
  time = time_vector(startTime,endTime,Ts);

  // Simulate the sine function over the time vector at a given frequency
  std::vector<double> outside;
  float per = 10;
  float freq = 2 * M_PI/per;
  outside = simulate_sine(time,stopDex,freq);


  // Basic example of using the runga kutta method
  //float x0 = 0, y = 1, x = 1, h = 0.01;
  //printf("\nThe value of y at x is : %f \n",  rungeKutta(x0, y, x, h)); 


  // Run runga kutta over a time series
  std::vector<double> yyy, t;
  int stopperDex = stopDex - 1;
  float y0 = cos(freq*time[1]);
  float h0 = Ts;
  yyy = rungeKutta_simple(time[0],y0,time[stopperDex],Ts, stopDex);


  
  // Save data to .csv file so we can look at it later!!
  std::ofstream output_file;
  output_file.open("simulation_data.csv");
  output_file << "Time, ";
  output_file << "Analytic_State, ";
  output_file << "RungeKutta_State" << "\n";
    for (int i = 0; i < stopDex; i++) {
      output_file << time[i] << ", " ;
      output_file << outside[i] << ", ";
      output_file << yyy[i] << "\n";

    }
  output_file.close();
    

  
  return;
}
