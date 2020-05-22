#include <iostream>
#include <vector>
#include <cmath> // sin function and M_PI
#include <fstream>
//#include <sstream>
//using namespace std;


struct state_t {

  std::vector<double> time;
  std::vector<double> lead_pos; // desired position
  std::vector<double> lead_vel; // desired velocity
  std::vector<double> pos_1; // agent position
  std::vector<double> vel_1; // agent velocity
} scrappy;

struct ode_state {

  float x1;
  float x2;
} scooby;


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


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


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


// This is change in state, dy, over change in interval, dx
float dydx(float x, std::vector<double> y, int derv_type, float ff, float yd, float freq) 
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
      state1 = ff - 3*(y[2] - y[0]) - 4*(y[3] - y[1]);
      break;
    default:
      printf("Pick another derv_type!");
      state1=0;
      break;
    }
      
  
  return state1; 
}


float rungeKuttaEqns(float x0, std::vector<double> y, float h, int derv_type, float ff, float yd, float freq)
{

  float k1, k2, k3, k4;
  // Apply Runge Kutta Formulas to find next value of y 
  k1 = h*dydx(x0, y, derv_type, ff, yd, freq);
  std::vector<double> temp1 = y, temp2 = y, temp3 = y;
  temp1[derv_type] = temp1[derv_type] + 0.5*k1;
  k2 = h*dydx(x0 + 0.5*h, temp1, derv_type, ff, yd, freq);
  temp2[derv_type] = temp2[derv_type] + 0.5*k2;
  k3 = h*dydx(x0 + 0.5*h, temp2, derv_type, ff, yd, freq);
  temp3[derv_type] = temp3[derv_type] + k3;
  k4 = h*dydx(x0 + h, temp3, derv_type, ff, yd, freq); 
  
  // Update next value of y 
  y[derv_type] = y[derv_type] + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);;
  
  return y[derv_type];

}




// Finds value of y for a given x using step size h and initial value y0 at x0. 
void rungeKutta(float x0, std::vector<double> y0, float x, float h, int stopDex, int nag, float freq) 
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
  std::vector<double> y = y0;
  for (int i=1; i<=n; i++) 
    {
      // Compute the integral for the current state y at x0
      
      y[0] = rungeKuttaEqns(x0, y, h, 0, 0.0, 0.0, freq);
      y[1] = rungeKuttaEqns(x0, y, h, 1, 0.0, 0.0, freq);
      
      float ff_1 =  -freq*sin(freq*x0), ff_2 = -freq*freq*cos(freq*x0); 
      y[2] = rungeKuttaEqns(x0, y, h, 2, ff_1, y[0], freq);
      y[3] = rungeKuttaEqns(x0, y, h, 3, ff_2, y[1], freq);


      
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
  scrappy.time = t;
  scrappy.lead_pos = lead_pos;
  scrappy.lead_vel = lead_vel;
  scrappy.pos_1 = pos_1;
  scrappy.vel_1 = vel_1;
  
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
int main() {
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
  int n = 4; // Number of states to be simulated
  std::vector<double> y0(n,0);
  float h0 = Ts;


  // Set the initial conditions
  y0[0] = cos(freq*time[0]);
  y0[2] = 7;

  
  // Run the simulation
  rungeKutta(time[0],y0,time[stopperDex],Ts, stopDex, n, freq);

  
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
      output_file << scrappy.lead_pos[i] << ", ";
      output_file << scrappy.lead_vel[i] << ", ";
      output_file << scrappy.time[i] << ", ";
      output_file << scrappy.pos_1[i] << ", ";
      output_file << scrappy.vel_1[i] << "\n";
    }
  output_file.close();
    

  
  return 0;
}
