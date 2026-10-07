/* ================================================================
   simulation.cpp  -  MEMBER 2 : Passenger Demand & Full-Day Simulation
   Menu options: 11, 13
   ================================================================ */
#include "simulation.h"
#include "network.h"
#include "traversal.h"
#include "routing.h"

/* ---------------- DEMAND MODEL ---------------- */

bool isPeak(int hour) {
    return demand[hour] >= PEAK_DEMAND;
}

const char *periodName(int hour) {
    if (!isPeak(hour))
        return "Normal";
    return (hour < 12) ? "Morning Peak" : "Evening Peak";
}

/* More passengers -> more crowding -> slightly longer ride */
double crowdFactor(int hour) {
    return 1.0 + CROWD_EXTRA * demand[hour] / MAX_DEMAND;
}

/* Peak: more vehicles -> shorter wait */
double averageWait(Mode mode, int hour) {
    if (mode == TRAIN)
        return isPeak(hour) ? 3.0 : 6.0;
    return isPeak(hour) ? 5.0 : 10.0;
}

/* Wait once for each new vehicle boarded */
double waitingTime(const int pathRoutes[], int length, int hour) {

    double wait = 0;
    int prevRoute = -1;

    for (int i = 1; i < length; i++) {
        if (pathRoutes[i] != prevRoute) {
            wait += averageWait(routes[pathRoutes[i]].mode, hour);
            prevRoute = pathRoutes[i];
        }
    }

    return wait;
}

/* ---------------- MENU 11 : PASSENGER DEMAND ---------------- */

void showDemand() {

    int hour;
    if (!readInt("\nEnter hour (0-23): ", 0, 23, hour))
        return;

    cout << fixed << setprecision(2);
    cout << "\n=== PASSENGER DEMAND ===\n\n";

    cout << "Time             : ";
    printClock(hour * 60);
    cout << "\n";
    cout << "Demand           : " << demand[hour] << " passengers\n";
    cout << "Period           : " << periodName(hour) << "\n";
    cout << "Crowding factor  : x" << crowdFactor(hour) << "\n";

    cout << setprecision(1);
    cout << "Average wait     : Train " << averageWait(TRAIN, hour)
         << " mins, Bus " << averageWait(BUS, hour) << " mins\n";
}

/* ---------------- RANDOM TRIP GENERATION ----------------
   Simple LCG so it works on old C++98 Dev-C++.            */

static unsigned int seedValue = 12345;

int randomNumber(int maxValue) {

    if (maxValue <= 0)
        return 0;

    seedValue = seedValue * 1103515245 + 12345;
    return (int)((seedValue / 65536) % maxValue);
}

/* Morning peak: home -> work | Evening peak: work -> home | else random */
void generateTrip(int hour, Place &origin, Place &destination) {

    if (isPeak(hour) && hour < 12) {
        origin = (Place)randomNumber(RESIDENTIAL_COUNT);
        destination = (Place)(BUSINESS + randomNumber(WORK_COUNT));
    }
    else if (isPeak(hour)) {
        origin = (Place)(BUSINESS + randomNumber(WORK_COUNT));
        destination = (Place)randomNumber(RESIDENTIAL_COUNT);
    }
    else {
        do {
            origin = (Place)randomNumber(PLACES);
            destination = (Place)randomNumber(PLACES);
        } while (origin == destination);
    }
}

/* ---------------- FULL-DAY SIMULATION ---------------- */

void runSimulation(int allowedMode, SimResult &r) {

    r = SimResult();        /* reset all values to 0 */
    seedValue = 12345;      /* same trips for every network -> fair comparison */

    for (int hour = 0; hour < 24; hour++) {

        double crowd = crowdFactor(hour);
        bool peak = isPeak(hour);

        for (int p = 0; p < demand[hour]; p++) {

            Place origin, destination;
            generateTrip(hour, origin, destination);
            r.total++;

            Place path[MAX_PATH];
            int pathRoutes[MAX_PATH];
            int length;

            if (!bestRoute(origin, destination, true, allowedMode, path, pathRoutes, length))
                continue;

            r.success++;

            Journey j = measureJourney(path, pathRoutes, length);
            double wait = waitingTime(pathRoutes, length, hour);
            double journeyTime = j.rideTime * crowd + wait;

            for (int i = 1; i < length; i++)
                r.routeUsage[pathRoutes[i]]++;

            r.distance += j.distance;
            r.totalTime += journeyTime;
            r.waitTime += wait;

            if (j.transfers == 0)      r.direct++;
            else if (j.transfers == 1) r.oneTransfer++;
            else                       r.moreTransfer++;

            if (peak) { r.peakTime += journeyTime;   r.peakCount++;   }
            else      { r.normalTime += journeyTime; r.normalCount++; }
        }
    }
}

static void printCompareRow(const char *name, const SimResult &r) {

    cout << "  " << left << setw(14) << name;

    if (r.total > 0)
        cout << right << setw(8) << (r.success * 100.0 / r.total) << " %";
    else
        cout << setw(10) << "-";

    if (r.success > 0) {
        cout << setw(12) << (r.totalTime / r.success) << " min";
        cout << setw(10) << (r.distance / (r.totalTime / 60.0)) << " km/h";
    }
    else
        cout << setw(16) << "-" << setw(14) << "-";

    cout << "\n";
}

/* ---------------- MENU 13 : PROFILING ---------------- */

void fullDaySimulation() {

    SimResult full, busOnly, trainOnly;

    runSimulation(ANY_MODE, full);
    runSimulation(BUS, busOnly);
    runSimulation(TRAIN, trainOnly);

    cout << fixed << setprecision(1);
    cout << "\n=== SYSTEM EFFICIENCY PROFILING ===\n\n";

    cout << "Total passengers simulated : " << full.total << "\n";
    cout << "Successful journeys        : " << full.success << "\n";
    cout << "Completion rate            : " << (full.success * 100.0 / full.total) << "%\n";

    if (full.success > 0) {
        cout << "Average travel time        : " << full.totalTime / full.success << " mins\n";
        cout << "Average waiting time       : " << full.waitTime / full.success << " mins\n";
        cout << "Average journey distance   : " << full.distance / full.success << " km\n";
        cout << "Average speed              : " << full.distance / (full.totalTime / 60.0) << " km/h\n";
        cout << "Direct journeys            : " << full.direct * 100.0 / full.success << "%\n";
        cout << "1-transfer journeys        : " << full.oneTransfer * 100.0 / full.success << "%\n";
        cout << "2+ transfer journeys       : " << full.moreTransfer * 100.0 / full.success << "%\n";
    }

    if (full.peakCount > 0)
        cout << "Peak average travel time   : " << full.peakTime / full.peakCount << " mins\n";

    if (full.normalCount > 0)
        cout << "Normal average travel time : " << full.normalTime / full.normalCount << " mins\n";

    cout << "\n=== ROUTE UTILISATION ===\n\n";

    for (int i = 0; i < ROUTES; i++)
        cout << "  " << left << setw(10) << routes[i].name
             << " (" << setw(5) << (routes[i].mode == TRAIN ? "Train" : "Bus")
             << ") : " << full.routeUsage[i] << " edge-uses\n";

    cout << "\n=== NETWORK COMPARISON ===\n\n";
    cout << "  " << left << setw(14) << "Network"
         << right << setw(10) << "Completed"
         << setw(16) << "Avg time"
         << setw(14) << "Avg speed" << "\n";

    printCompareRow("Train + Bus", full);
    printCompareRow("Bus only", busOnly);
    printCompareRow("Train only", trainOnly);
}
