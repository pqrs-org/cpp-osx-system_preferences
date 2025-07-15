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

  "nlohmann_json properties"_test = [] {
    {
      pqrs::osx::system_preferences::properties p1;
      p1.set_use_fkeys_as_standard_function_keys(true);
      p1.set_scroll_direction_is_natural(false);

      nlohmann::json json = p1;
      expect(json == nlohmann::json::object({
                         {"use_fkeys_as_standard_function_keys", true},
                         {"scroll_direction_is_natural", false},
                     }));

      // from_json

      auto p2 = json.get<pqrs::osx::system_preferences::properties>();

      expect(p1 == p2);
      expect(p1.get_use_fkeys_as_standard_function_keys() == true);
      expect(p1.get_scroll_direction_is_natural() == false);
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
            {"use-fkeys-as-standard-function-keys", nlohmann::json()},
        }),
        "unknown key: `use-fkeys-as-standard-function-keys`");
  };
}
