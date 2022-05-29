#include "boost_test.hpp"
#include "keyboard_type_test.hpp"
#include "nlohmann_json_test.hpp"
#include "properties_test.hpp"

int main(void) {
  run_boost_test();
  run_keyboard_type_test();
  run_nlohmann_json_test();
  run_properties_test();
  return 0;
}
