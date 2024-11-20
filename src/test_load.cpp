#include <catch2/catch_test_macros.hpp>

#include "loader.hpp"

TEST_CASE( "Loader can load the example map", "[loader]" ) {

    std::vector<int8_t> map = load_map( "data/sample_map.json" );

    // this is the required size specified in the project assignment (32 x 32 == 1024)
    REQUIRE( map.size() == MAP_SIZE );

    print_map( map );

}