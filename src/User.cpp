//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/User.h"
#include "../include/Session.h"
#include "../include/Watchable.h"


// USER type User
User::User( std::string &name) : name(name){
    // make sure that the initialized vector is made in stack and copy to history by deep copy
    history = std::vector<Watchable*>();
}

// copy constructor
User::User( User &other) : name(other.name), history(other.history) {
}

// copy assignment operator
User& User::operator=(const User& other) {
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










// LENGTH type user

// constructor
LengthRecommenderUser::LengthRecommenderUser( std::string &name) : User(name) {
}

// copy constructor
LengthRecommenderUser::LengthRecommenderUser( LengthRecommenderUser &other) : User(other) {

}

// return new user of type length
LengthRecommenderUser &LengthRecommenderUser::cloneUser(std::string newName){
    LengthRecommenderUser* userClone = new LengthRecommenderUser(*this);
    userClone->setName(newName);
    return *userClone;
}

// say if user watched a given watchable
bool LengthRecommenderUser::userWatched(Watchable *watchable) {
    std::vector<Watchable*>::iterator iterator;
    iterator = std::find(history.begin(),history.end(),watchable);

    // if watched
    if(iterator != history.end() ){
        return true;
    }
    return false;
}










// RERUN type user

// constructor
RerunRecommenderUser::RerunRecommenderUser( std::string &name) : User(name) {
}

// copy constructor
RerunRecommenderUser::RerunRecommenderUser( RerunRecommenderUser &other) : User(other) {

}










// GENRE user type
// constructor
GenreRecommenderUser::GenreRecommenderUser( std::string &name) : User(name) {

}

// copy constructor
GenreRecommenderUser::GenreRecommenderUser( GenreRecommenderUser &other) : User(other) {

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



