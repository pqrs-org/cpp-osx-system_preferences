#include <boost/ut.hpp>
#include <pqrs/osx/system_preferences/extra/nlohmann_json.hpp>

namespace {
using namespace boost::ut;
using namespace boost::ut::literals;

template <typename T>
void exception_test(const nlohmann::json& json, const std::string_view& what) {
  try {
    json.get<T>();
    expect(false);
  } catch (pqrs::json::unmarshal_error& ex) {
    expect(what == ex.what());
  } catch (...) {
    expect(false);
  }
}
} // namespace

void run_nlohmann_json_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "nlohmann_json keyboard_type"_test = [] {
    {
      pqrs::hid::vendor_id::value_t vendor_id(1);
      pqrs::hid::product_id::value_t product_id(2);
      pqrs::hid::country_code::value_t country_code(3);

      pqrs::osx::system_preferences::keyboard_type_key t1(vendor_id,
                                                          product_id,
                                                          country_code);

      nlohmann::json json = t1;
      expect(json == nlohmann::json::object({
                         {"vendor_id", vendor_id},
                         {"product_id", product_id},
                         {"country_code", country_code},
                     }));

      // from_json

      auto t2 = json.get<pqrs::osx::system_preferences::keyboard_type_key>();
      expect(t2.get_vendor_id() == vendor_id);
      expect(t2.get_product_id() == product_id);
      expect(t2.get_country_code() == country_code);

      expect(t1 == t2);
    }

    // keyboard_type errors

    exception_test<pqrs::osx::system_preferences::keyboard_type_key>(
        nlohmann::json(),
        "json must be object, but is `null`");

    exception_test<pqrs::osx::system_preferences::keyboard_type_key>(
        nlohmann::json::object({
            {"vendor_id", nlohmann::json()},
        }),
        "vendor_id error: json must be number, but is `null`");

    exception_test<pqrs::osx::system_preferences::keyboard_type_key>(
        nlohmann::json::object({
            {"product_id", nlohmann::json()},
        }),
        "product_id error: json must be number, but is `null`");

    exception_test<pqrs::osx::system_preferences::keyboard_type_key>(
        nlohmann::json::object({
            {"country_code", nlohmann::json()},
        }),
        "country_code error: json must be number, but is `null`");

    exception_test<pqrs::osx::system_preferences::keyboard_type_key>(
        nlohmann::json::object({
            {"vendor-id", nlohmann::json()},
        }),
        "unknown key: `vendor-id`");
  };

  "nlohmann_json properties"_test = [] {
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

      nlohmann::json json = p1;
      expect(json == nlohmann::json::object({
                         {"use_fkeys_as_standard_function_keys", true},
                         {"scroll_direction_is_natural", false},
                         {"keyboard_types", nlohmann::json::array({
                                                nlohmann::json::array({
                                                    nlohmann::json::object({
                                                        {"vendor_id", 1},
                                                        {"product_id", 2},
                                                        {"country_code", 3},
                                                    }),
                                                    4,
                                                }),
                                            })},
                     }));

      // from_json

      auto p2 = json.get<pqrs::osx::system_preferences::properties>();

      expect(p1 == p2);
      expect(p1.get_use_fkeys_as_standard_function_keys() == true);
      expect(p1.get_scroll_direction_is_natural() == false);
      expect(p1.get_keyboard_types() == keyboard_types);
    }

    // properties errors

    exception_test<pqrs::osx::system_preferences::properties>(
        nlohmann::json(),
        "json must be object, but is `null`");

    exception_test<pqrs::osx::system_preferences::properties>(
        nlohmann::json::object({
            {"use_fkeys_as_standard_function_keys", nlohmann::json()},
        }),
        "`use_fkeys_as_standard_function_keys` must be boolean, but is `null`");

    exception_test<pqrs::osx::system_preferences::properties>(
        nlohmann::json::object({
            {"scroll_direction_is_natural", nlohmann::json()},
        }),
        "`scroll_direction_is_natural` must be boolean, but is `null`");

    exception_test<pqrs::osx::system_preferences::properties>(
        nlohmann::json::object({
            {"keyboard_types", nlohmann::json()},
        }),
        "`keyboard_types` must be array, but is `null`");

    exception_test<pqrs::osx::system_preferences::properties>(
        nlohmann::json::object({
            {"keyboard_types", nlohmann::json::array({
                                   nlohmann::json(),
                               })},
        }),
        "keyboard_types error: [json.exception.type_error.302] type must be array, but is null");

    exception_test<pqrs::osx::system_preferences::properties>(
        nlohmann::json::object({
            {"use-fkeys-as-standard-function-keys", nlohmann::json()},
        }),
        "unknown key: `use-fkeys-as-standard-function-keys`");
  };
}
