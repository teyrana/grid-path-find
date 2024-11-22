#include <iostream>

#include "loader.hpp"
#include "search.hpp"

int main( int argc, char* argv[] ) {

    if( argc < 2 ) {
        std::cerr << "Usage: " << argv[0] << " <map_file>\n";
        return 1;
    }
    const auto map = load_map( argv[1] );

    std::cout << "Print Map: \n====================\n";
    print_map( map );
    std::cout << std::endl;

    const int start_index = map_find_start( map );
    const int goal_index = map_find_goal( map );
    std::cout << "    start_point: " << start_index << '\n';
    std::cout << "    goal_point:  " << goal_index << '\n';

    const auto path = search_map_a_star( map, start_index, goal_index );

    // std::cout << "Print Path: \n====================\n";
    // print_path_steps( path );

    std::cout << "Print Path: \n====================\n";
    print_path_map( map, start_index, goal_index, path );    
    std::cout << std::endl;

    return 0;
}
