//examples.h


std::vector<double> time_vector(float startTime, float endTime, float Ts);

void mainTest(void);


std::vector<double> simulate_sine(std::vector<double> time, int stopDex, float freq);

void main_SimpleSim(void);

float dydx_simple(float x, float y);

void main_MedSim(void);

void main_HardMedSim(void);


void main_HardSim(void);


void main_DISim(void);

void main_Form2(void);


void main_TimeStamp(void);


void main_MultiThread(void);
