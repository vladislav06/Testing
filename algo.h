//
// Created by vm on 24.7.3.
//

#pragma once
#include <string>
#include <vector>
#include <fstream>
struct Track {
    std::string name;
    std::string path;
};


struct Playlist {
    std::string name;
    std::vector<Track> tracks{};
};

bool save(std::vector<Playlist> &playlists, std::ostream &ostream);