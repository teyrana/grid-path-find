#include <catch2/catch_test_macros.hpp>

#include "loader.hpp"

TEST_CASE( "Loader can load the example map", "[loader]" ) {

    std::vector<int8_t> map = load_map( "data/sample_map.json" );

    // this is the required size specified in the project assignment (32 x 32 == 1024)
    REQUIRE( map.size() == MAP_SIZE );

    // perform some rough spot checks -- it's not enough to prove correct, but it's 
    // a quick sanity check to make sure the loader is actually changing values
    REQUIRE( map[0] == -1 );
    REQUIRE( map[23] == -1 );
    REQUIRE( map[32] == -1 );
    REQUIRE( map[127] == 3 );
    REQUIRE( map[128] == 3);
    REQUIRE( map[129] == 3 );
    REQUIRE( map[510] == 3 );
    REQUIRE( map[511] == -1 );
    REQUIRE( map[512] == -1 );

    // for visualization
    // print_map( map );
}