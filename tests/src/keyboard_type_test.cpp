#include <catch2/catch.hpp>

#include <pqrs/osx/system_preferences.hpp>

TEST_CASE("keyboard_type") {
  using keyboard_type = pqrs::osx::system_preferences::keyboard_type;

  {
    pqrs::osx::iokit_hid_vendor_id iokit_hid_vendor_id(1);
    pqrs::osx::iokit_hid_product_id iokit_hid_product_id(2);
    pqrs::osx::iokit_hid_country_code iokit_hid_country_code(3);
    pqrs::osx::iokit_keyboard_type iokit_keyboard_type(4);

    keyboard_type t1(iokit_hid_vendor_id,
                     iokit_hid_product_id,
                     iokit_hid_country_code,
                     iokit_keyboard_type);

    REQUIRE(t1.get_vendor_id() == iokit_hid_vendor_id);
    REQUIRE(t1.get_product_id() == iokit_hid_product_id);
    REQUIRE(t1.get_country_code() == iokit_hid_country_code);
    REQUIRE(t1.get_keyboard_type() == iokit_keyboard_type);

    keyboard_type t2;
    t2.set_vendor_id(iokit_hid_vendor_id);
    t2.set_product_id(iokit_hid_product_id);
    t2.set_country_code(iokit_hid_country_code);
    t2.set_keyboard_type(iokit_keyboard_type);

    // operator==

    REQUIRE(t1 == t2);

    REQUIRE(t1 != keyboard_type(pqrs::osx::iokit_hid_vendor_id(0),
                                iokit_hid_product_id,
                                iokit_hid_country_code,
                                iokit_keyboard_type));
    REQUIRE(t1 != keyboard_type(iokit_hid_vendor_id,
                                pqrs::osx::iokit_hid_product_id(0),
                                iokit_hid_country_code,
                                iokit_keyboard_type));
    REQUIRE(t1 != keyboard_type(iokit_hid_vendor_id,
                                iokit_hid_product_id,
                                pqrs::osx::iokit_hid_country_code(0),
                                iokit_keyboard_type));
    REQUIRE(t1 != keyboard_type(iokit_hid_vendor_id,
                                iokit_hid_product_id,
                                iokit_hid_country_code,
                                pqrs::osx::iokit_keyboard_type(0)));
  }

  // make_keyboard_type_string

  {
    keyboard_type t;

    t.set_keyboard_type(pqrs::osx::iokit_keyboard_type(40));
    REQUIRE(t.make_keyboard_type_string() == "ansi");

    t.set_keyboard_type(pqrs::osx::iokit_keyboard_type(41));
    REQUIRE(t.make_keyboard_type_string() == "iso");

    t.set_keyboard_type(pqrs::osx::iokit_keyboard_type(42));
    REQUIRE(t.make_keyboard_type_string() == "jis");
  }
}
