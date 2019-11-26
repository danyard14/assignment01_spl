//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/User.h"
#include "../include/Session.h"
#include "../include/Watchable.h"

//TODO: implement copy constructor for use (vector cloning)

// USER type User
User::User( std::string &name) : name(name){
    // make sure that the initialized vector is made in stack and copy to history by deep copy
    history = std::vector<Watchable*>();
}

// copy constructor
User::User(User &other) : name(other.name), history(other.history) {}

// copy assignment operator
User& User::operator=(const User& other) {
    name = other.name;
    history = other.history;
}

// move constructor
User::User(User &&other) : name(other.name), history(other.history) {
    other.name = nullptr;
    other.history.clear();
}

// distractor
User::~User() {
    history.clear();
}

// add watched to history
void User::addToHistory(Watchable* watchable) {
    history.push_back(watchable);
}

std::string User::getName() {
    return name;
}

// get history vector
std::vector<Watchable*> User::get_history() const {
    return history;
}

void User::setName(std::string nameToSet) {
    name =nameToSet;
}

// methods
bool User::userWatched(Watchable *watchable) {
    std::vector<Watchable*>::iterator iterator;
    iterator = std::find(history.begin(),history.end(),watchable);

// if watched
    if(iterator != history.end() ){
        return true;
    }
    return false;
}

std::pair<std::string, int> User::getMaxFromMap(std::map<std::string, int>* map) {
    std::pair<std::string, int> maxPair = {"", 0};
    for (auto &item : *map) {
        if (item.second > maxPair.second) {
            maxPair = item;
        } else if (item.second == maxPair.second & item.first < maxPair.first) {
            maxPair = item;
        }
    }
    map->erase(maxPair.first);
    return maxPair;
}

//
// LENGTH type user

// constructor
LengthRecommenderUser::LengthRecommenderUser(std::string &name) : User(name) {}

// copy constructor
LengthRecommenderUser::LengthRecommenderUser(LengthRecommenderUser &other) : avg(other.avg), User(other) {}

// copy assignment operator
LengthRecommenderUser& LengthRecommenderUser::operator=(const LengthRecommenderUser& other) {
    //TODO:: check how to do
}

// move constructor
LengthRecommenderUser::LengthRecommenderUser(LengthRecommenderUser &&other) : avg(other.avg), User(other) {
    other.avg = 0;
}

// return new user of type length
LengthRecommenderUser &LengthRecommenderUser::cloneUser(std::string newName){
    LengthRecommenderUser* userClone = new LengthRecommenderUser(*this);
    userClone->setName(newName);
    return *userClone;
}

Watchable* LengthRecommenderUser::getRecommendation(Session &s) {
    int sum = 0;
    int i = 0;
    for(auto& item: history){
        sum = sum + item->getLength();
        i++;
    }
    double average = sum/i;

    return s.getClosestTimeWatchable(average,this);
}

//
// RERUN type user

// constructor
RerunRecommenderUser::RerunRecommenderUser( std::string &name) :  lastRecIndex(-1), User(name) {}

// copy constructor
RerunRecommenderUser::RerunRecommenderUser(RerunRecommenderUser &other) : lastRecIndex(other.lastRecIndex), User(other) {}

// copy assignment operator
RerunRecommenderUser& RerunRecommenderUser::operator=(const RerunRecommenderUser& other) {
    //TODO:: check how to do
}

// move constructor
RerunRecommenderUser::RerunRecommenderUser(RerunRecommenderUser &&other) : lastRecIndex(other.lastRecIndex), User(other) {
    other.lastRecIndex = 0;
}

int RerunRecommenderUser:: getLastRecIndex() {
    return lastRecIndex;
}

// methods
Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    if(lastRecIndex == -1 & history.size() > 0){
        return history.at(0);
    }
    else if (lastRecIndex =! -1){
        int nextIndexToWatch = (lastRecIndex+1) % history.size();
        lastRecIndex = nextIndexToWatch;
        return history.at(nextIndexToWatch);

    }
}

RerunRecommenderUser &RerunRecommenderUser::cloneUser(std::string newName){
    RerunRecommenderUser* userClone = new RerunRecommenderUser(*this);
//    for(auto& watchable : history){
//        userClone->history
//    }
    userClone->setName(newName);
    return *userClone;
}

// GENRE user type
// constructor
GenreRecommenderUser::GenreRecommenderUser( std::string &name) : User(name) {

}

// copy constructor
GenreRecommenderUser::GenreRecommenderUser( GenreRecommenderUser &other) : User(other) {}

// copy assignment operator
GenreRecommenderUser& GenreRecommenderUser::operator=(const GenreRecommenderUser& other) {
    //TODO:: check how to do
}

// methods
Watchable *GenreRecommenderUser::getRecommendation(Session &s) {

    std::map<std::string,int> genreMap;

    // build map by frequency of tag appearance.
    for(auto& watchable: history){
        for(auto& tag: watchable->getTags()){
            auto iterator = genreMap.find(tag);
            if(iterator != genreMap.end()){
                iterator->second ++ ;
            }
            // didn't see this genre before
            else{
                genreMap.insert({tag,1});
            }
        }
    }

    Watchable* watchable = s.findcontentByGenre(getMaxFromMap(&genreMap).first);

    while (!genreMap.empty() & watchable == nullptr) {
        watchable = s.findcontentByGenre(getMaxFromMap(&genreMap).first);
    }

    if (watchable == nullptr) {
        // return - error
    }

    return watchable;
}

GenreRecommenderUser &GenreRecommenderUser::cloneUser(std::string newName){
    GenreRecommenderUser* userClone = new GenreRecommenderUser(*this);
    userClone->setName(newName);
    return *userClone;
}