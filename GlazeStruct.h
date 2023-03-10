#ifndef BILIBILISUBTITLEDOWNLOAD_GLAZESTRUCT_H
#define BILIBILISUBTITLEDOWNLOAD_GLAZESTRUCT_H

#include <string>
#include <glaze/core/macros.hpp>
#include <glaze/glaze.hpp>

struct JsonPlayerSubtitleDataSubtitleSubtitleStruct
{
    std::string lan;
    std::string subtitle_url;

    GLZ_LOCAL_META(JsonPlayerSubtitleDataSubtitleSubtitleStruct, lan, subtitle_url);
};

struct JsonVideoInfoDataSubtitle
{
    std::vector<JsonPlayerSubtitleDataSubtitleSubtitleStruct> list;

    GLZ_LOCAL_META(JsonVideoInfoDataSubtitle, list);
};

struct JsonVideoInfoData
{
    // uint64_t aid;
    // uint64_t cid;
    JsonVideoInfoDataSubtitle subtitle;

    GLZ_LOCAL_META(JsonVideoInfoData, subtitle);
};

/**
 * @brief api.bilibili.com/x/web-interface/view 获取的Json数据结构
 *
 */
struct JsonVideoInfo
{
    uint8_t code;
    JsonVideoInfoData data;

    GLZ_LOCAL_META(JsonVideoInfo, code, data);
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

//--------------------------------------------
// 解析ep，ss的Json数据结构
//--------------------------------------------

struct EpSsJsonResultEpisode {
    std::string bvid;

    GLZ_LOCAL_META(EpSsJsonResultEpisode, bvid);
};

struct EpSsJsonResult {
    std::vector<EpSsJsonResultEpisode> episodes;

    GLZ_LOCAL_META(EpSsJsonResult, episodes);
};

struct EpSsJson {
    int64_t code;
    EpSsJsonResult result;

    GLZ_LOCAL_META(EpSsJson, code, result);
};

#endif // BILIBILISUBTITLEDOWNLOAD_GLAZESTRUCT_H
