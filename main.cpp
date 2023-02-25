#include "convert.h"
#include "GetSubtitle.h"
#include <fmt/core.h>
#include <cmdlime/commandlinereader.h>

struct Cfg : public cmdlime::Config {
    CMDLIME_ARG(id, std::string);
    CMDLIME_PARAM(page, int)();
    CMDLIME_PARAM(proxy, std::string)() << cmdlime::WithoutShortName{};
};

int main(int argc, char *argv[]) {
    auto reader = cmdlime::CommandLineReader{"BiliBili Subtitle Downloader"};
    auto cfg = reader.read<Cfg>(argc, argv);
    BiliBiliHelper helper{};
    if (cfg.proxy != "") {
        helper.setProxy(cfg.proxy);
    }
    if (!helper.praseVideoInfoCid(cfg.id)) {
        fmt::print("Error: Failed to get subtitle\n");
        return 1;
    }
    helper.getSubtitle();
    helper.writeSubtitle(cfg.id + ".srt");
    return 0;
}
