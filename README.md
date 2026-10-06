# Smart City Public Transportation System

> **Academic Context**: IS2202 - Data Structures & Algorithms (Group Assignment: Problem C)  
> **Domain**: Graph Theory, Urban Transportation Simulation, and Multi-Modal Pathfinding

---

## 1. Project Overview

The **Smart City Public Transportation System** is a comprehensive C++ console application designed to model, simulate, and analyze an urban public transit network. Developed for the **IS2202 Data Structures and Algorithms** course assignment (Problem C), this application evaluates the operational efficiency of a future smart city paradigm where private motor vehicles are prohibited, forcing complete reliance on a synchronized multi-modal public transit network (buses and trains).

Using **Graph Theory**, the city is modeled as an **undirected, weighted graph** stored via an **Adjacency List**. The system implements multi-modal pathfinding (Dijkstra's Algorithm), minimum-hop routing (Breadth-First Search), and network connectivity validation (Depth-First Search). In addition, it integrates a **24-Hour Passenger Demand & Dynamic Delay Engine** that simulates time-dependent crowding penalties, service-frequency waiting times, multi-leg transfer itineraries (e.g., Passenger X scenario), and full-day network profiling across thousands of randomized passenger journeys.

---

## 2. Key Features

- **Graph-Based City Topology**: Models 12 key municipal locations connected by 7 transit routes (2 Train lines operating at 60 km/h and 5 Bus lines operating at 25 km/h).
- **Adjacency List Graph Architecture**: Space-efficient $O(V + E)$ structure supporting multi-graph properties (route IDs, physical distances, transit modes).
- **Multi-Modal Route Optimization**:
  - **Shortest Distance Route**: Calculates the physically shortest path in kilometers using Dijkstra's algorithm.
  - **Fastest Travel Time Route**: Calculates the time-optimized path in minutes, factoring in vehicle speeds, crowding delays, and transfer wait times.
  - **Mode-Restricted Routing**: Filters search spaces for Train-only, Bus-only, or Combined transit modes.
- **Topological Analysis & Edge-Hop Optimization**:
  - **BFS Route Search**: Finds paths minimizing the total number of stops/transfers (minimum edge count).
  - **DFS Network Validation**: Recursively checks graph connectivity to ensure all city vertices remain connected.
- **Dynamic 24-Hour Simulation Engine**:
  - **Variable Passenger Demand**: Models hourly demand fluctuations ranging from 60 to 650 passengers/hour with distinct morning and evening peak windows.
  - **Crowding Penalties**: Dynamically scales ride durations by up to +30% during peak demand periods.
  - **Service Headways & Wait Times**: Computes realistic passenger wait times based on transit mode and peak/normal demand periods.
- **Multi-Modal Transfer Planning (Passenger X Scenario)**: Solves multi-leg itineraries requiring specific mode transfer sequences (e.g., Train from Green Valley to Central, then transfer to Bus to Riverside at 07:00 AM).
- **Full-Day System Efficiency Profiling**: Simulates ~7,890 passenger trips across 24 hours to analyze completion rates, average travel/wait times, average journey speed, transfer distributions, individual route utilization, and comparative benchmarks across network configurations.
- **Interactive Command-Line Interface (CLI)**: A 13-option menu driven interface allowing users to inspect graph data, execute pathfinding queries, simulate passenger journeys, and execute full-day system profiling.

---

## 3. Data Structures & Algorithms

### Data Structures

- **Adjacency List (`Graph`)**:
  - Represented as an array of vectors (`std::vector<Edge> adj[12]`).
  - Provides optimal memory complexity of $O(V + E)$ and fast neighbor iteration during graph traversals.
- **Edge Representation (`Edge`)**:
  - `to`: Destination vertex ID (`Place`).
  - `distance`: Physical distance in kilometers (`double`).
  - `route`: Transit line identifier linking to global route specifications (`int`).
- **Route Specification (`Route`)**:
  - Encapsulates line name, transport mode (`TRAIN` or `BUS`), stop count, ordered stop sequence (`Place stops[]`), and segment distances (`double distance[]`).
- **Standard Library Collections**:
  - `std::vector` for adjacency lists and route structures.
  - `std::queue` for Breadth-First Search level-order traversal.

### Core Algorithms

| Algorithm | Primary Purpose | Time Complexity | Space Complexity |
|---|---|---|---|
| **Dijkstra's Algorithm (Array-Based)** | Shortest Distance & Fastest Time Pathfinding | $O(V^2 + E)$ | $O(V)$ |
| **Breadth-First Search (BFS)** | Minimum Edge Hops (Fewest Stops/Transfers) | $O(V + E)$ | $O(V)$ |
| **Depth-First Search (DFS)** | Network Connectivity Validation (`isConnected()`) | $O(V + E)$ | $O(V)$ |
| **Linear Congruential Generator (LCG)** | Deterministic Pseudo-Random Trip Generation | $O(1)$ | $O(1)$ |

---

## 4. Graph Topology & Network Specifications

### Vertices ($V = 12$ City Locations)

| ID | Location Name | Vertex Index | Category / Role |
|---|---|---|---|
| 1 | Green Valley | `0` | Residential |
| 2 | Lakeside | `1` | Residential |
| 3 | Hill Town | `2` | Residential |
| 4 | Riverside | `3` | Residential |
| 5 | Central | `4` | Central Transit Hub |
| 6 | Tech Park | `5` | Commercial / Industrial |
| 7 | Business | `6` | Business District |
| 8 | Harbour | `7` | Maritime / Commercial |
| 9 | University | `8` | Educational |
| 10 | Hospital | `9` | Essential Healthcare |
| 11 | Airport | `10` | International Terminal |
| 12 | City Mall | `11` | Commercial / Retail |

### Edges ($E = 7$ Public Transit Routes)

#### Train Lines (Operating Speed: 60 km/h)
- **Red Line** (4 stops): Green Valley $\leftrightarrow$ Central (8 km) $\leftrightarrow$ Business (5 km) $\leftrightarrow$ Airport (12 km)
- **Blue Line** (4 stops): Lakeside $\leftrightarrow$ University (7 km) $\leftrightarrow$ Central (6 km) $\leftrightarrow$ Harbour (6 km)

#### Bus Lines (Operating Speed: 25 km/h)
- **Bus 1** (4 stops): Green Valley $\leftrightarrow$ Hill Town (4 km) $\leftrightarrow$ Tech Park (5 km) $\leftrightarrow$ Business (4 km)
- **Bus 2** (4 stops): Central $\leftrightarrow$ Tech Park (3 km) $\leftrightarrow$ Hospital (4 km) $\leftrightarrow$ Riverside (4 km)
- **Bus 3** (4 stops): Lakeside $\leftrightarrow$ City Mall (5 km) $\leftrightarrow$ Hospital (4 km) $\leftrightarrow$ Business (5 km)
- **Bus 4** (3 stops): University $\leftrightarrow$ Riverside (4 km) $\leftrightarrow$ Harbour (5 km)
- **Bus 5** (3 stops): Airport $\leftrightarrow$ City Mall (6 km) $\leftrightarrow$ Hill Town (5 km)

---

## 5. Tech Stack & Dependencies

- **Programming Language**: C++ (Fully compatible with C++98, C++11, C++14, C++17, and C++20).
- **Standard Libraries Used**: `<iostream>`, `<iomanip>`, `<vector>`, `<queue>`, `<string>`, `<stdlib.h>`.
- **Target Compilers**: `g++` (GCC), Clang, MSVC, Dev-C++ (MinGW).
- **Platform Support**: Cross-platform (Windows, Linux, macOS).

---

## 6. Compilation & Execution Instructions

### Prerequisites
Ensure a standard C++ compiler (such as `g++`) is installed and configured in your system environment path.

### Standard Compilation
Compile the source code using standard `g++` flags:

```bash
g++ -O2 main.cpp -o smart_city_transit.exe
```

### Legacy Compiler / C++98 Compatibility
To compile under strict C++98 standard constraints (e.g., in Dev-C++ or older evaluation environments):

```bash
g++ -std=c++98 main.cpp -o smart_city_transit.exe
```

### Running the Application

**Windows (PowerShell / Command Prompt):**
```cmd
.\smart_city_transit.exe
```

**Linux / macOS Terminal:**
```bash
./smart_city_transit.exe
```

---

## 7. Interactive Menu Options

The application provides a 13-option CLI menu for inspecting graph data and running simulations:

```text
==============================================
     SMART CITY PUBLIC TRANSPORT SYSTEM
==============================================
  1. View City Locations
  2. View Bus Network
  3. View Train Network
  4. View Adjacency List
  5. BFS Route Search
  6. DFS Connectivity Check
  7. Vertex Degrees / Main Hub
  8. Shortest Distance Route
  9. Fastest Route
 10. Passenger Journey
 11. Passenger Demand
 12. Passenger X Assignment
 13. Full-Day Simulation / Profiling
  0. Exit
==============================================
```

### Detailed Menu Functionality

1. **View City Locations**: Displays the enumerated roster of all 12 city vertices.
2. **View Bus Network**: Lists all 5 bus routes, stop counts, and stop sequences.
3. **View Train Network**: Lists all train routes (Red Line and Blue Line) and stop sequences.
4. **View Adjacency List**: Prints the complete graph structure showing vertex neighbors, transit line names, and edge distances in km.
5. **BFS Route Search**: Executes Breadth-First Search to find paths with the minimum number of edges (stops/transfers).
6. **DFS Connectivity Check**: Executes Depth-First Search from Green Valley to verify complete graph connectivity.
7. **Vertex Degrees / Main Hub**: Calculates the vertex degree for each location and identifies the primary transit hub (`Central`, degree = 5).
8. **Shortest Distance Route**: Runs Dijkstra's algorithm using physical distance (km) as edge weights.
9. **Fastest Route**: Runs Dijkstra's algorithm using travel time (minutes) as edge weights based on vehicle speeds.
10. **Passenger Journey**: Interactive travel assistant that calculates exact departure/arrival times, crowding delay penalties, wait times, and route sequences for a named passenger.
11. **Passenger Demand**: Displays passenger load, period classification (Normal, Morning Peak, Evening Peak), crowding factor, and estimated wait times for any hour (0–23).
12. **Passenger X Assignment**: Solves the IS2202 Problem C required assignment scenario (07:00 AM trip from Green Valley to Riverside via Central using Train then Bus).
13. **Full-Day Simulation / Profiling**: Simulates ~7,890 passenger journeys over a 24-hour cycle, outputting network completion rates, average travel/wait times, average speed, transfer counts, route usage metrics, and a comparative efficiency matrix (Combined vs. Bus-only vs. Train-only).
0. **Exit**: Terminates the program.

---

## 8. Simulation & System Profiling Metrics

The system profiling module measures performance across a full 24-hour cycle:

- **Completion Rate (%)**: Percentage of generated passenger trip requests successfully completed.
- **Average Journey Time (mins)**: Total duration including pure ride time, crowding delay, and transfer waiting penalties.
- **Average Travel Speed (km/h)**: Net speed evaluated across distance traveled divided by total journey time.
- **Transfer Breakdown**: Percentage of direct trips, 1-transfer trips, and multi-transfer trips.
- **Route Utilization**: Counts total edge traversals per line to highlight peak usage corridors.
- **Network Benchmark Comparison**:
  - **Combined Network (Train + Bus)**: Achieves 100% completion rate with optimal travel times.
  - **Bus-Only Network**: High coverage but lower average speed (25 km/h) and longer journey times.
  - **Train-Only Network**: High transit speed (60 km/h) but fragmented connectivity leading to lower overall completion rates.

---

## 9. Academic Integrity & Credits

### Academic Information
- **Course**: IS2202 - Data Structures and Algorithms
- **Assignment**: Group Assignment (Problem C: Smart City Public Transportation System)
- **Submission Deadline**: October 6, 2026

### Group Members
| Name | Student ID / Index | Contribution / Module |
|---|---|---|
| *[Member 1 Name]* | *[Index Number]* | Graph Data Structure & BFS/DFS Implementation |
| *[Member 2 Name]* | *[Index Number]* | Dijkstra Engine & Multi-Modal Pathfinding |
| *[Member 3 Name]* | *[Index Number]* | 24-Hour Passenger Demand & Dynamic Delay Model |
| *[Member 4 Name]* | *[Index Number]* | System Profiling, Benchmarking & CLI Menu Interface |