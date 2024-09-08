#include "styles.h"

// Color codes using ANSI escape sequences
std::string color_red(const std::string& input) {
    return "\033[31m" + input + "\033[0m";
}
std::string color_green(const std::string& input) {
    return "\033[32m" + input + "\033[0m";
}
std::string color_yellow(const std::string& input) {
    return "\033[33m" + input + "\033[0m";
}
std::string color_bright_yellow(const std::string& input) {
    return "\033[93m" + input + "\033[0m";
}
std::string color_blue(const std::string& input) {
    return "\033[34m" + input + "\033[0m";
}
std::string color_magenta(const std::string& input) {
    return "\033[35m" + input + "\033[0m";
}
std::string color_cyan(const std::string& input) {
    return "\033[36m" + input + "\033[0m";
}
std::string color_white(const std::string& input) {
    return "\033[37m" + input + "\033[0m";
}

// Unique styles using ANSI escape sequences
std::string style_bold(const std::string& input) {
    return "\033[1m" + input + "\033[0m";
}
std::string style_underline(const std::string& input) {
    return "\033[4m" + input + "\033[0m";
}
std::string style_blink(const std::string& input) {
    return "\033[5m" + input + "\033[0m";
}
std::string style_dim(const std::string& input) {
    return "\033[2m" + input + "\033[0m";
}
std::string style_italic(const std::string& input) {
    return "\033[3m" + input + "\033[0m";
}
std::string style_inverse(const std::string& input) {
    return "\033[7m" + input + "\033[0m";
}
std::string style_hidden(const std::string& input) {
    return "\033[8m" + input + "\033[0m";
}
std::string style_strikethrough(const std::string& input) {
    return "\033[9m" + input + "\033[0m";
}
std::string style_double_underline(const std::string& input) {
    return "\033[21m" + input + "\033[0m";
}
std::string style_overline(const std::string& input) {
    return "\033[53m" + input + "\033[0m";
}
