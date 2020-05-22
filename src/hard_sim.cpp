#include <iostream>
#include <vector>
#include <cmath> // sin function and M_PI
#include <fstream>
//#include <sstream>
//using namespace std;
#include "examples.h"


struct state_t_vec {

  std::vector<double> time;
  std::vector<double> pos; // desired position
  std::vector<double> my_pos; // agent position
} scrappy, scooby;


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////

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


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


// This function is used to "simulate" the sine function over a given time vector
std::vector<double> simulate_sine(std::vector<double> time, int stopDex, float freq) {
  std::cout << "Simulate Sine Function!!" << "\n";

  std::vector<double> output(stopDex,0);


  for (int i = 0; i < stopDex; i++) {
    output[i] = sin(freq*time[i] + M_PI/2);
    // std::cout << output[i] << "\n";
  }

  return output;

}
*/

////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


// This is change in state, dy, over change in interval, dx
float dydx_medium(float x, float y, int derv_type, float ff, float yd, float freq) 
{
  float state1;


  switch(derv_type)
    {
    case 0:
      state1 = -freq*sin(freq*x);
      //state2 = 0;
      break;
    case 1:
      //float ff = freq*sin(freq*x);
      state1 = ff - 2.3*(y - yd);
      break;
    default:
      printf("Pick another derv_type!");
      state1=0;
      break;
    }
      

  //scooby.pos = state1;
  //scooby.my_pos = state2;
  
  return state1; 
}


float rungeKuttaEqns_simple(float x0, float y, float h, int derv_type, float ff, float yd, float freq)
{

  float k1, k2, k3, k4;
  // Apply Runge Kutta Formulas to find next value of y 
  k1 = h*dydx_medium(x0, y, derv_type, ff, yd, freq); 
  k2 = h*dydx_medium(x0 + 0.5*h, y + 0.5*k1, derv_type, ff, yd, freq); 
  k3 = h*dydx_medium(x0 + 0.5*h, y + 0.5*k2, derv_type, ff, yd, freq); 
  k4 = h*dydx_medium(x0 + h, y + k3, derv_type, ff, yd, freq); 
  
  // Update next value of y 
  y = y + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);;
  
  return y;

}




// Finds value of y for a given x using step size h and initial value y0 at x0. 
void rungeKutta_medium(float x0, std::vector<double> y0, float x, float h, int stopDex, int nag, float freq) 
{

  // Initiate state vector
  std::vector<double> pos(stopDex,0), my_pos(stopDex,0), t(stopDex,0);
  t[0] = x0;
  pos[0] = y0[0];
  my_pos[0] = y0[1];
  
  // Count number of iterations using step size or step height h 
  int n = (int)((x - x0) / h); 
  
  float k1, k2, k3, k4, k5; 
  
  // Iterate for number of iterations 
  std::vector<double> y = y0;
  for (int i=1; i<=n; i++) 
    {
      // Compute the integral for the current state y at x0
      for (int j=0; j < nag; j++)
	{
	  if (j == 0)
	    {
	      y[j] = rungeKuttaEqns_simple(x0, y[j], h, 0, 0.0, 0.0, freq);
	    }
	  else
	    {
	      float ff =  -freq*sin(freq*x0);
	      y[j] = rungeKuttaEqns_simple(x0, y[j], h, 1, ff, y[0], freq);
	    }
	}

      // Update next value of x 
      x0 = x0 + h;
      
      // Update state vector
      pos[i] = y[0];
      my_pos[i] = y[1];
      t[i] = x0;
    }


  // Update the output time and state vectors
  scrappy.time = t;
  scrappy.pos = pos;
  scrappy.my_pos = my_pos;
  
  //return scrappy.pos; 
}


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


// Main Loop
void main_HardSim(void) {
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


  // Run runga kutta over a time series
  std::vector<double> yyy, t;
  int stopperDex = stopDex - 1;
  int n = 2;
  std::vector<double> y0(n,0);
  float h0 = Ts;


  // Set the initial conditions
  y0[0] = cos(freq*time[0]);
  y0[1] = 7;

  
  // Run the simulation
  rungeKutta_medium(time[0],y0,time[stopperDex],Ts, stopDex, n, freq);

  
  // Save data to .csv file so we can look at it later!!
  std::ofstream output_file;
  output_file.open("simulation_data.csv");
  output_file << "Time, ";
  output_file << "Analytic_State, ";
  output_file << "Leader_State, ";
  output_file << "T_Kutta" << ", ";
  output_file << "Agent_Pos" << "\n";
  for (int i = 0; i < stopDex; i++)
    {
      output_file << time[i] << ", " ;
      output_file << outside[i] << ", ";
      output_file << scrappy.pos[i] << ", ";
      output_file << scrappy.time[i] << ", ";
      output_file << scrappy.my_pos[i] << "\n";
    }
  output_file.close();
    

  
  return;
}
