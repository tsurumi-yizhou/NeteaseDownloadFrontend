#define SION_DISABLE_SSL
#include "sion.h"
#include "json.hpp"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

auto write(string url, string name) {
    auto cmd = "wget -c " + url + " -O " + name;
    system(cmd.c_str());
}

auto record(string data, string name, string filename) {
    auto fd = fopen(filename.c_str(), "a+");
    if (fputs(("\nconst " + name + "=" + data + "\n").c_str(), fd))    return;
    throw data;
}

auto download(unsigned id, string pic) {
    auto resp = nlohmann::json::parse(sion::Fetch("http://localhost:3000/song/url/v1?id=" + to_string(id) + "&level=hires").StrBody());
    auto url = resp["data"][0]["url"].get<string>();
    write(url, to_string(id) + ".mp3");
    write(pic, to_string(id) + ".jpg");
}

auto info(string title, string artist, unsigned id) {
    nlohmann::json info;
    info["artist"] = artist;
    info["name"] = title;
    info["cover"] = to_string(id) + ".jpg";
    info["url"] = to_string(id) + ".mp3";
    return info;
}

auto dump(unsigned long playlist) {
    auto data = sion::Fetch("http://localhost:3000/playlist/detail?id=" + to_string(playlist)).StrBody();
    auto resp = nlohmann::json::parse(data);
    //std::cout << data << std::endl;
    nlohmann::json list;
    for (auto music: resp["playlist"]["tracks"]) {
        unsigned long id = 0;
        string pic, title, author ="佚名";
        try {
            id = music["id"].get<unsigned long>();
            pic = music["al"]["picUrl"].get<string>();
            title = music["name"].get<string>();
            author = music["ar"][0]["name"].get<string>();
            download(id, pic);
            list += info(title, author, id);
        } catch (...) {
            string cmd = "echo \"" + to_string(id) + "\" >> log";
            system(cmd.c_str());
            continue;
        }
    }
    return list;
}

int main(int argc, char* argv[]) {
    auto resp = sion::Fetch("http://" + string(argv[2]) + "/user/playlist?uid=" + string(argv[1]));
    auto list = nlohmann::json::parse(resp.StrBody())["playlist"];
    for (auto i = 0; i < 8; i ++) {
        auto id = list[i]["id"].get<unsigned long>();
        std::cout << "Downloading " << id << std::endl;
        record(dump(id).dump(4), list[i]["name"].get<string>(), string(argv[3]));
    }
}