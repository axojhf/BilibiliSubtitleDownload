#ifndef BILIBILISUBTITLEDOWNLOAD_CONVERT_H
#define BILIBILISUBTITLEDOWNLOAD_CONVERT_H
#define Opencc_BUILT_AS_STATIC 1

#include <string>
#include <opencc/opencc.h>

inline std::string convert(const std::string &input, const std::string &configFileName);


#endif //BILIBILISUBTITLEDOWNLOAD_CONVERT_H
