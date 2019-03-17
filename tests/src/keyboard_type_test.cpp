#include <catch2/catch.hpp>

#include <pqrs/osx/system_preferences.hpp>
#include <unordered_set>

TEST_CASE("keyboard_type") {
  using keyboard_type_key = pqrs::osx::system_preferences::keyboard_type_key;

  {
    pqrs::osx::iokit_hid_vendor_id iokit_hid_vendor_id(1);
    pqrs::osx::iokit_hid_product_id iokit_hid_product_id(2);
    pqrs::osx::iokit_hid_country_code iokit_hid_country_code(3);

    keyboard_type_key t1(iokit_hid_vendor_id,
                         iokit_hid_product_id,
                         iokit_hid_country_code);

    REQUIRE(t1.get_vendor_id() == iokit_hid_vendor_id);
    REQUIRE(t1.get_product_id() == iokit_hid_product_id);
    REQUIRE(t1.get_country_code() == iokit_hid_country_code);

    keyboard_type_key t2;
    t2.set_vendor_id(iokit_hid_vendor_id);
    t2.set_product_id(iokit_hid_product_id);
    t2.set_country_code(iokit_hid_country_code);

    // operator==

    REQUIRE(t1 == t2);

    REQUIRE(t1 != keyboard_type_key(pqrs::osx::iokit_hid_vendor_id(0),
                                    iokit_hid_product_id,
                                    iokit_hid_country_code));
    REQUIRE(t1 != keyboard_type_key(iokit_hid_vendor_id,
                                    pqrs::osx::iokit_hid_product_id(0),
                                    iokit_hid_country_code));
    REQUIRE(t1 != keyboard_type_key(iokit_hid_vendor_id,
                                    iokit_hid_product_id,
                                    pqrs::osx::iokit_hid_country_code(0)));
  }

  // operator<

  {
    keyboard_type_key v1(pqrs::osx::iokit_hid_vendor_id(1),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(3));
    keyboard_type_key v2(pqrs::osx::iokit_hid_vendor_id(3),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(1));
    REQUIRE(v1 < v2);
  }
  {
    keyboard_type_key v1(pqrs::osx::iokit_hid_vendor_id(1),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(3));
    keyboard_type_key v2(pqrs::osx::iokit_hid_vendor_id(1),
                         pqrs::osx::iokit_hid_product_id(3),
                         pqrs::osx::iokit_hid_country_code(2));
    REQUIRE(v1 < v2);
  }
  {
    keyboard_type_key v1(pqrs::osx::iokit_hid_vendor_id(1),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(3));
    keyboard_type_key v2(pqrs::osx::iokit_hid_vendor_id(1),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(4));
    REQUIRE(v1 < v2);
  }
  {
    keyboard_type_key v1(pqrs::osx::iokit_hid_vendor_id(1),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(3));
    keyboard_type_key v2(pqrs::osx::iokit_hid_vendor_id(1),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(3));
    REQUIRE(!(v1 < v2));
  }
  {
    keyboard_type_key v1(pqrs::osx::iokit_hid_vendor_id(3),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(1));
    keyboard_type_key v2(pqrs::osx::iokit_hid_vendor_id(1),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(3));
    REQUIRE(!(v1 < v2));
  }
  {
    keyboard_type_key v1(pqrs::osx::iokit_hid_vendor_id(3),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(1));
    keyboard_type_key v2(pqrs::osx::iokit_hid_vendor_id(3),
                         pqrs::osx::iokit_hid_product_id(1),
                         pqrs::osx::iokit_hid_country_code(2));
    REQUIRE(!(v1 < v2));
  }
  {
    keyboard_type_key v1(pqrs::osx::iokit_hid_vendor_id(3),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(1));
    keyboard_type_key v2(pqrs::osx::iokit_hid_vendor_id(3),
                         pqrs::osx::iokit_hid_product_id(2),
                         pqrs::osx::iokit_hid_country_code(0));
    REQUIRE(!(v1 < v2));
  }

  // hash

  {
    std::unordered_set<pqrs::osx::system_preferences::keyboard_type_key> set;
    set.insert(keyboard_type_key(pqrs::osx::iokit_hid_vendor_id(1),
                                 pqrs::osx::iokit_hid_product_id(2),
                                 pqrs::osx::iokit_hid_country_code(3)));
  }
}
