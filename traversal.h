/* ================================================================
   traversal.h  -  MEMBER 4 : BFS, DFS & Path Utilities
   ================================================================ */
#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "common.h"

/* path helpers (also used by Members 2 and 3) */
bool isSimplePath(const Place path[], int length);
Journey measureJourney(const Place path[],
                       const int pathRoutes[], int length);
void printPath(const Place path[],
               const int pathRoutes[], int length);

/* algorithms */
bool bfs(const Graph &graph, Place start, Place goal,
         Place path[], int pathRoutes[], int &pathLength);
bool isConnected(const Graph &graph);

#endif
