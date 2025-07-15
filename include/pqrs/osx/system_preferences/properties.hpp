#pragma once

// (C) Copyright Takayama Fumihiko 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See https://www.boost.org/LICENSE_1_0.txt)

#include "system_preferences.hpp"
#include <map>
#include <pqrs/cf/string.hpp>
#include <pqrs/hash.hpp>
#include <pqrs/hid.hpp>

namespace pqrs {
namespace osx {
namespace system_preferences {
class properties final {
public:
  properties(void) : use_fkeys_as_standard_function_keys_(false),
                     scroll_direction_is_natural_(true) {
  }

  bool get_use_fkeys_as_standard_function_keys(void) const {
    return use_fkeys_as_standard_function_keys_;
  }

  void set_use_fkeys_as_standard_function_keys(bool value) {
    use_fkeys_as_standard_function_keys_ = value;
  }

  bool get_scroll_direction_is_natural(void) const {
    return scroll_direction_is_natural_;
  }

  void set_scroll_direction_is_natural(bool value) {
    scroll_direction_is_natural_ = value;
  }

  void update(void) {
    // use_fkeys_as_standard_function_keys_

    if (auto value = find_app_bool_property(CFSTR("com.apple.keyboard.fnState"),
                                            CFSTR("Apple Global Domain"))) {
      use_fkeys_as_standard_function_keys_ = *value;
    }

    // scroll_direction_is_natural_

    if (auto value = find_app_bool_property(CFSTR("com.apple.swipescrolldirection"),
                                            CFSTR("Apple Global Domain"))) {
      scroll_direction_is_natural_ = *value;
    }
  }

  bool operator==(const properties& other) const {
    return use_fkeys_as_standard_function_keys_ == other.use_fkeys_as_standard_function_keys_ &&
           scroll_direction_is_natural_ == other.scroll_direction_is_natural_;
  }

  bool operator!=(const properties& other) const {
    return !(*this == other);
  }

private:
  bool use_fkeys_as_standard_function_keys_;
  bool scroll_direction_is_natural_;
};
} // namespace system_preferences
} // namespace osx
} // namespace pqrs

namespace std {
template <>
struct hash<pqrs::osx::system_preferences::properties> final {
  std::size_t operator()(const pqrs::osx::system_preferences::properties& value) const {
    std::size_t h = 0;

    pqrs::hash::combine(h, value.get_use_fkeys_as_standard_function_keys());
    pqrs::hash::combine(h, value.get_scroll_direction_is_natural());

    return h;
  }
};
} // namespace std
