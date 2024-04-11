//
// Created by vm on 24.11.4.
//
#include <cstring>
#include "algo.h"
#include "gtest/gtest.h"

namespace {
    TEST(Saver, NormalData) {
        std::vector<Playlist> playlists = {
                {
                        .name="playlist 1",
                        .tracks={
                                {.name="track11.mp3", .path=R"(C:\\users\\music)"},
                                {.name="track12.mp3", .path=R"(C:\\users\\music)"},
                                {.name="track13.mp3", .path=R"(C:\\users\\music)"},
                                {.name="track14.mp3", .path=R"(C:\\users\\music)"}
                        }
                },
                {
                        .name="playlist 2",
                        .tracks={
                                {.name="track21.mp3", .path=R"(C:\\users\\music)"},
                                {.name="track22.mp3", .path=R"(C:\\users\\music)"}
                        }
                },
                {
                        .name="playlist 3",
                        .tracks={

                        }
                }
        };
        std::stringstream strstream;
        save(playlists, strstream);
        ASSERT_EQ(strstream.str(),
                  "[{\"name\":\"playlist 1\",\"tracks\":[{\"name\":\"track11.mp3\",\"path\":\"C:\\\\users\\\\music\"},{\"name\":\"track12.mp3\",\"path\":\"C:\\\\users\\\\music\"},{\"name\":\"track13.mp3\",\"path\":\"C:\\\\users\\\\music\"},{\"name\":\"track14.mp3\",\"path\":\"C:\\\\users\\\\music\"}]},{\"name\":\"playlist 2\",\"tracks\":[{\"name\":\"track21.mp3\",\"path\":\"C:\\\\users\\\\music\"},{\"name\":\"track22.mp3\",\"path\":\"C:\\\\users\\\\music\"}]},{\"name\":\"playlist 3\",\"tracks\":[]}]");
    }

    TEST(Saver, NoData) {
        std::vector<Playlist> playlists = {
                {
                        .name="playlist 1",
                        .tracks={

                        }
                },
                {
                        .name="playlist 2",
                        .tracks={

                        }
                }
        };
        std::stringstream strstream;
        save(playlists, strstream);
        ASSERT_EQ(strstream.str(), "[{\"name\":\"playlist 1\",\"tracks\":[]},{\"name\":\"playlist 2\",\"tracks\":[]}]");
    }

    TEST(Saver, NoData2) {
        std::vector<Playlist> playlists;
        std::stringstream strstream;
        save(playlists, strstream);
        ASSERT_EQ(strstream.str(), "[]");
    }

    TEST(Saver, EmptyData) {
        std::vector<Playlist> playlists = {
                {
                        .name=" ",
                        .tracks={
                                {.name=" ", .path=R"(C:\\users\\music)"},
                                {.name=" ", .path=R"(C:\\users\\music)"}
                        }
                },
                {
                        .name=" ",
                        .tracks={
                                {.name=" ", .path=R"(C:\\users\\music)"},
                                {.name=" ", .path=R"(C:\\users\\music)"}
                        }
                }
        };
        std::stringstream strstream;
        save(playlists, strstream);
        ASSERT_EQ(strstream.str(),
                  "[{\"name\":\" \",\"tracks\":[{\"name\":\" \",\"path\":\"C:\\\\users\\\\music\"},{\"name\":\" \",\"path\":\"C:\\\\users\\\\music\"}]},{\"name\":\" \",\"tracks\":[{\"name\":\" \",\"path\":\"C:\\\\users\\\\music\"},{\"name\":\" \",\"path\":\"C:\\\\users\\\\music\"}]}]");
    }

    TEST(Saver, EmptyPath) {
        std::vector<Playlist> playlists = {
                {
                        .name=" ",
                        .tracks={
                                {.name=" ", .path=" "},
                                {.name=" ", .path=" "}
                        }
                },
                {
                        .name=" ",
                        .tracks={
                                {.name=" ", .path=" "},
                                {.name=" ", .path=" "}
                        }
                }
        };
        std::stringstream strstream;
        save(playlists, strstream);
        ASSERT_EQ(strstream.str(),
                  "[{\"name\":\" \",\"tracks\":[{\"name\":\" \",\"path\":\" \"},{\"name\":\" \",\"path\":\" \"}]},{\"name\":\" \",\"tracks\":[{\"name\":\" \",\"path\":\" \"},{\"name\":\" \",\"path\":\" \"}]}]");
    }

    TEST(Saver, MalformedData) {
        GTEST_SKIP();
        std::vector<Playlist> playlists = {
                {
                        .name=" ",
                        .tracks={
                                {.name=" ", .path="12\0 34"},
                        }
                }
        };
        std::stringstream strstream;
        save(playlists, strstream);
        ASSERT_EQ(strstream.str(),
                  "[{\"name\":\" \",\"tracks\":[{\"name\":\" \",\"path\":\"12\0 34\"}]}}]");
    }

    TEST(Saver, MalformedData2) {
        Playlist pl = {
                .name=" ",
                .tracks={
                        {.name=" ", .path="1234"},
                }
        };
        Playlist &pl2 = pl;
        std::vector<Playlist> playlists = {
                pl, pl2
        };
        std::stringstream strstream;
        save(playlists, strstream);
        ASSERT_EQ(strstream.str(),
                  "[{\"name\":\" \",\"tracks\":[{\"name\":\" \",\"path\":\"1234\"}]},{\"name\":\" \",\"tracks\":[{\"name\":\" \",\"path\":\"1234\"}]}]");
    }

    TEST(Saver, MalformedData3) {
        auto c = new char[1];
        c[0] = 0;
        Playlist pl = {
                .name=c,
                .tracks={
                        {.name=c, .path=c},
                }
        };
        Playlist &pl2 = pl;
        std::vector<Playlist> playlists = {
                pl
        };
        std::stringstream strstream;
        save(playlists, strstream);
        ASSERT_EQ(strstream.str(),
                  "[{\"name\":\"\",\"tracks\":[{\"name\":\"\",\"path\":\"\"}]}]");
    }

    TEST(Saver, MalformedData4) {
        std::vector<Playlist> playlists;

        playlists.push_back({.name="1", .tracks={{.name="2", .path="3"},}});

        auto d = new uint8_t[56];
        for (int i = 0; i < 56; i++) {
            d[i] = 0;
        }
        std::memcpy(&playlists[0], d, 56);

        std::stringstream strstream;

        save(playlists, strstream);

        ASSERT_EQ(strstream.str(), "[{\"name\":\"\",\"tracks\":[]}]");

        delete[] d;
    }

}
