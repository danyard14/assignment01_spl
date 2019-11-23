//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/User.h"

// constractor
User::User(const std::string &name) : name(name){
    // make sure that the initialized vector is made in stack and copy to history by deep copy
    history = std::vector<Watchable*>();
}
LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) {

}
RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name) {

}
GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name) {

}

// destractor
User::~User() {
    history.clear();
}

// copy constructor
User::User(const User &other) : name(other.name), history(other.history) {

}
LengthRecommenderUser::LengthRecommenderUser(const LengthRecommenderUser &other) : User(other) {

}
RerunRecommenderUser::RerunRecommenderUser(const RerunRecommenderUser &other) : User(other) {

}
GenreRecommenderUser::GenreRecommenderUser(const GenreRecommenderUser &other) : User(other) {

}

// copy assignment operator
User& User::operator=(const User& other) {
}


std::string User::getName() const {
    return name;
}
std::vector<Watchable*> User::get_history() const {
    return history;
}

Watchable* LengthRecommenderUser::getRecommendation(Session &s) {

}