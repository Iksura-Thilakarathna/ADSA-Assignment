/* ================================================================
   traversal.cpp  -  MEMBER 4 : BFS, DFS & Path Utilities
   Menu options: 5, 6
   ================================================================ */
#include "traversal.h"
#include "network.h"
#include "routing.h"

/* ---------------- PATH RECONSTRUCTION ----------------
   Used by BFS: follow parent[] back from goal,
   then reverse. pathRoutes[i] = route used to reach path[i].   */

static bool buildPath(Place start, Place goal,
                      const int parent[], const int parentRoute[],
                      Place path[], int pathRoutes[], int &pathLength) {

    Place revPath[MAX_PATH];
    int revRoutes[MAX_PATH];
    int n = 0;
    int cur = goal;

    while (cur != start && n < MAX_PATH - 1) {
        revPath[n] = (Place)cur;
        revRoutes[n] = parentRoute[cur];
        n++;
        cur = parent[cur];
        if (cur == -1)
            return false;
    }

    if (cur != start)
        return false;

    revPath[n] = start;
    revRoutes[n] = -1;
    n++;

    for (int i = 0; i < n; i++) {
        path[i] = revPath[n - 1 - i];
        pathRoutes[i] = revRoutes[n - 1 - i];
    }

    pathLength = n;
    return true;
}

/* ---------------- BFS ----------------
   Uses an array queue. Finds the path with the minimum
   NUMBER OF EDGES (not minimum distance).                */

bool bfs(const Graph &graph, Place start, Place goal,
         Place path[], int pathRoutes[], int &pathLength) {

    bool visited[PLACES] = {false};
    int parent[PLACES], parentRoute[PLACES];

    for (int i = 0; i < PLACES; i++)
        parent[i] = parentRoute[i] = -1;

    Place queue[PLACES];
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = true;
    pathLength = 0;

    while (front < rear) {

        Place curr = queue[front++];

        if (curr == goal)
            break;

        for (int j = 0; j < graph.edgeCount[curr]; j++) {

            const Edge &e = graph.edges[curr][j];

            if (!visited[e.to]) {
                visited[e.to] = true;
                parent[e.to] = curr;
                parentRoute[e.to] = e.route;
                queue[rear++] = e.to;
            }
        }
    }

    if (!visited[goal])
        return false;

    return buildPath(start, goal, parent, parentRoute, path, pathRoutes, pathLength);
}

/* ---------------- DFS ---------------- */

static void dfsVisit(const Graph &graph, Place current, bool visited[]) {

    visited[current] = true;

    for (int j = 0; j < graph.edgeCount[current]; j++)
        if (!visited[graph.edges[current][j].to])
            dfsVisit(graph, graph.edges[current][j].to, visited);
}

bool isConnected(const Graph &graph) {

    bool visited[PLACES] = {false};

    dfsVisit(graph, GREEN_VALLEY, visited);

    for (int i = 0; i < PLACES; i++)
        if (!visited[i])
            return false;

    return true;
}

bool isSimplePath(const Place path[], int length) {

    for (int i = 0; i < length; i++)
        for (int j = i + 1; j < length; j++)
            if (path[i] == path[j])
                return false;

    return true;
}

/* ---------------- JOURNEY MEASUREMENT ---------------- */

Journey measureJourney(const Place path[],
                       const int pathRoutes[], int length) {

    Journey j;
    j.distance = 0;
    j.rideTime = 0;
    j.transfers = 0;

    int prevRoute = -1;

    for (int i = 1; i < length; i++) {

        /* km and minutes come from COUNTING small edges */
        j.distance += countPieces(false, path[i - 1], path[i], pathRoutes[i]);
        j.rideTime += countPieces(true, path[i - 1], path[i], pathRoutes[i])
                      / (double)PIECES_PER_MINUTE;

        if (prevRoute != -1 && prevRoute != pathRoutes[i])
            j.transfers++;

        prevRoute = pathRoutes[i];
    }

    return j;
}

void printPath(const Place path[],
               const int pathRoutes[], int length) {

    cout << fixed << setprecision(1);

    cout << "  Path    : ";
    for (int i = 0; i < length; i++)
        cout << (i ? " -> " : "") << placeNames[path[i]];

    cout << "\n  Routes  : ";
    int prevRoute = -1;

    for (int i = 1; i < length; i++) {

        int r = pathRoutes[i];

        if (r != prevRoute) {
            if (prevRoute != -1)
                cout << " -> ";
            cout << routes[r].name << " ("
                 << (routes[r].mode == TRAIN ? "Train" : "Bus") << ")";
            prevRoute = r;
        }
    }

    Journey j = measureJourney(path, pathRoutes, length);

    cout << "\n  Distance : " << j.distance << " km\n";
    cout << "  Ride time: " << j.rideTime << " mins (no waiting)\n";
    cout << "  Transfers: " << j.transfers << "\n";
    cout << "  Path type: "
         << (isSimplePath(path, length) ? "Simple Path" : "Path with repeated vertices") << "\n";
    cout << "  Edges    : " << length - 1 << "\n";
}

/* ---------------- MENU ACTIONS ---------------- */

void checkBFS(const Graph &graph) {

    Place origin, destination;
    if (!askOriginDestination(origin, destination))
        return;

    Place path[MAX_PATH];
    int pathRoutes[MAX_PATH];
    int length;

    if (!bfs(graph, origin, destination, path, pathRoutes, length)) {
        cout << "No path found.\n";
        return;
    }

    cout << "\n=== BFS ROUTE RESULT ===\n\n";
    printPath(path, pathRoutes, length);
    cout << "\nBFS selects a path with the minimum number of edges.\n";
}

void checkDFS(const Graph &graph) {

    cout << "\n=== DFS CONNECTIVITY CHECK ===\n\n";
    cout << (isConnected(graph) ? "Combined network is CONNECTED.\n"
                                : "Combined network is NOT CONNECTED.\n");
}
