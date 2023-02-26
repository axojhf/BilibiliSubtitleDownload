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
     * @brief 是否存在字幕
     */
    bool isExistSubtitle{false};

    std::string subtitle_url{};

    uint64_t index{1};

    /**
     * @brief 字幕语言
     * 0:zh-Hans 1:zh-Hant 2:其他
     */
    int8_t subtitle_lan{-1};

    JsonSubtitle subtitle{};

public:
    BiliBiliHelper();

    bool praseVideo(const std::string &id);

    bool getSubtitle();

    bool writeSubtitle(const std::string &path);

    std::string format_time(float seconds);

    void setProxy(const std::string &proxy);

    void setIndex(uint64_t index);

private:
    bool praseNormalVideo(const std::string &url);

    bool praseBangumiVideo(const std::string &url);
};

#endif // BILIBILISUBTITLEDOWNLOAD_GETSUBTITLE_H
