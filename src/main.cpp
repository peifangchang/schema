#include <iostream>

import string_utils;

int main(int argc, char **argv) {
  auto aa = "hello-world";
  println("{}", string_utils::to_pascal(aa));
  println("{}", string_utils::to_camel(aa));
  println("{}", string_utils::to_snake(aa));
  println("{}", string_utils::to_kebab(aa));
  return 0;
}
