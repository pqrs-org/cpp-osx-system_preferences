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
  for (const auto& [k, t] : properties.get_keyboard_types()) {
    std::cout << "  vendor_id: " << k.get_vendor_id() << std::endl;
    std::cout << "  product_id: " << k.get_product_id() << std::endl;
    std::cout << "  country_code: " << k.get_country_code() << std::endl;
    std::cout << "  keyboard_type: " << t << std::endl;
    std::cout << std::endl;
  }

#if 0
  pqrs::osx::system_preferences::user_defaults::set_keyboard_type(pqrs::hid::product_id::value_t(10203),
                                                                  pqrs::hid::vendor_id::value_t(5824),
                                                                  pqrs::hid::country_code::value_t(0),
                                                                  pqrs::osx::iokit_keyboard_type::ansi);
#endif

  return 0;
}
