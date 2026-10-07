/* ================================================================
   network.h  -  MEMBER 1 : Graph Construction & Network Display
   ================================================================ */
#ifndef NETWORK_H
#define NETWORK_H

#include "common.h"

/* input / output helpers */
bool readInt(const char *prompt, int low, int high, int &value);
void printClock(int minutes);
bool askOriginDestination(Place &origin, Place &destination);

/* graph */
void addEdge(Graph &graph, Place a, Place b, int route);
void buildGraph(Graph &graph);

/* display */
void printLocations();
void printRoutes(Mode mode);
void printAdjacencyList(const Graph &graph);
void printDegrees(const Graph &graph);

#endif
