# N-Puzzle Solver

A high-performance implementation of the N-puzzle game solver using the A* search algorithm, written in C.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Algorithm](#algorithm)
- [Installation](#installation)
- [Usage](#usage)
- [Input Format](#input-format)
- [Heuristics](#heuristics)
- [Performance](#performance)
- [Project Structure](#project-structure)
- [Examples](#examples)
- [Technical Details](#technical-details)

## Overview

The N-puzzle is a sliding puzzle that consists of a frame of numbered square tiles in random order with one tile missing. The goal is to arrange the tiles in numerical order by making sliding moves that use the empty space.

This solver uses the A* search algorithm to find the optimal solution path from any solvable initial state to the goal state (snail pattern).

## Features

- **Multiple puzzle sizes**: Supports 3x3, 4x4, 5x5, and larger puzzles
- **A* Algorithm**: Optimal pathfinding with admissible heuristics
- **Multiple heuristics**: Manhattan distance and inversion count heuristics
- **Solvability detection**: Automatically detects unsolvable puzzles
- **Performance metrics**: Reports time complexity, space complexity, and solution path
- **Optimized data structures**: Uses hash tables and heaps for efficient state management
- **Memory management**: Careful memory allocation and deallocation

## Algorithm

The solver implements the A* search algorithm with the following components:

- **g(n)**: Cost from start to current node (depth/number of moves)
- **h(n)**: Heuristic estimate from current node to goal
- **f(n) = g(n) + h(n)**: Total estimated cost

The algorithm maintains:
- **Open set**: Priority queue (min-heap) of states to explore
- **Closed set**: Hash table of already explored states
- **Path reconstruction**: Backtracking through parent nodes

## Installation

1. Clone the repository:
```bash
git clone <repository-url>
cd n-puzzle
```

2. Compile the project:
```bash
make
```

This will create the `npuzzle` executable.

## Usage

Run the solver with a puzzle file:

```bash
./npuzzle <puzzle_file>
```

Example:
```bash
./npuzzle tests/test_3_medium.txt
```

## Input Format

Input files should follow this format:

```
# Comments start with '#'
3                    # Size of the puzzle (3x3)
3 2 6                # First row
1 4 0                # Second row (0 represents empty space)
8 7 5                # Third row
```

### Rules:
- First non-comment line specifies the puzzle size (N)
- Next N lines contain N numbers each
- Numbers range from 0 to N²-1
- 0 represents the empty space
- Comments can be placed anywhere using '#'

## Heuristics

The solver implements multiple admissible heuristics:

### 1. Manhattan Distance (Primary)
Calculates the sum of Manhattan distances for each tile to its goal position:
```
distance = |current_x - goal_x| + |current_y - goal_y|
```

### 2. Inversion Count
Counts the number of tiles that are in reverse order compared to the goal state. This helps detect puzzle solvability and provides additional guidance.

### Admissibility
Both heuristics are admissible (never overestimate the actual cost), ensuring A* finds the optimal solution.

## Performance

The solver provides detailed performance metrics:

- **Time Complexity**: Total number of states in the "opened" set
- **Space Complexity**: Maximum number of states in memory simultaneously
- **Solution Length**: Number of moves in the optimal path
- **Solution Path**: Complete sequence of states from start to goal

### Optimization Features:
- Hash table for O(1) duplicate detection
- Min-heap for efficient state selection
- Memory-efficient state representation
- Pruning of impossible states

## Project Structure

```
n-puzzle/
├── Makefile              # Build configuration
├── README.md             # This file
├── npuzzle-gen.py        # Puzzle generator script
├── include/
│   └── npuzzle.h         # Header file with structures and prototypes
├── src/
│   ├── main.c            # Entry point and argument parsing
│   ├── heap.c            # Min-heap implementation and A* logic
│   ├── hashtable.c       # Hash table for duplicate detection
│   ├── heuristics.c      # Heuristic functions
│   ├── list.c            # Linked list utilities
│   └── utils.c           # Input parsing and utility functions
└── tests/
    ├── test_3_medium.txt # 3x3 test cases
    ├── test_4_medium.txt # 4x4 test cases
    └── ...               # Additional test files
```

## Examples

### Solvable 3x3 Puzzle
```bash
./npuzzle tests/test_3_medium.txt
```

Output includes:
- Solution path with intermediate states
- Number of moves required
- Performance statistics

### Unsolvable Puzzle
The solver automatically detects unsolvable configurations using parity analysis and exits with an appropriate message.

## Technical Details

### Data Structures

**State Representation (t_queue/t_heap)**:
- 2D array for puzzle configuration
- Position tracking for empty space
- Parent pointer for path reconstruction
- Depth and heuristic values

**Hash Table**:
- FNV-1a hash function for state hashing
- Collision handling with chaining
- Dynamic sizing based on puzzle complexity

**Min-Heap**:
- Priority queue for A* open set
- Efficient insertion and extraction
- f(n) = g(n) + h(n) ordering

### Memory Management
- Careful allocation/deallocation of 2D arrays
- State copying for path exploration
- Cleanup on exit and error conditions

### Solvability Check
Uses mathematical properties of the N-puzzle:
- Inversion count analysis
- Empty space position consideration
- Parity invariant validation

## Compilation Flags

The Makefile uses these compiler flags:
- `-Wall -Werror -Wextra`: Comprehensive warnings
- `-O3`: Maximum optimization
- `-g`: Debug information
- `-lncurses`: Terminal interface library

## Performance Benchmarks

Typical performance on standard puzzles:
- 3x3 medium: < 1 second
- 3x3 hard: 1-5 seconds  
- 4x4 medium: 5-30 seconds
- Larger puzzles: Performance varies based on initial state complexity

## Contributing

To extend the solver:
1. Add new heuristic functions in `heuristics.c`
2. Implement additional search algorithms
3. Optimize data structures for larger puzzles
4. Add visualization features

## Author

Created as part of the 42 School curriculum - N-puzzle project.
