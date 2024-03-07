#include "algo.h"

bool save(std::vector<Playlist> &playlists, std::ostream &ostream) {
    ostream << "[";
    for (auto &playlist: playlists) {
        ostream << "{";
        ostream << "\"name\":\"" << playlist.name << "\",";
        ostream << "\"tracks\":[";
        for (auto &track: playlist.tracks) {
            ostream << "{";
            ostream << "\"name\":\"" << track.name << "\",";
            ostream << "\"path\":\"" << track.path << "\"";
            ostream << "}";
            if (&track != &playlist.tracks.back()) {
                ostream << ",";
            }
        }
        ostream << "]";

        ostream << "}";
        if (&playlist != &playlists.back()) {
            ostream << ",";
        }
    }

    ostream << "]";
    return ostream.good();
}
