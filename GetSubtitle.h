#ifndef BILIBILISUBTITLEDOWNLOAD_GETSUBTITLE_H
#define BILIBILISUBTITLEDOWNLOAD_GETSUBTITLE_H

#include <cpr/cpr.h>
#include <string>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <fmt/os.h>
#include "GlazeStruct.h"

class BiliBiliHelper
{
private:
    /**
     * @brief Cpr会话
     */
    cpr::Session session{};
    /**
     * @brief 视频cid
     */
    uint64_t cid{0};
    /**
     * @brief 视频aid
     */
    uint64_t aid{0};
    /**
     * @brief 是否存在字幕
     */
    bool isExistSubtitle{false};

    std::string subtitle_url{};

    /**
     * @brief 字幕语言
     * 0:zh-Hans 1:zh-Hant 2:其他
     */
    int8_t subtitle_lan{-1};

    JsonSubtitle subtitle{};

public:
    BiliBiliHelper();

    bool praseVideoInfoCid(const std::string &id);

    bool getSubtitle();

    bool writeSubtitle(const std::string &path);

    std::string format_time(float seconds);

    void setProxy(const std::string &proxy);
};

#endif // BILIBILISUBTITLEDOWNLOAD_GETSUBTITLE_H
