# Search Algorithms Visualization with OpenGL

An educational project that visualizes in real-time various search algorithms on graphs generated from Delaunay triangulation. Implemented in C++ with OpenGL for an interactive graphics experience.

## Project Description

This project implements an interactive visualization of 7 popular search algorithms working on a graph generated dynamically using Delaunay triangulation. Users can:

- Generate random points in 2D
- Automatically construct a graph from Delaunay triangulation
- Select start and end points
- Execute different search algorithms
- Visualize in real-time the path found and nodes visited

## Implemented Algorithms

The project implements 7 different search algorithms:

1. **BFS (Breadth-First Search)**
   - Explores all nodes at distance k before exploring those at distance k+1
   - Guarantees finding the shortest path in unweighted graphs

2. **DFS (Depth-First Search)**
   - Explores as deep as possible in each branch before backtracking
   - Useful for exploration and cycle detection

3. **A***
   - Heuristic search that combines actual cost with estimated heuristic
   - More efficient than Dijkstra when having a good heuristic
   - Uses Euclidean distance as heuristic

4. **Greedy Best-First**
   - Selects the node that appears most promising according to the heuristic
   - Does not guarantee optimal solution but is fast
   - Uses Euclidean distance to destination

5. **Hill Climbing**
   - Local algorithm that always moves towards the best neighbor
   - Can get stuck in local optima
   - Does not guarantee finding a solution

6. **Dijkstra**
   - Finds the shortest weighted path
   - Guarantees optimal solution
   - Uses Euclidean distance as edge weight

7. **IDA* (Iterative Deepening A*)**
   - Combines Iterative Deepening with A*
   - Saves memory compared to traditional A*
   - Guarantees finding the optimal solution

## Project Structure

```
Search Algorithms OpenGL/
├── Makefile
├── main.cpp
├── include/
│   ├── Algorithms.h
│   ├── delaunator.hpp
│   ├── Globals.h
│   ├── Graph.h
│   ├── Input.h
│   ├── Point.h
│   ├── Renderer.h
│   └── Utils.h
├── src/
│   ├── Algorithms.cpp
│   ├── Globals.cpp
│   ├── Graph.cpp
│   ├── Input.cpp
│   ├── Renderer.cpp
│   └── Utils.cpp
```

## Main Components

### Globals
- `NUM_POINTS`: Number of points to generate (default: 1000)
- `MARGIN`: Screen margin (default: 0.95)
- `points`: Vector of 2D points
- `coords`: Coordinates in flat format for Delaunator
- `graph`: Adjacency graph
- `path`: Path found by the algorithm
- `nodes_visited`: Nodes visited during search
- `triangulation`: Delaunay triangulation
- `start_point`: Selected starting point
- `end_point`: Selected destination point

### Graph
- `generate_points()`: Generates random 2D points
- `compute_triangulation()`: Computes Delaunay triangulation
- `build_graph()`: Builds graph from triangulation
- `nearest_point()`: Finds nearest point to a coordinate
- `run_algorithm()`: Executes the selected algorithm

### Renderer
- `draw_mesh()`: Draws triangle mesh
- `draw_points()`: Draws points
- `draw_path()`: Draws the found path
- `display()`: Main rendering function

### Input
- `mouse()`: Handles mouse events
- `keyboard()`: Handles keyboard events

## Requirements

- **Compiler**: G++ with C++17 support
- **OpenGL**: GLUT, GLU, GL
- **System**: Linux/Unix
- **Other**: Make

### Installing Dependencies (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install freeglut3-dev mesa-utils libglu1-mesa-dev
```

## Compilation

From the project root:

```bash
make clean
make
```

The executable will be generated as `main`.

## Execution

```bash
make run
```

Or directly:

```bash
./main
```

## 🎮 Controls

### Mouse
- **Left click**: Select points
  - First click: Define start point (green color)
  - Second click: Define destination point (red color)
  - Following clicks: Redefine start point

### Keyboard
| Key | Action |
|-----|--------|
| `1` | Run BFS |
| `2` | Run DFS |
| `3` | Run A* |
| `4` | Run Greedy Best-First |
| `5` | Run Hill Climbing |
| `6` | Run Dijkstra |
| `7` | Run IDA* |
| `R` | Reset - Clear points and path |
| `G` | Generate - Generate new points |
| `ESC` | Exit program |

## Visualization

- **White**: Normal points
- **Green**: Starting point
- **Red**: Destination point
- **Yellow**: Nodes visited during search
- **Blue**: Found path (thick line)
- **White**: Delaunay triangulation mesh

## Features

- Automatic generation of random points
- Delaunay triangulation for graph construction
- 7 different search algorithms
- Execution time measurement in microseconds
- Real-time visualization with OpenGL
- Interactive interface with mouse and keyboard
- Statistics: path found, nodes visited, execution time

## Execution Results

When executing an algorithm, the console shows:
- Name of the executed algorithm
- Length of the found path
- Sequence of nodes in the path
- Number of visited nodes
- Execution time in microseconds

Example:
```
Running BFS...
Path length: 42
Path: 0 5 12 18 25 ... 98 105
Visited: 156 nodes
Execution time: 2341 microseconds
```

## Technical Details

### Delaunay Triangulation
- Uses `delaunator.hpp` library
- Generates a connected graph where each triangle provides edges
- Duplicates are removed from the adjacency list

### Distance Metrics
- **BFS/DFS**: Unweighted (distance = 1 for any edge)
- **A*/Greedy/Dijkstra/IDA***: Euclidean distance between points
- **Hill Climbing**: Euclidean distance to destination

### Space and Time Complexity
- **Point generation**: O(N)
- **Delaunay triangulation**: O(N log N)
- **BFS/DFS**: O(V + E)
- **A*/Dijkstra**: O((V + E) log V) with binary heap
- **Hill Climbing**: O(V) in best case
- **IDA***: O(b^d) where b is branching factor and d is depth

## References

- [Delaunay Triangulation](https://en.wikipedia.org/wiki/Delaunay_triangulation)
- [A* Search Algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm)
- [OpenGL Documentation](https://www.khronos.org/opengl/)
- [GLUT Documentation](https://www.opengl.org/resources/libraries/glut/)

## License

This project is open source for educational purposes.