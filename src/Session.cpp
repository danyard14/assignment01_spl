//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Session.h"
#include "../include/Watchable.h"
#include "../include/User.h"

// constractor
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
                Episode* newEpisode = new Episode(id, element.value()["name"], element.value()["episode_length"],
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
Session::Session(const Session &other) {
   //TODO: copy constructor
    }
// destractor
Session::~Session() {
    actionsLog.clear();

    activeUser = nullptr;

    for (auto content : content) {
        delete content;
    }

    for (auto user : userMap) {
        delete user.second;
    }

    userMap.clear();
}

void Session::start() {
    Session("../config1.json");
    activeUser = new LengthRecommenderUser("default");

    std::string command;
    std::cout << "insert a command";
    std::getline(std::cin, command);
    while (command != "exit") {

        std::string commandType = command.substr(0, command.find_first_of(' '));


        if (commandType == "createuser") {
            std::string afterFirstWord = command.substr(command.find(' ') + 1);
            std::string userName = afterFirstWord.substr(0, afterFirstWord.find_first_of(' '));
            std::string reccomendAlgo = afterFirstWord.substr(afterFirstWord.find(' ') + 1);

            CreateUser* action = new CreateUser(userName, reccomendAlgo);
            actionsLog.push_back(action);
            action->act(*this);
            }
        else if (commandType == "changeuser") {
                std::string afterFirstWord = command.substr(command.find(' ') + 1);
                std::string userName = afterFirstWord.substr(0, afterFirstWord.find_first_of(' '));

                ChangeActiveUser* action = new ChangeActiveUser(userName);
                actionsLog.push_back(action);
                action->act(*this);
        }
        else if (commandType == "deleteuser") {
                std::string afterFirstWord = command.substr(command.find(' ') + 1);
                std::string userName = afterFirstWord.substr(0, afterFirstWord.find_first_of(' '));

                DeleteUser* action = new DeleteUser(userName);
                actionsLog.push_back(action);
                action->act(*this);
        }
        else if (commandType == "dupuser") {
            std::string afterFirstWord = command.substr(command.find(' ') + 1);
            std::string originUserName = afterFirstWord.substr(0, afterFirstWord.find_first_of(' '));
            std::string newUserName = afterFirstWord.substr(afterFirstWord.find(' ') + 1);

            //TODO: duplicate user
        }
        else if (commandType == "content") {
            PrintContentList* action = new PrintContentList();
            actionsLog.push_back(action);
            action->act(*this);
        }
        else if (commandType == "watchlist") {
                //TODO: print watch list history
        }
        else if (commandType == "watch") {
                std::string afterFirstWord = command.substr(command.find(' ') + 1);
                std::string contentId = afterFirstWord.substr(0, afterFirstWord.find_first_of(' '));

                //TODO: watch content
        }
        else if(commandType == "log"){
            PrintActionsLog* action = new PrintActionsLog();
            actionsLog.push_back(action);
            action->act(*this);
            action->setStatus(COMPLETED);
        }
    }
}

std::string Session::createUser(CreateUser &action) {
    // check if user exist already
    if (userMap.find(action.getName()) != userMap.end()) {
        return "User Already Exist";
    }
    else {
        std::string typeOfUser = action.getRecAlgo();
        std::string userName = action.getName();

        if (typeOfUser == "len") {
            LengthRecommenderUser *user = new LengthRecommenderUser(userName);
            userMap.insert({userName, user});
        } else if (typeOfUser == "gen") {
            RerunRecommenderUser *user = new RerunRecommenderUser(userName);
            userMap.insert({userName, user});

        } else if (typeOfUser == "rer") {
            GenreRecommenderUser *user = new GenreRecommenderUser(userName);
            userMap.insert({userName, user});
        }
        return "";
    }
}

std::string Session::deleteUser(DeleteUser &action) {
    if (userMap.find(action.getUserName()) != userMap.end()) {
        userMap.erase(action.getUserName());
        return "";
    }
    else {
        action.setStatus(ERROR);
        return "User Doesn't Exist";
    }
}

std::string Session::changeActiveUser(ChangeActiveUser &action) {
    std::string userName = action.getUserName();
    if (userMap.find(userName) != userMap.end()) {
        activeUser = userMap.at(userName);
        return "";
    }
    else {
        return "User Doesn't Exist";
    }
}

void Session::printActionLog(){
    for (int i = actionsLog.size()-2; i > 0; i--) {
        std::cout << (actionsLog.at(i))->toString() << std::endl;
    }
}

void Session::printContentList(PrintContentList &action) {
    for (auto &element : content)
        std::cout << element->toString() << std::endl;
}
