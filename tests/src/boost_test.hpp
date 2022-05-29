#include <boost/ut.hpp>
#include <pqrs/osx/system_preferences/extra/boost.hpp>

void run_boost_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "boost"_test = [] {
    {
      pqrs::osx::system_preferences::keyboard_type_key v(
          pqrs::hid::vendor_id::value_t(1),
          pqrs::hid::product_id::value_t(2),
          pqrs::hid::country_code::value_t(3));
      expect(std::hash<pqrs::osx::system_preferences::keyboard_type_key>{}(v) ==
             pqrs::osx::system_preferences::hash_value(v));
    }
  };
}
