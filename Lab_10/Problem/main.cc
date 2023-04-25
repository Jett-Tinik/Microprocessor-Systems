#include <chrono>
#include <ctime>
#include <iostream>

#include "GravSim.hh"
using namespace std;

int main(int argc, char* argv[]) {
  auto start = std::chrono::system_clock::now();

  GravSim sim("solarsys.dat");
  const double secondsInYear = 365.2425 * 24 * 60 * 60;
  const double dt = 10;
  const uint32_t numTimeSteps = uint32_t(secondsInYear / dt);
  const uint32_t numStepsPerPrint = numTimeSteps;
  for (uint32_t i = 0; i < numTimeSteps; i += numStepsPerPrint) {
    sim.forward(numStepsPerPrint, dt);
  }
  auto end = std::chrono::system_clock::now();
  int mytestvariable = 0;
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished computation at " << std::ctime(&end_time)
            << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
