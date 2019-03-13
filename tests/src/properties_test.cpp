#include <catch2/catch.hpp>

#include <pqrs/osx/system_preferences.hpp>

TEST_CASE("properties") {
  {
    std::unordered_set<pqrs::osx::system_preferences::keyboard_type> keyboard_types{
        pqrs::osx::system_preferences::keyboard_type(
            pqrs::osx::iokit_hid_vendor_id(1),
            pqrs::osx::iokit_hid_product_id(2),
            pqrs::osx::iokit_hid_country_code(3),
            pqrs::osx::iokit_keyboard_type(4)),
    };

    pqrs::osx::system_preferences::properties p1;
    p1.set_use_fkeys_as_standard_function_keys(true);
    p1.set_scroll_direction_is_natural(false);
    p1.set_keyboard_types(keyboard_types);

    // operator==

    auto p2 = p1;
    REQUIRE(p1 == p2);

    p2 = p1;
    p2.set_use_fkeys_as_standard_function_keys(false);
    REQUIRE(p1 != p2);

    p2 = p1;
    p2.set_scroll_direction_is_natural(true);
    REQUIRE(p1 != p2);

    p2 = p1;
    p2.set_keyboard_types(std::unordered_set<pqrs::osx::system_preferences::keyboard_type>());
    REQUIRE(p1 != p2);
  }
}
