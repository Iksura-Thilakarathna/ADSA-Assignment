# Traversal Module

## Purpose

The traversal module provides the graph operations used by the Smart City Public Transportation System:

- Breadth-first search (BFS) for the minimum number of edges between two locations.
- Depth-first search (DFS) for connectivity validation.
- Path reconstruction and journey measurement for the selected route.
- CLI actions for the BFS and DFS menu options.

## Key Functions

- `bfs(...)`: Finds a path from the origin to the destination with the minimum edge count.
- `isConnected(...)`: Checks whether every city location is reachable from Green Valley.
- `isSimplePath(...)`: Detects repeated vertices in a candidate path.
- `measureJourney(...)`: Calculates total distance, ride time, and transfers.
- `printPath(...)`: Displays the route, transport modes, distance, time, and path details.
- `checkBFS(...)` and `checkDFS(...)`: Connect the traversal utilities to the interactive menu.

## Implementation Notes

The BFS implementation uses an array-based queue and stores the parent and route for each visited location. The DFS implementation uses recursion and marks every reachable vertex before verifying the graph's overall connectivity.

## Build

Compile the complete project using:

```bash
g++ -O2 main.cpp -o smart_city_transit.exe
```
