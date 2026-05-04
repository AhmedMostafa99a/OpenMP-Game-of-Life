# Conway's Game of Life - Parallel OpenMP Implementation

[![OpenMP](https://img.shields.io/badge/OpenMP-Parallel-blue.svg)](https://www.openmp.org/)

## Overview

A high-performance parallel implementation of **Conway's Game of Life** using **OpenMP** for shared-memory parallelism. This implementation features configurable grid initialization, terminal-based visualization with colored output, and optimized parallel computation of cellular automaton rules.

## Features

- **Parallel Processing**: Leverages OpenMP for multi-threaded performance
- **Dual Initialization Modes**: 
  - Random initialization (50% alive probability)
  - Percentage-based initialization (customizable alive cell ratio)
- **Interactive Interface**: User-friendly menu system
- **Configurable Simulation**: Adjustable grid size and generation count
- **Memory Efficient**: Uses 1D array with halo borders for boundary handling

## Getting Started

```bash
# Compile the program
gcc -fopenmp game_of_life.c -o game_of_life
export OMP_NUM_THREADS=4

# Run the program
./game_of_life
```

### Interactive Menu

```
=== Hello in Game Of Life === 
Choose an option:
[1] Random initialization
[2] Percentage-based initialization
[3] Exit Program
```

## Game Rules

The Game of Life follows four simple rules:

1. **Survival**: A live cell with 2 or 3 live neighbors survives
2. **Death by underpopulation**: A live cell with <2 live neighbors dies
3. **Death by overpopulation**: A live cell with >3 live neighbors dies
4. **Birth**: A dead cell with exactly 3 live neighbors becomes alive