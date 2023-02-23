cmake_minimum_required(VERSION 3.24)
project(BilibiliSubtitleDownload)

set(CMAKE_CXX_STANDARD 20)

include_directories(thirdparts/include)
link_directories(thirdparts/lib)

add_executable(BilibiliSubtitleDownload main.cpp convert.cpp convert.h GetSubtitle.cpp GetSubtitle.h GlazeStruct.h)

#设置符号-fpermissive
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

target_link_libraries(BilibiliSubtitleDownload fmt opencc marisa cpr curl winmm zstd ws2_32 nghttp2 zlib advapi32 Wldap32 iphlpapi crypt32 bcrypt)
