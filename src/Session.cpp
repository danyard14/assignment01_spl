//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Session.h"
#include "../include/Watchable.h"
#include "../include/User.h"

Session::Session(const std::string &configFilePath) {

    // read a JSON file
    using json = nlohmann::json;
    std::ifstream i(configFilePath);
    json j;
    i >> j;

    long id = 1;

    // insert all movies to watchable vector
    for (auto &element : j["movies"].items()) {
        std::vector<std::string> tags;

        // get movie tags
        for (auto &subElement : element.value()["tags"].items()) {
            tags.push_back(subElement.value());
        }

        Movie* movie =  new Movie(id, element.value()["name"],element.value()["length"], tags);

        content.push_back(movie);
        id++;
    }

    // insert all tv-series to watchable vector
    for (auto &element : j["tv_series"].items()) {
        std::vector<std::string> tags;

        // get series tags
        for (auto &subElement : element.value()["tags"].items()) {
            tags.push_back(subElement.value());
        }
        int numOfSeasons = element.value()["seasons"].size();
        for (int season = 1; season <= numOfSeasons; season++) {
            int numOfEpisodes = element.value()["seasons"][season-1];
            for (int episode = 1; episode <= numOfEpisodes ; episode++) {
                Episode *newEpisode = new Episode(id, element.value()["name"], element.value()["episode_length"],
                                                  season, episode, tags);
                content.push_back(newEpisode);
                id++;
            }
        }
    }

    // print the contents
    for (auto &content : content) {
        std::cout << content -> toString() << std::endl;
    }
    //actionsLog and userMap are initialized automatically as empty.
    //TODO:figure out where we get current user from
}

void Session::start() {
    Session("../config1.json");
    std::string command;
    std::cout << "insert a command";
    std::getline(std::cin, command);

    while (command != "exit") {

        std::string commandType = command.substr(0, command.find_first_of(' '));
        if (commandType == "createuser") {
            std::string afterFirstWord = command.substr(command.find(' ') + 1);
            std::string userName = afterFirstWord.substr(0, afterFirstWord.find_first_of(' '));
            std::string reccomendAlgo = afterFirstWord.substr(afterFirstWord.find(' ') + 1);

            //TODO: create user
//            actionsLog.push_back(createUserAct);
//            if (userMap.find(userName) != userMap.end()) {
//                User* user;
//                if (reccomendAlgo == "len")
//                    user = new LengthRecommenderUser(userName);
//                else if (reccomendAlgo == "rer")
//                    user = new RerunRecommenderUser(userName);
//                else if (reccomendAlgo == "gen")
//                    user = new GenreRecommenderUser(userName);
//                userMap.insert({userName, user});
//                //return "";
//            }
//            else
//                //return "error..."
        }
        else if (commandType == "changeuser") {
            std::string afterFirstWord = command.substr(command.find(' ') + 1);
            std::string userName = afterFirstWord.substr(0, afterFirstWord.find_first_of(' '));

            //TODO: change user
        }
        else if (commandType == "deleteuser") {
            std::string afterFirstWord = command.substr(command.find(' ') + 1);
            std::string userName = afterFirstWord.substr(0, afterFirstWord.find_first_of(' '));

            //TODO: delete user
        }
        else if (commandType == "dupuser") {
            std::string afterFirstWord = command.substr(command.find(' ') + 1);
            std::string originUserName = afterFirstWord.substr(0, afterFirstWord.find_first_of(' '));
            std::string newUserName = afterFirstWord.substr(afterFirstWord.find(' ') + 1);

            //TODO: duplicate user
        }
        else if (commandType == "content") {
            //TODO: print content
        }
        else if (commandType == "watchlist") {
            //TODO: print watch list history
        }
        else if (commandType == "watch") {
            std::string afterFirstWord = command.substr(command.find(' ') + 1);
            std::string contentId = afterFirstWord.substr(0, afterFirstWord.find_first_of(' '));

            //TODO: watch content
        }
        else if (commandType == "deleteuser") {
            //TODO: print actions
        }
    }
}