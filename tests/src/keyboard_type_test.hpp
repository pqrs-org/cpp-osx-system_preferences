#include <boost/ut.hpp>
#include <pqrs/osx/system_preferences.hpp>
#include <unordered_set>

void run_keyboard_type_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "keyboard_type"_test = [] {
    using keyboard_type_key = pqrs::osx::system_preferences::keyboard_type_key;

    {
      pqrs::hid::vendor_id::value_t vendor_id(1);
      pqrs::hid::product_id::value_t product_id(2);
      pqrs::hid::country_code::value_t country_code(3);

      keyboard_type_key t1(vendor_id,
                           product_id,
                           country_code);

      expect(t1.get_vendor_id() == vendor_id);
      expect(t1.get_product_id() == product_id);
      expect(t1.get_country_code() == country_code);

      keyboard_type_key t2;
      t2.set_vendor_id(vendor_id);
      t2.set_product_id(product_id);
      t2.set_country_code(country_code);

      // operator==

      expect(t1 == t2);

      expect(t1 != keyboard_type_key(pqrs::hid::vendor_id::value_t(0),
                                     product_id,
                                     country_code));
      expect(t1 != keyboard_type_key(vendor_id,
                                     pqrs::hid::product_id::value_t(0),
                                     country_code));
      expect(t1 != keyboard_type_key(vendor_id,
                                     product_id,
                                     pqrs::hid::country_code::value_t(0)));
    }

    // operator<

    {
      keyboard_type_key v1(pqrs::hid::vendor_id::value_t(1),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(3));
      keyboard_type_key v2(pqrs::hid::vendor_id::value_t(3),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(1));
      expect(v1 < v2);
    }
    {
      keyboard_type_key v1(pqrs::hid::vendor_id::value_t(1),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(3));
      keyboard_type_key v2(pqrs::hid::vendor_id::value_t(1),
                           pqrs::hid::product_id::value_t(3),
                           pqrs::hid::country_code::value_t(2));
      expect(v1 < v2);
    }
    {
      keyboard_type_key v1(pqrs::hid::vendor_id::value_t(1),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(3));
      keyboard_type_key v2(pqrs::hid::vendor_id::value_t(1),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(4));
      expect(v1 < v2);
    }
    {
      keyboard_type_key v1(pqrs::hid::vendor_id::value_t(1),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(3));
      keyboard_type_key v2(pqrs::hid::vendor_id::value_t(1),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(3));
      expect(!(v1 < v2));
    }
    {
      keyboard_type_key v1(pqrs::hid::vendor_id::value_t(3),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(1));
      keyboard_type_key v2(pqrs::hid::vendor_id::value_t(1),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(3));
      expect(!(v1 < v2));
    }
    {
      keyboard_type_key v1(pqrs::hid::vendor_id::value_t(3),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(1));
      keyboard_type_key v2(pqrs::hid::vendor_id::value_t(3),
                           pqrs::hid::product_id::value_t(1),
                           pqrs::hid::country_code::value_t(2));
      expect(!(v1 < v2));
    }
    {
      keyboard_type_key v1(pqrs::hid::vendor_id::value_t(3),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(1));
      keyboard_type_key v2(pqrs::hid::vendor_id::value_t(3),
                           pqrs::hid::product_id::value_t(2),
                           pqrs::hid::country_code::value_t(0));
      expect(!(v1 < v2));
    }

    // hash

    {
      std::unordered_set<pqrs::osx::system_preferences::keyboard_type_key> set;
      set.insert(keyboard_type_key(pqrs::hid::vendor_id::value_t(1),
                                   pqrs::hid::product_id::value_t(2),
                                   pqrs::hid::country_code::value_t(3)));
    }
  };
}
