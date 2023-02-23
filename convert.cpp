#include "convert.h"

std::string convert(const std::string &input, const std::string &configFileName) {
    const opencc::SimpleConverter converter(configFileName);
    return converter.Convert(input);
}
