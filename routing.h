/* ================================================================
   routing.h  -  MEMBER 3 : Shortest / Fastest Route using BFS
                            on an UNWEIGHTED (split-edge) graph
   ================================================================ */
#ifndef ROUTING_H
#define ROUTING_H

#include "common.h"

/* Build the two unweighted graphs once, at program start */
void buildUnitGraphs();

#define PIECES_PER_MINUTE 5   /* timeGraph: 1 piece = 0.2 min */

/* Number of small edges between two neighbouring stops
   useTime false -> km, true -> minutes x 5               */
int countPieces(bool useTime, Place from, Place to, int route);

/* BFS on the unweighted graph.
   useTime     : false = shortest km, true = fastest minutes
   allowedMode : ANY_MODE / TRAIN / BUS                       */
bool bestRoute(Place start, Place goal, bool useTime, int allowedMode,
               Place path[], int pathRoutes[], int &pathLength);

void printJourneyReport(const Place path[], const int pathRoutes[],
                        int length, int hour, int minute);

/* menu actions */
void checkBestRoute(bool useTime);
void passengerJourney();
void passengerXDemo();

#endif
