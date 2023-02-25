#ifndef BILIBILISUBTITLEDOWNLOAD_CONVERT_H
#define BILIBILISUBTITLEDOWNLOAD_CONVERT_H
#define Opencc_BUILT_AS_STATIC 1

#include <string>
#include <opencc/opencc.h>

/**
 * Convert the input utf-8 zh-Hant string to the zh-Hans string.
 * @param input The input string.
 * @param configFileName The config file name.
 * @return The converted string.
 */
inline std::string convert(const std::string &input, const std::string &configFileName)
{
    const opencc::SimpleConverter converter(configFileName);
    return converter.Convert(input);
}

#endif // BILIBILISUBTITLEDOWNLOAD_CONVERT_H
