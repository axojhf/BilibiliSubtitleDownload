#ifndef BILIBILISUBTITLEDOWNLOAD_GLAZESTRUCT_H
#define BILIBILISUBTITLEDOWNLOAD_GLAZESTRUCT_H

#include <string>
#include <glaze/core/macros.hpp>
#include <glaze/glaze.hpp>

struct JsonVideoInfoData
{
    uint64_t aid;
    uint64_t cid;

    GLZ_LOCAL_META(JsonVideoInfoData, aid, cid);
};

struct JsonVideoInfo
{
    uint8_t code;
    JsonVideoInfoData data;

    GLZ_LOCAL_META(JsonVideoInfo, code, data);
};

struct JsonPlayerSubtitleDataSubtitleSubtitleStruct
{
    std::string lan;
    std::string subtitle_url;

    GLZ_LOCAL_META(JsonPlayerSubtitleDataSubtitleSubtitleStruct, lan, subtitle_url);
};

struct JsonPlayerSubtitleDataSubtitle
{
    std::vector<JsonPlayerSubtitleDataSubtitleSubtitleStruct> subtitles;

    GLZ_LOCAL_META(JsonPlayerSubtitleDataSubtitle, subtitles);
};

struct JsonPlayerSubtitleData
{
    JsonPlayerSubtitleDataSubtitle subtitle;

    GLZ_LOCAL_META(JsonPlayerSubtitleData, subtitle);
};

struct JsonPlayerSubtitle
{
    uint8_t code;

    JsonPlayerSubtitleData data;

    GLZ_LOCAL_META(JsonPlayerSubtitle, code, data);
};

struct JsonSubtitleBody
{
    float from;
    float to;
    std::string content;

    GLZ_LOCAL_META(JsonSubtitleBody, from, to, content);
};

struct JsonSubtitle
{
    std::vector<JsonSubtitleBody> body;

    GLZ_LOCAL_META(JsonSubtitle, body);
};

#endif // BILIBILISUBTITLEDOWNLOAD_GLAZESTRUCT_H
