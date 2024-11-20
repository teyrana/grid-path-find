#include <catch2/catch_test_macros.hpp>

#include "search.hpp"

TEST_CASE( "Loader can perform a simple search", "[3x3 grid]" ) {

    std::vector<int8_t> map = {
         0, -1, -1,
        -1, -1, -1,
        -1, -1,  8
    };

    auto path = search_map_a_star( map, {0,0}, {2,2} );

    REQUIRE( 1 < path.size() );

}