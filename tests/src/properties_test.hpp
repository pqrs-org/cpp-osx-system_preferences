#include <boost/ut.hpp>
#include <pqrs/osx/system_preferences.hpp>
#include <unordered_set>

void run_properties_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "properties"_test = [] {
    {
      using keyboard_types_t = std::map<pqrs::osx::system_preferences::keyboard_type_key,
                                        pqrs::osx::iokit_keyboard_type::value_t>;

      pqrs::osx::system_preferences::keyboard_type_key keyboard_type_key(
          pqrs::hid::vendor_id::value_t(1),
          pqrs::hid::product_id::value_t(2),
          pqrs::hid::country_code::value_t(3));
      keyboard_types_t keyboard_types;
      keyboard_types[keyboard_type_key] = pqrs::osx::iokit_keyboard_type::value_t(4);

      pqrs::osx::system_preferences::properties p1;
      p1.set_use_fkeys_as_standard_function_keys(true);
      p1.set_scroll_direction_is_natural(false);
      p1.set_keyboard_types(keyboard_types);

      // operator==

      auto p2 = p1;
      expect(p1 == p2);

      p2 = p1;
      p2.set_use_fkeys_as_standard_function_keys(false);
      expect(p1 != p2);

      p2 = p1;
      p2.set_scroll_direction_is_natural(true);
      expect(p1 != p2);

      p2 = p1;
      p2.set_keyboard_types(keyboard_types_t());
      expect(p1 != p2);
    }

    // hash

    {
      std::unordered_set<pqrs::osx::system_preferences::properties> set;
      set.insert(pqrs::osx::system_preferences::properties());
    }
  };
}
