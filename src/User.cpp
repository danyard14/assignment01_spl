//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/User.h"
#include "../include/Session.h"
#include "../include/Watchable.h"


double getAverageWatchTime();

// constractor
User::User( std::string &name) : name(name){
    // make sure that the initialized vector is made in stack and copy to history by deep copy
    history = std::vector<Watchable*>();
}

LengthRecommenderUser::LengthRecommenderUser( std::string &name) : User(name) {

}
RerunRecommenderUser::RerunRecommenderUser( std::string &name) : User(name) {
}
GenreRecommenderUser::GenreRecommenderUser( std::string &name) : User(name) {

}

// destractor
User::~User() {
    history.clear();
}

// copy constructor
User::User( User &other) : name(other.name), history(other.history) {

}
LengthRecommenderUser::LengthRecommenderUser( LengthRecommenderUser &other) : User(other) {

}
RerunRecommenderUser::RerunRecommenderUser( RerunRecommenderUser &other) : User(other) {

}
GenreRecommenderUser::GenreRecommenderUser( GenreRecommenderUser &other) : User(other) {

}

// copy assignment operator
User& User::operator=(const User& other) {
}


std::string User::getName() {
    return name;
}
std::vector<Watchable*> User::get_history() const {
    return history;
}

void User::setName(std::string nameToSet) {
    name =nameToSet;
}

void User::addToHistory(Watchable* watchable) {
    history.push_back(watchable);

}

Watchable* LengthRecommenderUser::getRecommendation(Session &s) {
    int sum=0;
    int i=0;
    for(auto& item: history){
        sum = sum + item->getLength();
        i++;
    }
    double average = sum/i;

    return s.getClosestTimeWatchable(average,this);
}



LengthRecommenderUser &LengthRecommenderUser::cloneUser(std::string newName){
    LengthRecommenderUser* userClone = new LengthRecommenderUser(*this);
    userClone->setName(newName);
    return *userClone;
}

bool LengthRecommenderUser::userWatched(Watchable *watchable) {
    std::vector<Watchable*>::iterator iterator;
    iterator = std::find(history.begin(),history.end(),watchable);

    // if watched
    if(iterator != history.end() ){
        return true;
    }
    return false;
}


GenreRecommenderUser &GenreRecommenderUser::cloneUser(std::string newName){
    GenreRecommenderUser* userClone = new GenreRecommenderUser(*this);
    userClone->setName(newName);
    return *userClone;
}

RerunRecommenderUser &RerunRecommenderUser::cloneUser(std::string newName){
    RerunRecommenderUser* userClone = new RerunRecommenderUser(*this);
    userClone->setName(newName);
    return *userClone;
}

 bool GenreRecommenderUser:: userWatched(Watchable* watchable){
    return false;
}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}

bool RerunRecommenderUser:: userWatched(Watchable* watchable){
    return false;
}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}



