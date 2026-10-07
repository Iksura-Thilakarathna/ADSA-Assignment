/* ================================================================
   network.cpp  -  MEMBER 1 : Graph Construction & Network Display
   Menu options: 1, 2, 3, 4, 7
   ================================================================ */
#include "network.h"
#include "routing.h"

/* ---------------- INPUT / OUTPUT HELPERS ---------------- */

bool readInt(const char *prompt, int low, int high, int &value) {

    cout << prompt;

    if (!(cin >> value)) {
        if (cin.eof())
            return false;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number.\n";
        return false;
    }

    if (value < low || value > high) {
        cout << "Number must be between " << low << " and " << high << ".\n";
        return false;
    }

    return true;
}

void printClock(int minutes) {

    minutes %= 1440;
    int h = minutes / 60;
    int m = minutes % 60;

    cout << (h < 10 ? "0" : "") << h << ":"
         << (m < 10 ? "0" : "") << m;
}

void printLocations() {

    cout << "\n=== CITY LOCATIONS ===\n\n";

    for (int i = 0; i < PLACES; i++)
        cout << "  " << setw(2) << (i + 1) << " - " << placeNames[i] << "\n";
}

bool askOriginDestination(Place &origin, Place &destination) {

    printLocations();

    int a, b;
    cout << "\n";

    if (!readInt("Enter origin number (1-12): ", 1, PLACES, a))
        return false;

    if (!readInt("Enter destination number (1-12): ", 1, PLACES, b))
        return false;

    if (a == b) {
        cout << "Origin and destination must be different.\n";
        return false;
    }

    origin = (Place)(a - 1);
    destination = (Place)(b - 1);
    return true;
}

/* ---------------- GRAPH CONSTRUCTION ---------------- */

/* Undirected graph: A -> B and B -> A */
void addEdge(Graph &graph, Place a, Place b, int route) {

    if (graph.edgeCount[a] < MAX_EDGES) {
        Edge &e = graph.edges[a][graph.edgeCount[a]++];
        e.to = b;
        e.route = route;
    }

    if (graph.edgeCount[b] < MAX_EDGES) {
        Edge &e = graph.edges[b][graph.edgeCount[b]++];
        e.to = a;
        e.route = route;
    }
}

void buildGraph(Graph &graph) {

    for (int i = 0; i < PLACES; i++)
        graph.edgeCount[i] = 0;

    for (int r = 0; r < ROUTES; r++)
        for (int s = 0; s < routes[r].stopCount - 1; s++)
            addEdge(graph, routes[r].stops[s], routes[r].stops[s + 1], r);
}

/* ---------------- NETWORK DISPLAY ---------------- */

void printRoutes(Mode mode) {

    cout << "\n" << (mode == TRAIN ? "=== TRAIN NETWORK ===" : "=== BUS NETWORK ===") << "\n\n";

    for (int r = 0; r < ROUTES; r++) {

        if (routes[r].mode != mode)
            continue;

        cout << "  " << left << setw(10) << routes[r].name << " : ";

        for (int s = 0; s < routes[r].stopCount; s++)
            cout << (s ? " -> " : "") << placeNames[routes[r].stops[s]];

        cout << "\n";
    }
}

void printAdjacencyList(const Graph &graph) {

    cout << "\n=== GRAPH REPRESENTATION: ADJACENCY LIST ===\n\n";
    cout << fixed << setprecision(0);

    for (int i = 0; i < PLACES; i++) {

        cout << left << setw(15) << placeNames[i] << " : ";

        for (int j = 0; j < graph.edgeCount[i]; j++) {
            const Edge &e = graph.edges[i][j];
            cout << (j ? " | " : "") << placeNames[e.to]
                 << " [" << routes[e.route].name << ", "
                 << countPieces(false, (Place)i, e.to, e.route) << " km]";
        }

        cout << "\n";
    }
}

void printDegrees(const Graph &graph) {

    cout << "\n=== VERTEX DEGREE / MAIN HUB ===\n\n";

    int highest = -1;
    Place hub = GREEN_VALLEY;

    for (int i = 0; i < PLACES; i++) {

        int degree = graph.edgeCount[i];

        cout << "  " << left << setw(15) << placeNames[i]
             << " degree = " << degree << "\n";

        if (degree > highest) {
            highest = degree;
            hub = (Place)i;
        }
    }

    cout << "\nMain transportation hub: " << placeNames[hub]
         << " (degree = " << highest << ")\n";
}
