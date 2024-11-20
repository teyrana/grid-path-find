// stdlib includes
#include <cmath>
#include <fstream>
#include <iostream>

// extern includes
#include <nlohmann/json.hpp>

// project includes
#include "loader.hpp"

using nlohmann::json;

std::vector<int8_t> load_map( const std::string & filename ) {

    std::ifstream infile( filename);

    if( ! infile.is_open() ) {
        throw std::runtime_error( "Could not open file" );
    }

    auto data = json::parse(infile);


    // check if the map has a layers array:
    if( (!data.contains("layers")) || (data["layers"].size() < 1) ){
        std::cerr << "No data layers found in map file" << std::endl;
        return {}; // Return an empty vector
    }
    if( ! data["layers"][0].contains("data") ){
        std::cerr << "No data found in first layer" << std::endl;
        return {}; // Return an empty vector
    }

    // get the data array
    std::vector<float> raw_grid = data["layers"][0]["data"].get<std::vector<float>>();

    std::vector<int8_t> grid;
    grid.reserve(raw_grid.size());
    grid.resize(raw_grid.size());

    for (int i = 0; i < raw_grid.size(); i++){
        constexpr float epsilon = 0.00001f;
        const float raw_value = raw_grid[i];

        // it turns out the json grid contains fractional (float) values, 
        // so we have to interpret the values somehow.  
        // ==> we choose a simple floor funcition:
        grid[i] = static_cast<int8_t>(floor(raw_value));
    }

    return grid;
}


void print_map( const std::vector<int8_t> & map ){
    // print map to stdout

    std::cout << "Printing map" << std::endl;
    std::cout << "====== ====== ====== ======\n";

    for( int i = 0; i < MAP_DIMENSION; i++ ) {
        for( int j = 0; j < MAP_DIMENSION; j++ ) {
            const int32_t value = static_cast<int>( map[i*32+j] );
            std::cout << ' ';

            // raw values, for debugging
            // std::cout << value;

            // better to visualize the terrain & channels
            if (3 == value){
                std::cout << 'E';
            } else if (0 == value){
                std::cout << 'O';
            } else if (8 == value){
                std::cout << 'X';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    std::cout << "====== ====== ====== ======\n" << std::endl;

}