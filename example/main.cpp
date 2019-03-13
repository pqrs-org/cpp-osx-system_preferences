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

  std::cout << "keyboard_types:" << std::endl;
  for (const auto& t : properties.get_keyboard_types()) {
    std::cout << "  vendor_id: " << t.get_vendor_id() << std::endl;
    std::cout << "  product_id: " << t.get_product_id() << std::endl;
    std::cout << "  country_code: " << t.get_country_code() << std::endl;
    std::cout << "  keyboard_type: " << t.get_keyboard_type() << std::endl;
    std::cout << std::endl;
  }

  return 0;
}
