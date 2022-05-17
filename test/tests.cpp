#include <myproject/myproject.h>

#include <catch2/catch.hpp>
#include <stdexcept>

TEST_CASE("Foo returns the result of an operation <op> performed on <a> and <b>", "[foo]")
{
    REQUIRE_THROWS_AS(myproject::foo(1, 1, '\0'), std::invalid_argument);
    REQUIRE(myproject::foo(1337.F, 1.F, '*') == 1337.F);  // NOLINT: magic number
    REQUIRE(myproject::foo(21, 21, '+') == 42);
}
