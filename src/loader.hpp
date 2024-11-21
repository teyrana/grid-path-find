#pragma once

#include <cstdint>
#include <string>
#include <vector>

constexpr int32_t MAP_DIMENSION = 32;
constexpr int32_t MAP_SIZE = MAP_DIMENSION * MAP_DIMENSION;

std::vector<int8_t> load_map( const std::string & filename );

void print_map( const std::vector<int8_t> & map );