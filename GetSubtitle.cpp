#include "GetSubtitle.h"


bool BiliBiliHelper::praseVideoInfoCid(const std::string &id) {
    //当id前两位为BV时，使用bvid接口，否则使用aid接口
    if (id.substr(0, 2) == "BV") {
        session.SetUrl(cpr::Url("https://api.bilibili.com/x/web-interface/view?bvid=" + id));
    } else if (id.substr(0, 2) == "av") {
        session.SetUrl(cpr::Url("https://api.bilibili.com/x/web-interface/view?aid=" + id.substr(2)));
    } else {
        throw std::runtime_error("Unknown id type, input aid or BVID");
    }
    auto response = session.Get();
    if (response.status_code != 200) {
        throw std::runtime_error("Error: Failed to get video info\n");
    }
    auto s = JsonVideoInfo{};
    glz::read<glz::opts{.error_on_unknown_keys = false}>(s, response.text);
    cid = s.data.cid;
    aid = s.data.aid;
    return true;
}

JsonSubtitle BiliBiliHelper::getSubtitle() {
    session.SetUrl(cpr::Url(
            "https://api.bilibili.com/x/player/v2?aid=" + std::to_string(aid) + "&cid=" + std::to_string(cid)));
    auto r = session.Get();
    if (r.status_code != 200) {
        throw std::runtime_error("Error: Failed to get subtitle");
    }
    auto s = JsonPlayerSubtitle{};
    glz::read<glz::opts{.error_on_unknown_keys = false}>(s, r.text);
    if (s.data.subtitle.subtitles.empty()) {
        throw std::runtime_error("Error: No subtitle found");
    }
    auto url = s.data.subtitle.subtitles[0].subtitle_url;
    session.SetUrl(cpr::Url("https:" + url));
    auto r2 = session.Get();
    if (r2.status_code != 200) {
        throw std::runtime_error("Error: Failed to get subtitle");
    }
    auto ans = JsonSubtitle{};
    glz::read<glz::opts{.error_on_unknown_keys = false}>(ans, r2.text);
    return ans;
}

BiliBiliHelper::BiliBiliHelper() {
    session.SetUserAgent(cpr::UserAgent(
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36 Edg/110.0.1587.41"));
    session.SetAcceptEncoding(cpr::AcceptEncoding(
            {cpr::AcceptEncodingMethods::deflate, cpr::AcceptEncodingMethods::gzip, cpr::AcceptEncodingMethods::zlib}));
}

bool BiliBiliHelper::writeSubtitle(const std::string &path, const JsonSubtitle &jsonSubtitle) {
    auto out = fmt::output_file(path);
    int x = 1;
    for (auto &i: jsonSubtitle.body) {
        out.print("{}\n{} --> {}\n{}\n\n", x, format_time(i.from), format_time(i.to), i.content);
        ++x;
    }
    return true;
}

std::string BiliBiliHelper::format_time(float seconds) {
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
