#ifndef STYLES_H
#define STYLES_H

#include <string>

// Color codes using ANSI escape sequences
std::string color_red(const std::string& input);
std::string color_green(const std::string& input);
std::string color_yellow(const std::string& input);
std::string color_bright_yellow(const std::string& input);
std::string color_blue(const std::string& input);
std::string color_magenta(const std::string& input);
std::string color_cyan(const std::string& input);
std::string color_white(const std::string& input);

// Unique styles using ANSI escape sequences
std::string style_bold(const std::string& input);
std::string style_underline(const std::string& input);
std::string style_blink(const std::string& input);
std::string style_dim(const std::string& input);
std::string style_italic(const std::string& input);
std::string style_inverse(const std::string& input);
std::string style_hidden(const std::string& input);
std::string style_strikethrough(const std::string& input);
std::string style_double_underline(const std::string& input);
std::string style_overline(const std::string& input);

#endif