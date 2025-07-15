#include <boost/ut.hpp>
#include <pqrs/osx/system_preferences.hpp>
#include <unordered_set>

void run_properties_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "properties"_test = [] {
    {
      pqrs::osx::system_preferences::properties p1;
      p1.set_use_fkeys_as_standard_function_keys(true);
      p1.set_scroll_direction_is_natural(false);

      // operator==

      auto p2 = p1;
      expect(p1 == p2);

      p2 = p1;
      p2.set_use_fkeys_as_standard_function_keys(false);
      expect(p1 != p2);

      p2 = p1;
      p2.set_scroll_direction_is_natural(true);
      expect(p1 != p2);
    }

    // hash

    {
      std::unordered_set<pqrs::osx::system_preferences::properties> set;
      set.insert(pqrs::osx::system_preferences::properties());
    }
  };
}
