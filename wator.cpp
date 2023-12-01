/**
 * @file wator.cpp
 * @author Daniel Giedraitis (C00260331)
 * @brief A simulation of the Wa-Tor world using SFML library for graphics and OpenMP for parallel programming.
 * @date 04/11/2023
 * @copyright GPL-3.0
 */

#include <SFML/Graphics.hpp>  // SFML library for graphics  
#include <chrono> // For time-based functionalities
#include <stdlib.h> // Standard library
#include <iostream> // Input/output streams
#include <fstream>  // File stream
#include <omp.h>  // OpenMP for parallel programming

// Constants defining various parameters
const int maxDuration = 100;
const int maxThreads = 8;
const int fishBreed = 1;
const int sharkBreed = 6;
const int energyGain = 1;
const int starve = 2;
const int xdim = 800;
const int ydim = 800;
const int WindowXSize = 1000;
const int WindowYSize = 800;
const int tileXSize = WindowXSize / xdim;
const int tileYSize = WindowYSize / ydim;
int numThreads = 0;
struct Tile;

// Enumeration defining different types of tiles in the simulation
enum TileType { 
  Ocean, 
  Fish, 
  Shark 
};

// Structure representing a tile in the simulation
struct Tile {
    TileType tiletype;
    sf::Color color;
    int energy = 0;
    int turn = 0;
    int x;
    int y;
    bool hasMoved = false;
};

// Window for displaying the simulation
sf::RenderWindow window(sf::VideoMode(WindowXSize,WindowYSize), "SFML Wa-Tor world");

// Array to store rectangle shapes for display
sf::RectangleShape display[xdim][ydim];

// Array to represent the world as tiles
Tile tiles[xdim][ydim];

// Array to hold decision data for threads
drand48_data DecisionData[maxThreads];

// Array to store durations for each output
int durations[maxDuration];

/**
 * @brief Get the color of a tile at given coordinates.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 * @return Color of the tile.
 */
sf::Color getColor(int x, int y) { return tiles[y][x].color; }

/**
 * @brief Check if the creature at given coordinates has moved.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 * @return True if the creature has moved, false otherwise.
 */
bool hasMoved(int x, int y) { return tiles[y][x].hasMoved; }

/**
 * @brief Set the tile at the given coordinates to Ocean type.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 */
void setOcean(int x, int y) { 
  Tile tile;
  tile.tiletype = TileType::Ocean;
  tile.color = sf::Color::Blue;
  tile.x = x;
  tile.y = y;
  tiles[y][x] = tile;
}

/**
 * @brief Set the tile at the given coordinates to Fish type.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 */
void setFish(int x, int y) { 
  Tile tile;
  tile.tiletype = TileType::Fish;
  tile.color = sf::Color::Green;
  tile.turn = 0;
  tile.hasMoved = false;
  tile.x = x;
  tile.y = y;
  tiles[y][x] = tile;
}

/**
 * @brief Set the tile at the given coordinates to Shark type.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 */
void setShark(int x, int y) { 
  Tile tile;
  tile.tiletype = TileType::Shark;
  tile.color = sf::Color::Red;
  tile.energy = starve;
  tile.turn = 0;
  tile.hasMoved = false;
  tile.x = x;
  tile.y = y;
  tiles[y][x] = tile;
}

/**
 * @brief Get the tile at the given coordinates.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 * @return The tile at the specified coordinates.
 */
Tile getTile(int x, int y) {
  return tiles[y][x];
}

/**
 * @brief Set the tile at the given coordinates.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 * @param tile Tile to set at the coordinates.
 */
void setTile(int x, int y, Tile tile) {
  tile.x = x;
  tile.y = y;
  tiles[y][x] = tile;
}

/**
 * @brief Set the neighboring tiles around the given coordinates.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 * @param list Array to store neighboring tiles.
 */
void setNeighbours(int x, int y, Tile list[]) {
    int offsetsX[] = {0, 1, 0, -1};
    int offsetsY[] = {-1, 0, 1, 0};

    for (int i = 0; i < 4; ++i) {
        int newX = (x + offsetsX[i] + xdim) % xdim;
        int newY = (y + offsetsY[i] + ydim) % ydim;
        list[i] = getTile(newX, newY);
    }
}

/**
 * @brief Move the fish creature at the given coordinates.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 */
void moveFish(int x, int y) {
    Tile fish = getTile(x, y);
    Tile neighbours[4];
    setNeighbours(x, y, neighbours);
    long location;
    lrand48_r(&DecisionData[omp_get_thread_num()], &location);
    location = location % 4;
    for (int i = 0; i < 4; i++) {
        int x2 = neighbours[location].x;
        int y2 = neighbours[location].y;
        if (tiles[y2][x2].tiletype == TileType::Ocean) {
            fish.turn = fish.turn + 1;
            fish.hasMoved = true;
            setOcean(x, y);
            if (fish.turn == fishBreed) {
                fish.turn = 0;
                setFish(x, y);
            }
            setTile(x2, y2, fish);
            break;
        }
        if (!fish.hasMoved) {
            location = (location + 1) % 4;
        }
    }
}

/**
 * @brief Move the shark creature at the given coordinates.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 */
void moveShark(int x, int y) {
    Tile shark = getTile(x, y);
    Tile neighbours[4];
    setNeighbours(x, y, neighbours);
    long location;
    lrand48_r(&DecisionData[omp_get_thread_num()], &location);
    location = location % 4;
    shark.energy--;
    shark.turn++;
    int x2, y2;
    bool foundFish = false; // variable to track if fish was found
    
    for (int i = 0; i < 4; i++) {
        x2 = neighbours[location].x;
        y2 = neighbours[location].y;
        if (tiles[y2][x2].tiletype == TileType::Fish) { // Check for fish
            shark.hasMoved = true;
            shark.energy += energyGain;
            setOcean(x, y);
            foundFish = true; // Set foundFish to true
            break;
        }
        if (!shark.hasMoved) {
            location = (location + 1) % 4;
        }
    }

    if (!shark.hasMoved && !foundFish) { // Check if fish was not found
        for (int i = 0; i < 4; ++i) {
            x2 = neighbours[location].x;
            y2 = neighbours[location].y;
            if (tiles[y2][x2].tiletype == TileType::Ocean) { // Check for ocean
                shark.hasMoved = true;
                setOcean(x, y);
                break;
            }
            if (!shark.hasMoved) {
                location = (location + 1) % 4;
            }
        }
    }

    if(shark.hasMoved) {
      if(shark.turn >= sharkBreed) {
        shark.turn = 0;
        setShark(x, y);
      }

      if(shark.energy < 0) {
        setOcean(x2, y2);
      } else {
        setTile(x2, y2, shark);
      }
    } else {
        // Sharks still starve if they don't move
        if(shark.energy < 0) {
          setOcean(x, y);
        } else {
          setTile(x2, y2, shark);
        }
    }
}

/**
 * @brief Poll and handle events in the window.
 */
void pollEvents() {
  sf::Event event;
  while (window.pollEvent(event))
  {
      if (event.type == sf::Event::Closed)
          window.close();
  }
}

/**
 * @brief Draw the current state of the simulation.
 */
void draw() {
  window.clear(sf::Color::Black);
  for(int y = 0; y < xdim; ++y) {
    for(int x = 0; x < ydim; ++x) {
      window.draw(display[y][x]);
    }
  }
  window.display();
}

/**
 * @brief Initialize the world by setting up tiles, creatures, and the display.
 */
void initializeWorld() {
  srand48(0);
  omp_set_num_threads(numThreads);
  for (int y = 0; y < xdim; ++y) {
    for (int x = 0; x < ydim; ++x) {
      display[y][x].setSize(sf::Vector2f(tileXSize, tileYSize));
      display[y][x].setPosition(x * tileXSize, y * tileYSize);
      setOcean(x, y);
      int id = y * 1 - +x;
      if (id % 18 == 0) {
        setShark(x, y);
      } else if (id % 10 == 0) {
        setFish(x, y);
      }
      display[y][x].setFillColor(getColor(x, y));
    }
  }
  draw();
}

/**
 * @brief Move creatures (Fish and Shark) in the simulation.
 */
void moveCreatures() {
#pragma omp parallel for collapse(2)
    for (int y = 0; y < xdim; ++y) {
        for (int x = 0; x < ydim; ++x) {
            if(tiles[y][x].tiletype == TileType::Fish && !hasMoved(x, y)) {
                moveFish(x, y);
            } 
            else if(tiles[y][x].tiletype == TileType::Shark && !hasMoved(x, y)) {
                moveShark(x, y);
            }
            display[y][x].setFillColor(getColor(x, y));
        }
    }
}

/**
 * @brief Run the simulation with varying thread counts.
 */
void runSimulation() {
    int threadCounts[] = {1, 2, 4, 8}; // Define the thread counts to test
    int numTests = 4; // Number of thread counts to test

    for (int i = 0; i < numTests; ++i) {
        numThreads = threadCounts[i]; // Set the number of threads for this test

        initializeWorld();
        int output = 0;
        while (window.isOpen() && output < maxDuration) {
            pollEvents();
            auto start = std::chrono::steady_clock::now();
            moveCreatures();

            // Reset hasMoved flag for all tiles
            #pragma omp parallel for collapse(2)
            for (int y = 0; y < xdim; ++y) {
                for (int x = 0; x < ydim; ++x) {
                    tiles[x][y].hasMoved = false;
                }
            }

            auto end = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            
            draw(); // Draw the updated world
            printf("Thread Count: %d, Output Number: %d, Duration: %ld\n", numThreads, output, duration);
            durations[output] = duration;
            output++;
        }
    }
}

/**
 * @brief Main function to run the simulation.
 * @return Exit code.
 */
int main()
{
    runSimulation();
    return 0;
}
