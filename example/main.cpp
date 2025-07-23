#include <iostream>
#include <pqrs/cf/dictionary.hpp>
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

  if (auto matching_dictionary = pqrs::cf::make_cf_mutable_dictionary()) {
    CFDictionarySetValue(*matching_dictionary,
                         CFSTR(kIOProviderClassKey),
                         CFSTR("IOHIDEventService"));

    if (auto dict = pqrs::cf::make_cf_mutable_dictionary()) {
      CFDictionarySetValue(*dict,
                           CFSTR("SerialNumber"),
                           CFSTR("pqrs.org:Karabiner-DriverKit-VirtualHIDKeyboard"));

      CFDictionarySetValue(*matching_dictionary,
                           CFSTR(kIOPropertyMatchKey),
                           *dict);
    }

    auto modifier_mappings = pqrs::osx::system_preferences::get_modifier_mappings(*matching_dictionary);
    std::cout << "modifier_mappings: [" << std::endl;
    for (const auto& m : modifier_mappings) {
      std::cout << "  {" << std::endl;
      std::cout << "    src_usage_page: " << m.src.get_usage_page() << std::endl;
      std::cout << "    src_usage: " << m.src.get_usage() << std::endl;
      std::cout << "    dst_usage_page: " << m.dst.get_usage_page() << std::endl;
      std::cout << "    dst_usage: " << m.dst.get_usage() << std::endl;
      std::cout << "  }," << std::endl;
    }
    std::cout << "]" << std::endl;
  }

  return 0;
}
