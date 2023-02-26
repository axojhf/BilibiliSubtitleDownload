#include "convert.h"
#include "GetSubtitle.h"
#include <fmt/core.h>
#include <cmdlime/commandlinereader.h>

struct Cfg : public cmdlime::Config
{
    CMDLIME_ARG(id, std::string);
    CMDLIME_PARAM(page, int)
    (1);
    CMDLIME_PARAM(proxy, std::string)
        () << cmdlime::WithoutShortName{};
};

int main(int argc, char *argv[])
{
    auto reader = cmdlime::CommandLineReader{"BiliBili Subtitle Downloader"};
    auto cfg = reader.read<Cfg>(argc, argv);
    BiliBiliHelper helper{};
    if (cfg.proxy != "")
    {
        helper.setProxy(cfg.proxy);
    }
    if (cfg.page != 1)
    {
        helper.setIndex(static_cast<uint64_t>(cfg.page));
    }
    if (!helper.praseVideo(cfg.id))
    {
        fmt::print("Error: No subtitles\n");
        return 1;
    }
    helper.getSubtitle();
    helper.writeSubtitle(cfg.id + ".srt");
    return 0;
}
