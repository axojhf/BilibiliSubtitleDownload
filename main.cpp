#include "convert.h"
#include "GetSubtitle.h"
#include <fmt/core.h>

int main(int argc, char *argv[]) {
    //当参数个数不为2时，输出错误信息并退出
    if (argc != 2) {
        fmt::print(stderr, "Error Arguments\n");
        return 1;
    }
    BiliBiliHelper helper{};
    if (!helper.praseVideoInfoCid(argv[1])) {
        return 1;
    }
    auto res = helper.getSubtitle();
    helper.writeSubtitle(argv[1] + std::string(".srt"), res);
    return 0;
}
