#include "algo.h"
#include "iostream"

int main() {
    // init structure
    // \\\\ is needed because json requires \\ to print one \ and c++ requires \\ to print one \.

    std::vector<Playlist> playlists = {
            {
                    .name="playlist 1",
                    .tracks={
                            {.name="track11.mp3", .path="C:\\\\users\\\\"
                                                        "music"},
                            {.name="track12.mp3", .path="C:\\\\users\\\\music"},
                            {.name="track13.mp3", .path="C:\\\\users\\\\music"},
                            {.name="track14.mp3", .path="C:\\\\users\\\\music"}
                    }
            },
            {
                    .name="playlist 2",
                    .tracks={
                            {.name="track21.mp3", .path="C:\\\\users\\\\music"},
                            {.name="track22.mp3", .path="C:\\\\users\\\\music"}
                    }
            },
            {
                    .name="playlist 3",
                    .tracks={

                    }
            }
    };

    // open file
    std::ofstream fout("./output.json");

    // save playlist and print status
    std::cout << "status: " << save(playlists, fout);

    fout.close();

    return 0;
}
