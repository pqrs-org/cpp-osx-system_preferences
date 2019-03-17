#include <catch2/catch.hpp>

#include <pqrs/osx/system_preferences/extra/nlohmann_json.hpp>

TEST_CASE("nlohmann_json keyboard_type") {
  {
    pqrs::osx::iokit_hid_vendor_id vendor_id(1);
    pqrs::osx::iokit_hid_product_id product_id(2);
    pqrs::osx::iokit_hid_country_code country_code(3);

    pqrs::osx::system_preferences::keyboard_type_key t1(vendor_id,
                                                        product_id,
                                                        country_code);

    nlohmann::json json = t1;
    REQUIRE(json == nlohmann::json::object({
                        {"vendor_id", vendor_id},
                        {"product_id", product_id},
                        {"country_code", country_code},
                    }));

    // from_json

    auto t2 = json.get<pqrs::osx::system_preferences::keyboard_type_key>();
    REQUIRE(t2.get_vendor_id() == vendor_id);
    REQUIRE(t2.get_product_id() == product_id);
    REQUIRE(t2.get_country_code() == country_code);

    REQUIRE(t1 == t2);
  }

  // keyboard_type errors

  {
    auto json = nlohmann::json();
    REQUIRE_THROWS_AS(json.get<pqrs::osx::system_preferences::keyboard_type_key>(),
                      pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(json.get<pqrs::osx::system_preferences::keyboard_type_key>(),
                        "json must be object, but is `null`");
  }
  {
    auto json = nlohmann::json::object({
        {"vendor_id", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(json.get<pqrs::osx::system_preferences::keyboard_type_key>(),
                      pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(json.get<pqrs::osx::system_preferences::keyboard_type_key>(),
                        "vendor_id error: json must be number, but is `null`");
  }
  {
    auto json = nlohmann::json::object({
        {"product_id", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(json.get<pqrs::osx::system_preferences::keyboard_type_key>(),
                      pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(json.get<pqrs::osx::system_preferences::keyboard_type_key>(),
                        "product_id error: json must be number, but is `null`");
  }
  {
    auto json = nlohmann::json::object({
        {"country_code", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(json.get<pqrs::osx::system_preferences::keyboard_type_key>(),
                      pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(json.get<pqrs::osx::system_preferences::keyboard_type_key>(),
                        "country_code error: json must be number, but is `null`");
  }
  {
    auto json = nlohmann::json::object({
        {"vendor-id", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(json.get<pqrs::osx::system_preferences::keyboard_type_key>(),
                      pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(json.get<pqrs::osx::system_preferences::keyboard_type_key>(),
                        "unknown key: `vendor-id`");
  }
}

TEST_CASE("nlohmann_json properties") {
  {
    using keyboard_types_t = std::map<pqrs::osx::system_preferences::keyboard_type_key,
                                      pqrs::osx::iokit_keyboard_type>;

    pqrs::osx::system_preferences::keyboard_type_key keyboard_type_key(
        pqrs::osx::iokit_hid_vendor_id(1),
        pqrs::osx::iokit_hid_product_id(2),
        pqrs::osx::iokit_hid_country_code(3));
    keyboard_types_t keyboard_types;
    keyboard_types[keyboard_type_key] = pqrs::osx::iokit_keyboard_type(4);

    pqrs::osx::system_preferences::properties p1;
    p1.set_use_fkeys_as_standard_function_keys(true);
    p1.set_scroll_direction_is_natural(false);
    p1.set_keyboard_types(keyboard_types);

    nlohmann::json json = p1;
    REQUIRE(json == nlohmann::json::object({
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

    REQUIRE(p1 == p2);
    REQUIRE(p1.get_use_fkeys_as_standard_function_keys() == true);
    REQUIRE(p1.get_scroll_direction_is_natural() == false);
    REQUIRE(p1.get_keyboard_types() == keyboard_types);
  }

  // properties errors

  {
    auto json = nlohmann::json();
    REQUIRE_THROWS_AS(json.get<pqrs::osx::system_preferences::properties>(),
                      pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(json.get<pqrs::osx::system_preferences::properties>(),
                        "json must be object, but is `null`");
  }
  {
    auto json = nlohmann::json::object({
        {"use_fkeys_as_standard_function_keys", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(json.get<pqrs::osx::system_preferences::properties>(),
                      pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(json.get<pqrs::osx::system_preferences::properties>(),
                        "`use_fkeys_as_standard_function_keys` must be boolean, but is `null`");
  }
  {
    auto json = nlohmann::json::object({
        {"scroll_direction_is_natural", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(json.get<pqrs::osx::system_preferences::properties>(),
                      pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(json.get<pqrs::osx::system_preferences::properties>(),
                        "`scroll_direction_is_natural` must be boolean, but is `null`");
  }
  {
    auto json = nlohmann::json::object({
        {"keyboard_types", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(json.get<pqrs::osx::system_preferences::properties>(),
                      pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(json.get<pqrs::osx::system_preferences::properties>(),
                        "`keyboard_types` must be array, but is `null`");
  }
  {
    auto json = nlohmann::json::object({
        {"keyboard_types", nlohmann::json::array({
                               nlohmann::json(),
                           })},
    });
    REQUIRE_THROWS_AS(json.get<pqrs::osx::system_preferences::properties>(),
                      pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(json.get<pqrs::osx::system_preferences::properties>(),
                        "keyboard_types error: [json.exception.type_error.302] type must be array, but is null");
  }
  {
    auto json = nlohmann::json::object({
        {"use-fkeys-as-standard-function-keys", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(json.get<pqrs::osx::system_preferences::properties>(),
                      pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(json.get<pqrs::osx::system_preferences::properties>(),
                        "unknown key: `use-fkeys-as-standard-function-keys`");
  }
}
