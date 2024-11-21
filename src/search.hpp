#pragma once

#include <cstdint>
#include <string>
#include <vector>


using path_t = std::vector<int>;

float distance( int a, int b );

// implementation reference: https://en.wikipedia.org/wiki/A*_search_algorithm
path_t search_map_a_star( const std::vector<int8_t> & map, int start, int goal );

void print_path( const path_t & path );


