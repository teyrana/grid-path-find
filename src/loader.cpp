// stdlib includes
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
    std::vector<int8_t> grid = data["layers"][0]["data"].get<std::vector<int8_t>>();

    // grid.reserve( 1024 );
    // grid.resize(1024);


    // while( !file.eof() ) {
    //     uint8_t byte;
    //     file.read( reinterpret_cast<char*>(&byte), 1 );
    //     map.push_back( byte );
    // }

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