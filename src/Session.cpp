//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Session.h"
#include "../include/Watchable.h"
#include "../include/User.h"
#include <limits>

// constractor
Session::Session(const std::string &configFilePath) {
    defaultUserString = "default";
    // read a JSON file
    using json = nlohmann::json;
    std::ifstream i(configFilePath);
    json j;
    i >> j;

    long id = 0;

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

                if(season == numOfSeasons & episode == numOfEpisodes){
                newEpisode->setNextWatchableId(-1);
                }
                else{
                    newEpisode->setNextWatchableId(id+1);
                }
                id++;
            }
        }
    }
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
    activeUser = new LengthRecommenderUser(defaultUserString);
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
            if(newUserName != "" & originUserName != ""){
                DuplicateUser* action = new DuplicateUser(originUserName, newUserName);
                actionsLog.push_back(action);
                action->act(*this);
            }
        }
        else if (commandType == "content") {
            PrintContentList* action = new PrintContentList();
            actionsLog.push_back(action);
            action->act(*this);
        }
        else if (commandType == "watchlist") {
            PrintWatchHistory* action = new PrintWatchHistory();
            actionsLog.push_back(action);
            action->act(*this);
        }
        else if (commandType == "watch") {
            std::string afterFirstWord = command.substr(command.find(' ') + 1);
            std::string contentId = afterFirstWord.substr(0, afterFirstWord.find_first_of(' '));

            if (is_number(contentId)) { // check if the content id is ok
                int id = stoi(contentId);
                if (id % 1 == 0) {
                    Watch* action = new Watch(id);
                    actionsLog.push_back(action);
                    action->act(*this);
                }
                else {
                    std::cout << "wrong Id" << std::endl;
                }
            }
            else
            {
                std::cout << "wrong Id" << std::endl;
            }
        }
        else if(commandType == "log"){
            PrintActionsLog* action = new PrintActionsLog();
            actionsLog.push_back(action);
            action->act(*this);
            action->setStatus(COMPLETED);
        }
        std::cout << "insert a command";
        std::getline(std::cin, command);
    }
}

std::string Session::createUser(CreateUser &action) {
    // check if user exist already
    if (userMap.find(action.getUserName()) != userMap.end()) {
        return "User Already Exist";
    }
    else {
        std::string typeOfUser = action.getUserRecAlgo();
        std::string userName = action.getUserName();

        if (typeOfUser == "len") {
            LengthRecommenderUser *user = new LengthRecommenderUser(userName);
            userMap.insert({userName, user});
        } else if (typeOfUser == "rer") {
            RerunRecommenderUser *user = new RerunRecommenderUser(userName);
            userMap.insert({userName, user});

        } else if (typeOfUser == "gen") {
            GenreRecommenderUser *user = new GenreRecommenderUser(userName);
            userMap.insert({userName, user});
        }
        return "";
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
std::string Session::deleteUser(DeleteUser &action) {
    std::string userName = action.getUserName();
    if (userMap.find(userName) != userMap.end()) {
        std::pair<std::string, User> usr = userMap.find(userName);
        delete *usr.second;
        userMap.erase(userName);
        return "";
    }
    else {
        action.setStatus(ERROR);
        return "User Doesn't Exist";
    }
}
void Session::printContentList(PrintContentList &action) {
    int i = 1;
    for (auto &element : content) {
        std::cout << std::to_string(i) + ". " + element->toString() + element->printLengthAndTags() << std::endl;
        i++;
    }
}
void Session::printWatchHistory() {
    int i = 1;
    std::cout << "Watch history for " + activeUser->getName() << std::endl;
    for (auto &content : activeUser->get_history()) {
        std::cout << std::to_string(i) + ". " + content->toString() << std::endl;
        i++;
    }
}
void Session::printActionLog(){
    for (int i = actionsLog.size()-2; i >= 0; i--) {
        std::cout << (actionsLog.at(i))->toString() << std::endl;
    }
}

std::string Session::duplicateUser(DuplicateUser &action) {
    std::string oldUserName = action.getOriginUserName();
    std::string newUserName = action.getNewUserName();

    // if old user exist
    if (userMap.find(oldUserName) != userMap.end()) {

        // if new user doesn't exist
        if(userMap.find(newUserName) == userMap.end()){


            // duplicate
            addUserToMap(&(userMap.find(oldUserName)->second->cloneUser(newUserName)));

            return "";
        }
        else{
            return "New User Name Is Taken";
        }
    }
    else {
        return "User To Duplicate Doesn't Exist";
    }
}

// check if string is a number
bool Session::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

std::string Session::watchContentById(Watch &action) {
    if(action.getContentId() < content.size()) {
        Watchable* cont = content.at(action.getContentId());
        std::cout << "Watching " + cont->toString() << std::endl;
        activeUser->addToHistory(cont);

        Watchable* suggestion = cont->getNextWatchable(*this);
        if(suggestion){
            std::string command;
            std::cout << "We recommend watching "+suggestion->toString()+" continue watching? [y/n]" << std::endl;
            std::getline(std::cin, command);
            if(command=="y" | command == "Y"){
                Watch* action = new Watch(suggestion->getContentId());
                actionsLog.push_back(action);
                action->act(*this);
            }
        }
        else {
            //TODO:: what if no content
        }
        return "";
    }
    else {
        return "Wrong ID";
    }
}

void Session::addUserToMap(User* user) {
    userMap.insert({user->getName(), user});
}

User *Session::getActiveUser() {
    return activeUser;
}

Watchable * Session::getContentAtIndex(int i) {
    return content[i];
}

Watchable *Session::getClosestTimeWatchable(double avg, LengthRecommenderUser* user) {
    int closestLength = std::numeric_limits<int>::max();
    //user->get_history();
    int index = 0;
    int chosen = -1;
    for(auto& item : content){
        if(!user->userWatched(item)){
            if(abs(item->getLength()-avg) < closestLength){
                chosen = index;
                closestLength = abs(item->getLength()-avg);
            }
        }
        index ++;
    }
    return content.at(chosen);
}

Watchable* Session::findcontentByGenre(std::string genre) {

    for(auto& watchable : content){
        if(watchable->hasTag(genre) && !activeUser->userWatched(watchable)){
            return watchable;
        }
    }
    return  nullptr;
}
