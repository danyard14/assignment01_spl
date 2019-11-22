//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Session.h"

Session::Session(const std::string &configFilePath) {
    //read a JSON file
    using json = nlohmann::json;
    std::ifstream i(configFilePath);
    json j;
    i >> j;

    for(auto &element : j["movies"].items()){
        std::string x = "Name: " + (std::string)element.value()["name"];

        for(auto &subElement : element.value()["tags"].items()) {
            x += (std::string)subElement.value();
        }
        std::cout << x << std::endl;

    }
}

void Session::start() {
    Session("../config1.json");
}