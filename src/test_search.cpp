#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
using Catch::Approx;

#include "search.hpp"

TEST_CASE( "Distance function correctly calculates distance", "[distance]" ) {
    // note: DIM is set === 32

    REQUIRE( distance(1, 2) == Approx(1) );
    REQUIRE( distance(1, 9) == Approx(8) );
    
    REQUIRE( distance(5, 2*32+5) == Approx(2) );
    REQUIRE( distance(8, 6*32+8) == Approx(6) );

    // a 3-4-5 triangle, just to make the math easier
    REQUIRE( distance( 1, 4 + 4*32) == Approx(5) );

    // check wrapping behavior
    REQUIRE( distance( 0, 31) == Approx(31) );
    REQUIRE( distance( 0, 32) == Approx(1) );

    REQUIRE( distance( 32, 2*32 + 2) < 9.0 );
}


TEST_CASE( "Loader can perform a simple search", "[search]" ) {

    std::vector<int8_t> map(1024);

    map[0]  = 0; map[1] = -1; 
    map[32] = -1; map[33] = -1; 
    map[64] = -1; map[65] = 8;

    auto path = search_map_a_star( map, 0, 65 );

    REQUIRE( 1 < path.size() );

    print_path( path );

}