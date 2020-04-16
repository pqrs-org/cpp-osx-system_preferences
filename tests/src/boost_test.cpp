#include <catch2/catch.hpp>

#include <pqrs/osx/system_preferences/extra/boost.hpp>

TEST_CASE("boost") {
  {
    pqrs::osx::system_preferences::keyboard_type_key v(
        pqrs::hid::vendor_id::value_t(1),
        pqrs::hid::product_id::value_t(2),
        pqrs::hid::country_code::value_t(3));
    REQUIRE(std::hash<pqrs::osx::system_preferences::keyboard_type_key>{}(v) ==
            pqrs::osx::system_preferences::hash_value(v));
  }
}
