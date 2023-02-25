#include "convert.h"
#include "GetSubtitle.h"
#include <fmt/core.h>
#include <cmdlime/commandlinereader.h>

struct Cfg : public cmdlime::Config {
    CMDLIME_ARG(id, std::string);
    CMDLIME_PARAM(page, int)();
};

int main(int argc, char *argv[]) {
    auto reader = cmdlime::CommandLineReader{"BiliBili Subtitle Downloader"};
    auto cfg = reader.read<Cfg>(argc, argv);
    BiliBiliHelper helper{};
    if (!helper.praseVideoInfoCid(cfg.id)) {
        return 1;
    }
    auto res = helper.getSubtitle();
    helper.writeSubtitle(argv[1] + std::string(".srt"), res);
    return 0;
}
