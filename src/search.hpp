#pragma once

#include <cstdint>
#include <string>
#include <vector>

/// @brief a list of indices representing a found path
/// The indices just index into the raw map. (i.e. not coordinates)
using path_t = std::vector<int>;

/// @brief  calculates the euclidean distance between two points
///
/// Note: this function operates on vector indices, NOT coordinates.
///
/// @param a index of the first point
/// @param b index of the second point
/// @return distance between the two points, as a float
float distance( int a, int b );

/// @brief find the (first) index to search from
int map_find_start( const std::vector<int8_t> map );
    
/// @brief find the (first) goal to search to
int map_find_goal( const std::vector<int8_t> map );

/// @brief search the map for a path from start to goal
///
/// note: implementations the A* algorithm: https://en.wikipedia.org/wiki/A*_search_algorithm
///
/// @param map the map to search in
/// @param start the index to start from
/// @param goal the index to search to
/// @return a path from start to goal
path_t search_map_a_star( const std::vector<int8_t> & map, int start, int goal );

/// @brief  print the path steps to stdout, simply as a list of indices and their translated coordinates
/// @param path 
void print_path_steps( const path_t & path );

void print_path_map( const std::vector<int8_t> & map, int start, int goal, const path_t & path );

