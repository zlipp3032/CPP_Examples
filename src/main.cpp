#include <iostream>
#include <vector>
#include "examples.h"



int main()
{



  // Display interactive prompt
  std::cout
    << "| Available commands:                                                                |"
    << std::endl;
  std::cout
    << "| [a] test.cpp - builds a time vector and prints it to screen                        |"
    << std::endl;
  std::cout
    << "| [b] simple_sim.cpp - builds time vector, computes sine wave, writes to .csv file   |"
    << std::endl;
  std::cout
    << "| [c] medium_sim.cpp - simulates sine wave with basic Runge Kutta, writes .csv file  |"
    << std::endl;
  std::cout
    << "| [d] hard_med_sim.cpp - same as [c], but utilizes vectors within a structure        |"
    << std::endl;
  std::cout
    << "| [e] hard_sim.cpp - same as [d], but uses different inner-loop simulate method      |"
    << std::endl;
  std::cout
    << "| [f] Double Integrator with a PD control tracking a sine wave simulation            |" // double_integrator_sim_v02.cpp
    << std::endl;
  std::cout
    << "| [g] Double Integrator Two Agent Formation control tracking a sine wave simulation  |"
    << std::endl;
  std::cout
    << "| [h] Using different clock methods to record timestamps                             |"
    << std::endl;
  std::cout
    << "| [i] Multithreading example                                                         |"
    << std::endl;



  
  
  char inputChar;
  std::cin >> inputChar;

  switch (inputChar)
    {
    case 'a':
      printf("Works!! \n");
      mainTest();
      break;
    case 'b':
      main_SimpleSim();
      break;
    case 'c':
      main_MedSim();
      break;
    case 'd':
      main_HardMedSim();
      break;
    case 'e':
      main_HardSim();
      break;
    case 'f':
      main_DISim();
      break;
    case 'g':
      main_Form2();
      break;
    case 'h':
      main_TimeStamp();
      break;
    case 'i':
      main_MultiThread();
      break;
    default:
      printf("Run again! Need to pick new commands!");
      break;
    }

  
  return 0;
}
