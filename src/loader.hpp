#pragma once

#include <cstdint>
#include <string>
#include <vector>

constexpr int32_t MAP_DIMENSION = 32;
constexpr int32_t MAP_SIZE = MAP_DIMENSION * MAP_DIMENSION;

constexpr int8_t MAP_VALUE_PASSABLE = -1;
constexpr int8_t MAP_VALUE_HIGH = 3;
constexpr int8_t MAP_VALUE_START = 0;
constexpr int8_t MAP_VALUE_GOAL = 8;

/// @brief Load a json map from the given filename 
///
/// Note: this function just loads the data array. 
///       will match the output of `jq .layers[0].data`
///
/// @param filename map to load
/// @return raw data of _just_ the cell values
std::vector<int8_t> load_map( const std::string & filename );

void print_map( const std::vector<int8_t> & map );