module;

#include <algorithm>
#include <string>
#include <vector>

export module string_utils;

namespace string_utils {

export std::string replace_all(const std::string &str,
                               const std::string &oldStr,
                               const std::string &newStr) {
  std::string replace_str = str;
  std::string::size_type pos = replace_str.find(oldStr);
  while (pos != std::string::npos) {
    replace_str.replace(pos, oldStr.size(), newStr);
    pos = replace_str.find(oldStr, pos + newStr.size());
  }
  return replace_str;
}

export std::string to_lower_case(const std::string &str) {
  std::string lower_str = str;
  std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                 ::tolower);
  return lower_str;
}

export std::string to_upper_case(const std::string &str) {
  std::string upper_str = str;
  std::transform(upper_str.begin(), upper_str.end(), upper_str.begin(),
                 ::toupper);
  return upper_str;
}

export std::vector<std::string> split_str(const std::string &str,
                                          const std::string &pattern) {
  std::vector<std::string> result;
  std::string::size_type begin, end;

  end = str.find(pattern);
  begin = 0;

  while (end != std::string::npos) {
    if (end - begin != 0) {
      result.push_back(str.substr(begin, end - begin));
    }
    begin = end + pattern.size();
    end = str.find(pattern, begin);
  }

  if (begin != str.length()) {
    result.push_back(str.substr(begin));
  }
  return result;
}

enum StringCaseStyle { NONE, KEBAB, SNAKE, CAMEL, PASCAL };

std::string case_style_name(const StringCaseStyle style) {
  if (style == StringCaseStyle::KEBAB)
    return "KEBAB";
  if (style == StringCaseStyle::SNAKE)
    return "SNAKE";
  if (style == StringCaseStyle::CAMEL)
    return "CAMEL";
  if (style == StringCaseStyle::PASCAL)
    return "PASCAL";
  return "NONE";
};

StringCaseStyle check_case_style(const std::string &str) {
  if (str.empty()) {
    return StringCaseStyle::NONE;
  }
  if (str.find_first_of("-") != std::string::npos) {
    return StringCaseStyle::KEBAB;
  }
  if (str.find_first_of("_") != std::string::npos) {
    return StringCaseStyle::SNAKE;
  }
  const char first_char = str.at(0);
  if (first_char >= 'a' && first_char <= 'z') {
    return StringCaseStyle::CAMEL;
  }
  if (first_char >= 'A' && first_char <= 'Z') {
    return StringCaseStyle::PASCAL;
  }
  return StringCaseStyle::NONE;
}

export std::vector<std::string> split_case_style(const std::string &str) {
  std::vector<std::string> result;
  auto style = check_case_style(str);
  if (style == StringCaseStyle::KEBAB) {
    return split_str(str, "-");
  }
  if (style == StringCaseStyle::SNAKE) {
    return split_str(str, "_");
  }
  if (style == StringCaseStyle::CAMEL || style == StringCaseStyle::PASCAL) {
    std::string tmp_str;
    bool is_first = true;
    for (auto c : str) {
      if (is_first == false && c >= 'A' && c <= 'Z') {
        result.push_back(tmp_str);
        tmp_str.clear();
      }
      tmp_str += c;
      is_first = false;
    }
    if (!tmp_str.empty()) {
      result.push_back(tmp_str);
    }
    return result;
  }
  result.push_back(str);
  return result;
}

export std::string to_camel(const std::string &str) {
  std::string result = "";
  auto words = split_case_style(str);
  for (auto word : words) {
    int i = 0;
    for (auto c : word) {
      if (i++ == 0) {
        if (result.empty())
          result += tolower(c);
        else
          result += toupper(c);
      } else {
        result += tolower(c);
      }
    }
  }
  return result;
}

export std::string to_pascal(const std::string &str) {
  std::string result = "";
  auto words = split_case_style(str);
  for (auto word : words) {
    int i = 0;
    for (auto c : word) {
      if (i++ == 0)
        result += toupper(c);
      else
        result += tolower(c);
    }
  }
  return result;
}

export std::string to_snake(const std::string &str) {
  std::string result = "";
  auto words = split_case_style(str);
  for (auto word : words) {
    if (!result.empty())
      result += '_';
    for (auto c : word) {
      result += tolower(c);
    }
  }
  return result;
}

export std::string to_kebab(const std::string &str) {
  std::string result = "";
  auto words = split_case_style(str);
  for (auto word : words) {
    if (!result.empty())
      result += '-';
    for (auto c : word) {
      result += tolower(c);
    }
  }
  return result;
}

} // namespace string_utils
