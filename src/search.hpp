#pragma once

#include <cstdint>
#include <string>
#include <vector>


using path_t = std::vector<int>;

float distance( int a, int b );

// find the (first) index to search from
int map_find_start( const std::vector<int8_t> map );
    
// find the (first) goal to search to
int map_find_goal( const std::vector<int8_t> map );

// implementation reference: https://en.wikipedia.org/wiki/A*_search_algorithm
path_t search_map_a_star( const std::vector<int8_t> & map, int start, int goal );

void print_path_steps( const path_t & path );

void print_path_map( const path_t & path );

