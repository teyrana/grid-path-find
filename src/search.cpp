// stdlib includes
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>

// extern includes
#include <nlohmann/json.hpp>

// project includes
#include "loader.hpp"
#include "search.hpp"

using nlohmann::json;

// local / utility functions

class Step {
public:
    int index;
    float cost;
    int parent; // index of parent // if parent == index, we have reached the start
};

std::array<int, 4> neighbors = {-1, 1, -MAP_DIMENSION, MAP_DIMENSION};


// define a custom comparator for the priority queue to use 'class Step'
struct compare_costs {
    bool operator()(const Step& a, const Step& b){
        return a.cost > b.cost;
    }
};

// external functions

// calculates the euclidean distance between two points
float distance( int a, int b ){
    // construct coordinate pairs from each_index
    const int ai = a % MAP_DIMENSION;
    const int aj = a / MAP_DIMENSION;
    const int bi = b % MAP_DIMENSION; 
    const int bj = b / MAP_DIMENSION;

    return sqrt( pow(ai - bi, 2) + pow(aj - bj, 2) );
}

int map_find_start( const std::vector<int8_t> map ){
    for( int i = 0; i < map.size(); i++ ){
        if( map[i] == MAP_VALUE_START ){
            return i;
        }
    }

    return -1;
}

int map_find_goal( const std::vector<int8_t> map ){
    for( int i = 0; i < map.size(); i++ ){
        if( map[i] == MAP_VALUE_GOAL ){
            return i;
        }
    }

    return -1;
}

path_t search_map_a_star( const std::vector<int8_t>& map, int start, int goal ){
    const int dim = sqrt(map.size());

    // enforce that the map is square, and 32x32
    assert( MAP_SIZE == map.size() );

    // std::vector<char> visited( MAP_SIZE, 0 );
    std::vector<int> parents( MAP_SIZE, -1 );

    std::priority_queue<
        Step, 
        std::vector<Step>, 
        struct compare_costs
    > next;
    
    next.emplace( start, distance(start,goal), start );

    while( 0 < next.size() ){

        const Step current = next.top();
        next.pop();

        std::cout << "@ step: " << current.index << ",   cost: " << current.cost << '\n';

        // mark index as visited, and path backwards
        parents[current.index] = current.parent;

        // check if the next step is the goal
        if(current.cost < 1){
            // sucess condition -- build the return path
            path_t path;

            std::cout << "goal found! -- constructing path\n";

            int path_index = current.index;
            path.push_back(path_index); // push the final coordinate

            while( parents[path_index] != path_index ){
                std::cerr << "    +> path @ " << path_index << '\n';
                path_index = parents[path_index];
                if (path_index < 0){
                    std::cerr << "    invalid path index!! BUG!!\n";
                    break;
                }
                path.push_back(path_index);
            }

            // Reverse the vector in-place, so that it goes start -> end

            std::reverse(path.begin(), path.end());

            return path;
        }

        // add the current (next) step to the path and remove it from the open list
        for( auto n : neighbors ){
            const int next_index = current.index + n;

            // check that the next step is within map bounds
            if( next_index < 0 || MAP_SIZE <= next_index ){
                continue;
            }

            // if this neighbor has already been visited, skip
            if( 0 < parents[next_index] ){
                continue;
            }

            // if this terrain is not passable, skip
            if( map[next_index] == MAP_VALUE_HIGH ){
                continue;
            }

            const float d = distance(next_index, goal);

            std::cout << "    +> push next @ " << next_index << "  cost: " << d << '\n';
            next.emplace(next_index, d, current.index);
        }

    }

    // error path
    return {};
}

void print_path_steps( const path_t& path ){
    // print map to stdout

    std::cout << "Printing Path:" << std::endl;
    std::cout << "====== ====== ====== ======\n";

    int i = 0;
    for( auto step : path ){
        const int col = step % MAP_DIMENSION;
        const int row = step / MAP_DIMENSION;
        std::cout << "    #" << i << " [" << step << "]: (" << col << ", " << row << ")\n";
        i++;
    }

    std::cout << "\n" << std::endl;
}

void print_path_map( const path_t& path ){
    // print map to stdout

    std::vector<int8_t> to_print( MAP_SIZE, -1 );

    int i = 0;
    for( auto step : path ){
        to_print[step] = 1;
        i++;
    }

    print_map( to_print );

    std::cout << "\n" << std::endl;
}
