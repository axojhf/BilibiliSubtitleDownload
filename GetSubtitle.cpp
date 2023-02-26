#include "GetSubtitle.h"
#include "convert.h"

/**
 * @brief Prase the video info
 * @param id bvid or aid or ss or ep
 * @return true
 * @return false
 */
bool BiliBiliHelper::praseVideo(const std::string &id)
{
    auto result = false;
    // 当id前两位为BV时，使用bvid接口，否则使用aid接口
    // 这个接口可能存在字幕信息，但是如果没有字幕，可以访问另一个接口获取字幕信息（可能是AI翻译的）
    if (id.substr(0, 2) == "BV")
    {
        result = praseNormalVideo("https://api.bilibili.com/x/web-interface/view?bvid=" + id);
    }
    else if (id.substr(0, 2) == "av")
    {
        result = praseNormalVideo("https://api.bilibili.com/x/web-interface/view?aid=" + id.substr(2));
    }
    else if(id.substr(0, 2) == "ss")
    {
        result = praseBangumiVideo("https://api.bilibili.com/pgc/view/web/season?season_id=" + id.substr(2));
    }
    else if(id.substr(0, 2) == "ep")
    {
        result = praseBangumiVideo("https://api.bilibili.com/pgc/view/web/season?ep_id=" + id.substr(2));
    }    
    else
    {
        throw std::runtime_error("Unknown id type, input aid or BVID or ss or ep");
    }
    return result;
}

/**
 * @brief Get the subtitle object
 *
 * @return bool
 */
bool BiliBiliHelper::getSubtitle()
{
    if (!this->isExistSubtitle)
    {
        throw std::runtime_error("Error: No subtitle url");
    }
    session.SetUrl(cpr::Url(this->subtitle_url));
    auto r2 = session.Get();
    if (r2.status_code != 200)
    {
        throw std::runtime_error("Error: Failed to get subtitle");
    }
    if (this->subtitle_lan == 0 || this->subtitle_lan == 2)
    {
        glz::read<glz::opts{.error_on_unknown_keys = false}>(this->subtitle, r2.text);
    }
    else if (this->subtitle_lan == 1)
    {
        auto zh_hans = convert(r2.text, "t2sextend.json");
        glz::read<glz::opts{.error_on_unknown_keys = false}>(this->subtitle, zh_hans);
    }
    else
    {
        throw std::runtime_error("Error: Unknown subtitle lan");
    }
    return true;
}

/**
 * @brief Construct a new Bili Bili Helper:: Bili Bili Helper object
 */
BiliBiliHelper::BiliBiliHelper()
{
    session.SetUserAgent(cpr::UserAgent(
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36 Edg/110.0.1587.41"));
    session.SetAcceptEncoding(cpr::AcceptEncoding(
        {cpr::AcceptEncodingMethods::deflate, cpr::AcceptEncodingMethods::gzip, cpr::AcceptEncodingMethods::zlib}));
}

/**
 * @brief Write the subtitle to a file
 *
 * @param path The path of the file
 * @return true
 * @return false
 */
bool BiliBiliHelper::writeSubtitle(const std::string &path)
{
    auto out = fmt::output_file(path);
    int x = 1;
    for (auto &&i : this->subtitle.body)
    {
        out.print("{}\n{} --> {}\n{}\n\n", x, format_time(i.from), format_time(i.to), i.content);
        ++x;
    }
    return true;
}

/**
 * @brief Format the time to a string
 *
 * @param seconds
 * @return std::string
 */
std::string BiliBiliHelper::format_time(float seconds)
{
    int total_milliseconds = static_cast<int>(seconds * 1000);
    int hours = total_milliseconds / (1000 * 60 * 60);
    int minutes = (total_milliseconds / (1000 * 60)) % 60;
    int seconds_int = (total_milliseconds / 1000) % 60;
    int milliseconds = total_milliseconds % 1000;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setw(2) << minutes << ":"
        << std::setw(2) << seconds_int << ","
        << std::setw(3) << milliseconds;
    return oss.str();
}

void BiliBiliHelper::setProxy(const std::string &proxy)
{
    session.SetProxies(cpr::Proxies{{"http", proxy}, {"https", proxy}});
}

/// @brief 设置分P的位置，默认不设置为1
/// @param index 
void BiliBiliHelper::setIndex(uint64_t index)
{
    this->index = index;
}

/// @brief 解析av号或者bv号的普通视频
/// @param url 目标url
bool BiliBiliHelper::praseNormalVideo(const std::string &url)
{
    session.SetUrl(cpr::Url(url));
    auto response = session.Get();
    if (response.status_code != 200)
    {
        throw std::runtime_error("Error: Failed to get video info\n");
    }
    auto s = JsonVideoInfo{};
    glz::read<glz::opts{.error_on_unknown_keys = false}>(s, response.text);
    if (s.data.subtitle.list.empty())
    {
        return false;
    }
    // 在s.data.subtitle里优先找到lan为zh-Hans的字幕
    for (auto &&i : s.data.subtitle.list)
    {
        // 如果找到了，就解析字幕
        if (i.lan == "zh-Hans" || i.lan == "ai-zh")
        {
            this->subtitle_url = i.subtitle_url;
            this->isExistSubtitle = true;
            this->subtitle_lan = 0;
            break;
        }
        // 如果没有找到，就找lan为zh-Hant的字幕
        else if (i.lan == "zh-Hant")
        {
            this->subtitle_url = i.subtitle_url;
            this->isExistSubtitle = true;
            this->subtitle_lan = 1;
        }
        else
        {
            this->subtitle_url = i.subtitle_url;
            this->isExistSubtitle = true;
            this->subtitle_lan = 2;
        }
    }
    return true;
}

/// @brief 解析ss号或者ep号的番剧/影视视频
/// @param url 目标url
bool BiliBiliHelper::praseBangumiVideo(const std::string &url)
{
    session.SetUrl(cpr::Url(url));
    auto response = session.Get();
    if (response.status_code != 200)
    {
        throw std::runtime_error("Error: status_code Error Failed to get ep/ss info\n");
    }
    auto s = EpSsJson{};
    glz::read<glz::opts{.error_on_unknown_keys = false}>(s, response.text);
    if (s.code != 0 || s.result.episodes.empty() || index > s.result.episodes.size())
    {
        throw std::runtime_error("Error: api code Error Failed to get ep/ss info\n");
    }
    auto result = praseNormalVideo("https://api.bilibili.com/x/web-interface/view?bvid=" + s.result.episodes[index - 1].bvid);
    return result;
}
