#include <iostream>
#include <pqrs/osx/system_preferences.hpp>
#include <string>

int main(void) {
  pqrs::osx::system_preferences::properties properties;
  properties.update();

  std::cout << "use_fkeys_as_standard_function_keys: "
            << properties.get_use_fkeys_as_standard_function_keys()
            << std::endl;

  std::cout << "scroll_direction_is_natural: "
            << properties.get_scroll_direction_is_natural()
            << std::endl;

  return 0;
}
