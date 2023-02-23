#ifndef BILIBILISUBTITLEDOWNLOAD_GETSUBTITLE_H
#define BILIBILISUBTITLEDOWNLOAD_GETSUBTITLE_H

#include <cpr/cpr.h>
#include <string>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <fmt/os.h>
#include "GlazeStruct.h"

class BiliBiliHelper {
private:
    cpr::Session session;
    uint64_t cid{0};
    uint64_t aid{0};
public:
    BiliBiliHelper();

    bool praseVideoInfoCid(const std::string &id);

    JsonSubtitle getSubtitle();

    bool writeSubtitle(const std::string &path, const JsonSubtitle &jsonSubtitle);

    std::string format_time(float seconds);
};

#endif //BILIBILISUBTITLEDOWNLOAD_GETSUBTITLE_H
