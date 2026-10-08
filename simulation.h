/* ================================================================
   simulation.h  -  MEMBER 2 : Passenger Demand & Full-Day Simulation
   ================================================================ */
#ifndef SIMULATION_H
#define SIMULATION_H

#include "common.h"

struct SimResult {
    int total, success;
    int direct, oneTransfer, moreTransfer;
    int peakCount, normalCount;
    double distance, totalTime, waitTime, peakTime, normalTime;
    int routeUsage[ROUTES];
};

/* demand model (also used by Member 3's journey report) */
bool isPeak(int hour);
const char *periodName(int hour);
double crowdFactor(int hour);
double averageWait(Mode mode, int hour);
double waitingTime(const int pathRoutes[], int length, int hour);

/* simulation */
int randomNumber(int maxValue);
void generateTrip(int hour, Place &origin, Place &destination);
void runSimulation(int allowedMode, SimResult &r);

/* menu actions */
void showDemand();
void fullDaySimulation();

#endif
