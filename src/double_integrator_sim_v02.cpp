#include <iostream>
#include <vector>
#include <cmath> // sin function and M_PI
#include <fstream>
//#include <sstream>
//using namespace std;
#include "examples.h"


struct state_t_DI {

  std::vector<double> time;
  std::vector<double> lead_pos; // desired position
  std::vector<double> lead_vel; // desired velocity
  std::vector<double> pos_1; // agent position
  std::vector<double> vel_1; // agent velocity
} states;

struct ode_state {

  float x1;
  float x2;
} scooby_DI;



////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


// This is change in state, dy, over change in interval, dx
float dydx_hard(float x, std::vector<double> y, int derv_type, std::vector<double> ff, float freq) 
{
  float state1;


  switch(derv_type)
    {
    case 0:
      // Leader Dynamics
      state1 = -freq*sin(freq*x);
      break;
    case 1:
      // Agent Dynamics
      state1 = -freq*freq*cos(freq*x);
      break;
    case 2:
      // Leader Dynamics
      state1 = y[3];
      break;
    case 3:
      // Agent Dynamics
      state1 = ff[1] - 3*(y[2] - y[0]) - 4*(y[3] - y[1]);
      break;
    default:
      printf("Pick another derv_type!");
      state1=0;
      break;
    }
      
  
  return state1; 
}


float rungeKuttaEqns(float x0, std::vector<double> y, float h, int derv_type, std::vector<double> ff, float freq)
{

  float k1, k2, k3, k4;
  // Apply Runge Kutta Formulas to find next value of y 
  k1 = h*dydx_hard(x0, y, derv_type, ff, freq);
  std::vector<double> temp1 = y, temp2 = y, temp3 = y;
  temp1[derv_type] = temp1[derv_type] + 0.5*k1;
  k2 = h*dydx_hard(x0 + 0.5*h, temp1, derv_type, ff, freq);
  temp2[derv_type] = temp2[derv_type] + 0.5*k2;
  k3 = h*dydx_hard(x0 + 0.5*h, temp2, derv_type, ff, freq);
  temp3[derv_type] = temp3[derv_type] + k3;
  k4 = h*dydx_hard(x0 + h, temp3, derv_type, ff, freq); 
  
  // Update next value of y 
  y[derv_type] = y[derv_type] + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);;
  
  return y[derv_type];

}




// Finds value of y for a given x using step size h and initial value y0 at x0. 
void ODEsolver(float x0, std::vector<double> y0, float x, float h, int stopDex, int nag, float freq) 
{

  // Initiate state vector
  std::vector<double> pos_1(stopDex,0), vel_1(stopDex,0), lead_pos(stopDex,0), lead_vel(stopDex,0), t(stopDex,0);
  t[0] = x0;
  lead_pos[0] = y0[0];
  lead_vel[0] = y0[1];
  pos_1[0] = y0[2];
  vel_1[0] = y0[3];
  
  
  // Count number of iterations using step size or step height h 
  int n = (int)((x - x0) / h); 
  
  float k1, k2, k3, k4, k5; 
  
  // Iterate for number of iterations 
  std::vector<double> y = y0, ff_temp(2,0);
  for (int i=1; i<=n; i++) 
    {      
      std::vector<double> ff(2,0);
      ff[0] = -freq*sin(freq*x0);
      ff[1]= -freq*freq*cos(freq*x0);
 
      // Compute the integral for the current state y at x0
      for (int j=0; j < nag; j++)
	{
	  if (j<2)
	    { 
	      y[j] = rungeKuttaEqns(x0, y, h, j, ff_temp, freq );
	    }
	  else
	    {
	      y[j] = rungeKuttaEqns(x0, y, h, j, ff, freq);
	    }
	}
      

      
      // Update next value of x 
      x0 = x0 + h;
      
      // Update state vector
      lead_pos[i] = y[0];
      lead_vel[i] = y[1];
      pos_1[i] = y[2];
      vel_1[i] = y[3];
      t[i] = x0;
    }


  // Update the output time and state vectors
  states.time = t;
  states.lead_pos = lead_pos;
  states.lead_vel = lead_vel;
  states.pos_1 = pos_1;
  states.vel_1 = vel_1;
  
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
void main_DISim(void) {
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


  // Run runga kutta over a time series
  int stopperDex = stopDex - 1;
  int n = 4; // Number of states to be simulated (Note: If we use double integrator dynamics, then each agent has 2 states, or n = 2 x (# agents + leader) )
  std::vector<double> y0(n,0); 


  // Set the initial conditions
  y0[0] = cos(freq*time[0]); // Leader initial position
  y0[2] = -2; // Agent 1 initial velocity

  
  // Run the simulation
  ODEsolver(time[0],y0,time[stopperDex],Ts, stopDex, n, freq);

  
  // Save data to .csv file so we can look at it later!!
  std::ofstream output_file;
  output_file.open("simulation_data.csv");
  output_file << "Time, ";
  output_file << "Leader_Pos, ";
  output_file << "Leader_Vel, ";
  output_file << "T_Kutta" << ", ";
  output_file << "Agent_Pos" << ", ";
  output_file << "Agent_Vel" << "\n";
  for (int i = 0; i < stopDex; i++)
    {
      output_file << time[i] << ", " ;
      output_file << states.lead_pos[i] << ", ";
      output_file << states.lead_vel[i] << ", ";
      output_file << states.time[i] << ", ";
      output_file << states.pos_1[i] << ", ";
      output_file << states.vel_1[i] << "\n";
    }
  output_file.close();
    

  
  return;
}
